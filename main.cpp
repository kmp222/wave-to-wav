#include "sine_oscillator.hpp"
#include <iostream>
#include <fstream>

void write_to_file(std::ofstream &file, int value, int size) {
    file.write(reinterpret_cast<const char*>(&value), size);
}

int main() {

    int duration = 2;
    const int bit_depth = 16;

    std::ofstream audio_file;
    audio_file.open("sine.wav", std::ios::binary);

    SineOscillator s(100, 2);

    // Header chunk
    audio_file << "RIFF";
    audio_file << "----"; // placeholder
    audio_file << "WAVE";

    // Format chunk
    audio_file << "fmt ";
    write_to_file(audio_file, 16, 4);
    write_to_file(audio_file, 1, 2); // codice compressione (PCM uncompressed)
    write_to_file(audio_file, 1, 2); // numero canali
    write_to_file(audio_file, sample_rate, 4); // sample rate
    write_to_file(audio_file, sample_rate * bit_depth / 8, 4); // bps
    write_to_file(audio_file, 2, 2); // block align
    write_to_file(audio_file, bit_depth, 2); // bit depth

    // Data chunk
    audio_file << "data";
    audio_file << "----"; // placeholder

    int pre_audio_pos = audio_file.tellp();

    auto max_amplitude = pow(2, bit_depth - 1) - 1;

    for (int i = 0; i < sample_rate * duration; ++i) {

        auto sample = s.process();
        int int_sample = static_cast<int> (sample * max_amplitude);
        write_to_file(audio_file, int_sample, 2);

    }

    int post_audio_pos = audio_file.tellp();

    audio_file.seekp(pre_audio_pos - 4); // torno al secondo placeholder e sostituisco
    write_to_file(audio_file, post_audio_pos - pre_audio_pos, 4);

    audio_file.seekp(4, std::ios::beg); // torno all'inizio e mi sposto di 4 byte
    write_to_file(audio_file, post_audio_pos - 8, 4);


    audio_file.close();  

    return 0;

}

