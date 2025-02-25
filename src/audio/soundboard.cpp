#include "soundboard.hpp"
#include "effects.hpp"

#include <SDL3/SDL_audio.h>
#include <SDL3/SDL_error.h>
#include <SDL3/SDL_init.h>
#include <SDL3/SDL_log.h>
#include <SDL3/SDL_oldnames.h>
#include <SDL3/SDL_stdinc.h>
#include <SDL3/SDL_timer.h>
#include <csignal>

void SDLCALL play(void* userdata, SDL_AudioStream* stream, int additional_len, int) {
    AudioData* data = static_cast<AudioData*>(userdata);

    // If there is nothing to play, return
    if (data->len <= 0) {
        return;
    }

    int   samples     = additional_len / sizeof(Sint16);
    float prev_sample = 0.0f;

    for (int i = 0; i < samples; ++i) {
        int    pos    = i * 2;
        Sint16 buf    = static_cast<Sint16>((data->buf[pos + 1] << 8) | data->buf[pos]);
        float  sample = buf / 32767.0f;
        // sample        = gain(sample, 0.3f);
        // sample = low_pass_filter(sample, prev_sample);
        // sample = normalize(sample);
        buf    = static_cast<Sint16>(sample * 32767.0f);

        data->buf[pos]     = buf & 0xFF;
        data->buf[pos + 1] = (buf >> 8) & 0xFF;
        prev_sample        = sample;
    }

    SDL_PutAudioStreamData(stream, data->buf, additional_len);

    data->buf += additional_len;
    data->len -= additional_len;
}

Soundboard::Soundboard() {
    if (!SDL_Init(SDL_INIT_AUDIO)) {
        SDL_Log("Error: %s", SDL_GetError());
    }
}

Soundboard::~Soundboard() {}

namespace {
    volatile bool stop = false;
}

void Soundboard::play_one() {
    if (!SDL_LoadWAV("/home/martis/personal/projects/zoundboard-new/let_it_happen.wav", &spec, &audio.buf,
                     &audio.len)) {
        return;
    }

    SDL_AudioStream* stream = SDL_OpenAudioDeviceStream(SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK, &spec, play, &audio);

    SDL_ResumeAudioStreamDevice(stream);

    std::signal(SIGINT, [](int) { stop = true; });
    while (audio.len > 0 && !stop) {}
}
