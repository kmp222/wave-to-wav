#include "sine_oscillator.hpp"

SineOscillator::SineOscillator(float freq, float amp) : frequency(freq), amplitude(amp) {
    offset = 2 * M_PI * frequency / sample_rate;
}

float SineOscillator::process() {
    auto sample = amplitude * sin(angle);
    angle += offset;
    return sample;
}
