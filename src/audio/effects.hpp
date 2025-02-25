#ifndef EFFECTS_HPP
#define EFFECTS_HPP

float normalize(float sample);

float gain(float sample, float gain);

float low_pass_filter(float current_sample, float previous_sample);

#endif // !EFFECTS_HPP
