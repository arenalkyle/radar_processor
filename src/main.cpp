#include <iostream>
#include <vector>
#include <complex>
#include <cmath>
#include "../include/FFT.h"

const double PI = std::acos(-1);

std::vector<std::complex<double>> generateSignal(int n, double freq, double fs) {
    std::vector<std::complex<double>> signal(n);
    for (int i = 0; i < n; ++i) {
        double t = static_cast<double>(i) / fs;
        signal[i] = { std::sin(2.0 * PI * freq * t), 0.0 };
    }
    return signal;
}

void runTest(int numSamples, double targetFreq, double fs) {
    std::cout << "Test -> N = " << numSamples << std::endl;

    auto data = generateSignal(numSamples, targetFreq, fs);

    FFT::fft(data);

    // Nyquist limit
    double maxMag = 0;
    int peakIdx = 0;
    for (int i = 0; i < numSamples / 2; ++i) {
        double mag = std::abs(data[i]);
        if (mag > maxMag) {
            maxMag = mag;
            peakIdx = i;
        }
    }

    double detectedFreq = peakIdx * (fs / numSamples);

    std::cout << "Target: " << targetFreq << " Hz -> Detected: " << detectedFreq << " Hz" << std::endl;

    if (std::abs(detectedFreq - targetFreq) <= (fs / numSamples)) {
        std::cout << "[PASS]" << std::endl;
    } else {
        std::cout << "[FAIL]" << std::endl;
    }
}

int main() {
    constexpr double fs = 2000.0; // Sample rate
    constexpr double freq = 150.0; // Target freq

    runTest(1024, freq, fs);
    runTest(1000, freq, fs);

    return 0;
}