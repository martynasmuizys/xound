#include "soundboard.hpp"
#include "effects.hpp"

#include <SDL3/SDL_audio.h>
#include <SDL3/SDL_error.h>
#include <SDL3/SDL_init.h>
#include <SDL3/SDL_log.h>
#include <SDL3/SDL_oldnames.h>
#include <SDL3/SDL_stdinc.h>
#include <SDL3/SDL_timer.h>

void SDLCALL play(void* userdata, SDL_AudioStream* stream, int additional_len, int) {
    AudioData* data = static_cast<AudioData*>(userdata);

    if(data->len == 0) {
        return;
    }

    additional_len  = SDL_min(additional_len, data->len);

    additional_len /= sizeof(Sint16);
    while (additional_len > 0) {
        Sint16    samples[1024];
        const int total = SDL_min(additional_len, SDL_arraysize(samples));

        float     prev_sample = 0.0f;

        for (int i = 0; i < total; ++i) {
            Sint16 buf    = static_cast<Sint16>((data->buf[data->pos + 1] << 8) | data->buf[data->pos]);
            float  sample = buf / 32767.0f;
            sample        = low_pass_filter(sample, prev_sample, data->a);
            sample        = high_pass_filter(sample, prev_sample, data->b);
            sample        = normalize(sample);

            buf         = static_cast<Sint16>(sample * 32767.0f);
            samples[i]  = buf;
            prev_sample = sample;
            data->pos += 2;
        }

        SDL_SetAudioStreamGain(stream, data->gain);
        SDL_SetAudioStreamFrequencyRatio(stream, data->ratio);
        SDL_PutAudioStreamData(stream, samples, total * sizeof(Sint16));

        additional_len -= total;
        data->len -= total * sizeof(Sint16);
    }
}

Soundboard::Soundboard() {}

Soundboard::~Soundboard() {
    cleanup();
}

void Soundboard::play_one() {
    // if (!SDL_LoadWAV("/home/martis/personal/projects/xound/let_it_happen.wav", &spec, &audio.buf, &audio.len)) {
    if (!SDL_LoadWAV("/home/martis/personal/projects/xound/augh.wav", &audio.spec, &audio.buf, &audio.len)) {
        // if (!SDL_LoadWAV("C:\\Users\\sirzi\\Downloads\\let_it_happen.wav", &spec, &audio.buf, &audio.len)) {
        SDL_Log("Error: %s", SDL_GetError());
        return;
    }

    stream = SDL_OpenAudioDeviceStream(SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK, &audio.spec, play, &audio);

    SDL_ResumeAudioStreamDevice(stream);
}

void Soundboard::cleanup() {
    if (stream) {
        SDL_ClearAudioStream(stream);
        SDL_DestroyAudioStream(stream);
        SDL_free(audio.buf);
        audio = {};
    }
}
