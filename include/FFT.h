#ifndef RADARSIGNALPROCESSOR_FFT_H
#define RADARSIGNALPROCESSOR_FFT_H
#include <vector>
#include <complex>

// Implement cooley-tukey fft (iteratively)
class FFT {
public:
    static void fft(std::vector<std::complex<double>>& data);
private:
    static void computeRadix2(std::vector<std::complex<double>>& data);     // Powers of 2 (Primary path)
    static void computeMixedRadix(std::vector<std::complex<double>>& data); // Unrestricted (For flexibility)
};

#endif //RADARSIGNALPROCESSOR_FFT_H
