#include "../include/PeakDetector.h"

#include <complex>

std::vector<size_t> PeakDetector::detectPeaks(const std::vector<double>& magnitude, const double threshold) {
    std::vector<size_t> peaks;
    peaks.reserve(32);

    for (size_t i = 1; i < magnitude.size() - 1; i++) {
        if (magnitude[i] > magnitude[i-1] && magnitude[i] > magnitude[i+1] && magnitude[i] > threshold) {
            if (peaks.empty() || (i - peaks.back() > 2)) {
                peaks.push_back(i);
            }
        }
    }
    return peaks;
}

std::vector<double> PeakDetector::toMagnitude(const std::vector<std::complex<double>>& fftData) {
    const size_t num = fftData.size() / 2;
    std::vector<double> magnitude(num);

    for (size_t i = 0; i < fftData.size() / 2; ++i) {
        magnitude[i] = std::abs(fftData[i]);
    }
    return magnitude;
}