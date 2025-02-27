#ifndef SOUNDBOARD_HPP
#define SOUNDBOARD_HPP

#include <SDL3/SDL_audio.h>

class Soundboard;

struct AudioData {
    SDL_AudioSpec spec;
    Uint8*        buf;
    Uint32        len;
    int           pos   = 0;
    float         gain  = 0.025f;
    float         ratio = 1.0f;
    float         a     = 1.0f;
    float         b     = 1.0f;
};

class Soundboard {
  public:
    SDL_AudioStream* stream = nullptr;
    AudioData        audio;

    Soundboard();
    ~Soundboard();

    void play_one();

    void cleanup();
};

#endif // SOUNDBOARD_HPP
