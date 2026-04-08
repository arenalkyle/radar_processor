#ifndef RADARSIGNALPROCESSOR_PEAKDETECTOR_H
#define RADARSIGNALPROCESSOR_PEAKDETECTOR_H
#include <complex>
#include <vector>

class PeakDetector {
public:
    static std::vector<size_t> detectPeaks(const std::vector<double>& magnitude, double threshold);
    static std::vector<double> toMagnitude(const std::vector<std::complex<double>>& fftData);
};

#endif //RADARSIGNALPROCESSOR_PEAKDETECTOR_H
