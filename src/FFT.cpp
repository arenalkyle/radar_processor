#include "../include/FFT.h"

const double PI = std::acos(-1);

// Keeps all memory in place to avoid extra memory allocation
void FFT::fft(std::vector<std::complex<double>>& data) {
    size_t n = data.size();

#ifdef DEBUG
    std::cout << "FFT Size: " << n << std::endl;
#endif

    if (n > 0 && (n & (n - 1)) == 0) {
        computeRadix2(data);
    } else {
        computeMixedRadix(data); // fallback so we are unrestricted
    }
}

void FFT::computeRadix2(std::vector<std::complex<double>>& data) {
    size_t n = data.size();

    // in place bit reversal
    for (size_t i = 1, j = 0; i < n; i++) {
        size_t bit = n >> 1;
        for (; j & bit; bit >>= 1) {
            j ^= bit;
        }
        j ^= bit;

        if (i < j) {
            std::swap(data[i], data[j]);
        }
    }

    // Controls stages of FFT (len = 2, 4, 8, ..., n)
    for (size_t len = 2; len <= n; len <<= 1) { //
        // -2pi is forward FFT.
        const double ang = -2 * PI / len;
        const std::complex<double> twiddleFactorStep(std::cos(ang), std::sin(ang));

        // `i += len` refers to next group of samples.
        for (size_t i = 0; i < n; i += len) {
            std::complex<double> twiddle(1);

            for (size_t j = 0; j < len / 2; j++) {
                std::complex<double> u = data[i + j];                       // Even
                std::complex<double> v = twiddle * data[i + j + len / 2];   // Odd, rotated by "twiddle factor"

                // butterfly step
                data[i + j] = u + v;
                data[i + j + len / 2] = u - v;
                twiddle *= twiddleFactorStep; // advance twiddle factor
            }
        }
    }
}

// TODO: optimize mixed radix
void FFT::computeMixedRadix(std::vector<std::complex<double>>& data) {
    size_t n = data.size();
    if (n <= 1) {
        return;
    }

    // find smallest prime factor
    size_t p = 2;
    while (n % p != 0) p++;

    size_t m = n / p;

    // Mixed-radix, data is a (p * m) matrix
    std::vector<std::vector<std::complex<double>>> subData(p, std::vector<std::complex<double>>(m)); // ! optimize

    for (size_t i = 0; i < p; i++) {
        for (size_t j = 0; j < m; j++) {
            subData[i][j] = data[i + j * p];
        }

        if (m > 0 && (m & (m - 1)) == 0) {
            computeRadix2(subData[i]);
        } else {
            computeMixedRadix(subData[i]); // Otherwise, keep factoring
        }
    }

    // Recombine using twiddle factor
    for (size_t k = 0; k < m; ++k) {
        for (size_t j = 0; j < p; ++j) {
            std::complex<double> sum(0, 0);

            for (size_t i = 0; i < p; ++i) {
                double angle = -2.0 * PI * (i * (j * m + k)) / n;
                std::complex<double> twiddle(std::cos(angle), std::sin(angle));
                sum += subData[i][k] * twiddle;
            }
            data[j * m + k] = sum;
        }
    }
}

