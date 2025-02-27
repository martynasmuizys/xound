#include "soundboard.hpp"
#include <SDL3/SDL_audio.h>
class Audio {
  public:
    SDL_AudioDeviceID device_id = SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK;
    SDL_AudioStream* stream = nullptr;
    Soundboard soundboard;

    Audio();
    ~Audio();

    void bind_stream(SDL_AudioStream* stream);
    void unbind_stream(SDL_AudioStream* stream);
};
