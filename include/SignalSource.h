#ifndef RADARSIGNALPROCESSOR_SIGNALSOURCE_H
#define RADARSIGNALPROCESSOR_SIGNALSOURCE_H
#include <complex>
#include <random>
#include <vector>

#include "Config.h"

struct Target {
    double frequency;
    double amplitude;
    double phase;
};

class SignalSource {
public:
    explicit SignalSource(double sampleRate = Config::DefaultSampleRate, unsigned int seed = Config::DefaultSeed);

    void addTarget(double freq, double amp, double phase);
    std::vector<std::complex<double>> generate(int numSamples) const;

private:
    double sampleRate;
    double noisePower;
    std::vector<Target> targets;
    std::complex<double> generateNoise() const;


    mutable std::mt19937 rng;
    mutable std::normal_distribution<> dist;
};

#endif //RADARSIGNALPROCESSOR_SIGNALSOURCE_H
