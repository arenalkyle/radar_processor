#include "../include/SignalSource.h"
#include "../include/Config.h"
#include <random>

const double PI = acos(-1.0);

SignalSource::SignalSource(const double sampleRate, const unsigned int seed) : sampleRate(sampleRate), noisePower(5), rng(seed), dist(0.0, 1.0) {
    for (const auto& [frequency, amplitude, phase] : Config::Targets) {
        addTarget(frequency, amplitude, phase);
    }
}

std::vector<std::complex<double>> SignalSource::generate(const int numSamples) const {
    std::vector<std::complex<double>> signal(numSamples);

    for (const auto& [frequency, amplitude, phase] : targets) {
        const double omega = 2.0 * PI * frequency;
        const double dt = 1.0 / sampleRate;

        std::complex<double> phasor = std::polar(amplitude, phase);
        const std::complex<double> step = std::polar(1.0, omega * dt);

        for (int n = 0; n < numSamples; ++n) {
            signal[n] += phasor;
            phasor *= step;
        }
    }

    if (noisePower <= 0.0) return signal;

    for (int n = 0; n < numSamples; ++n) {
        signal[n] += generateNoise();
    }

    return signal;
}

std::complex<double> SignalSource::generateNoise() const {
    const double sigma = std::sqrt(noisePower / 2.0);
    return {
        sigma * dist(rng),
        sigma * dist(rng)
    };
}

void SignalSource::addTarget(double freq, double amp, double phase) {
    if (freq < 0.0 || freq > sampleRate / 2.0) return;
    if (amp <= 0.0) return;

    targets.push_back({freq, amp, phase});
}