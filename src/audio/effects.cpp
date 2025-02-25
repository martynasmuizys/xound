#include "effects.hpp"
#include <SDL3/SDL_stdinc.h>

float normalize(float sample) {
    if (sample > 1.0f) {
        sample = 1.0f;
    }
    if (sample < -1.0f) {
        sample = -1.0f;
    }
    return sample;
}

float gain(float sample, float gain) {
    return sample * gain;
}

float low_pass_filter(float current_sample, float previous_sample) {
    float a0      = 0.75f;
    float a1      = 0.25f;
    return a0 * current_sample + a1 * previous_sample;
    // float x      = SDL_tanf(3.14f * 100.0f / 44100.0f);
    // float output = x * current_sample + x * previous_sample - (x - 1) * current_sample;
    // output /= (x + 1);

    // return output;
    // return a * current_sample + (1.0f - a) * previous_sample;
    // return (current_sample - previous_sample) / 2.0f;
}
