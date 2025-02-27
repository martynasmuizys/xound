#ifndef EFFECTS_HPP
#define EFFECTS_HPP

float normalize(float sample);

float low_pass_filter(float current_sample, float previous_sample, float a);

float high_pass_filter(float current_sample, float previous_sample, float a);

#endif // !EFFECTS_HPP
