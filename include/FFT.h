#ifndef RADARSIGNALPROCESSOR_FFT_H
#define RADARSIGNALPROCESSOR_FFT_H
#include <vector>
#include <complex>

// Implement cooley-tukey fft (iteratively)
class FFT {
public:
    static void fft(std::vector<std::complex<double>>& data, bool inverse = false);
private:
    static void computeRadix2(std::vector<std::complex<double>>& data, bool inverse);     // Powers of 2 (Primary path)
    static void computeMixedRadix(std::vector<std::complex<double>>& data, bool inverse); // Unrestricted (For flexibility)
};

#endif //RADARSIGNALPROCESSOR_FFT_H
