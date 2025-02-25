#ifndef SOUNDBOARD_HPP
#define SOUNDBOARD_HPP

#include <SDL3/SDL_audio.h>

struct AudioData {
    Uint8* buf;
    Uint32 len;
    int    pos = 0;
};

class Soundboard {
  public:
    SDL_AudioSpec spec;
    AudioData audio;

    Soundboard();
    ~Soundboard();

    void play_one();
};

#endif // SOUNDBOARD_HPP
