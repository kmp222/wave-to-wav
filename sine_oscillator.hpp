#ifndef SINE_OSCILLATOR_HPP
#define SINE_OSCILLATOR_HPP

#include <cmath>

const int sample_rate = 44100;

class SineOscillator {

    float frequency;
    float amplitude;
    float angle = 0.0f;
    float offset = 0.0;

    public:
        SineOscillator(float freq, float amp);
        float process();
        
};

#endif