#include "../include/FFT.h"

const double PI = acos(-1.0);

void FFT::fft(std::vector<std::complex<double>>& data, const bool inverse) {
    const size_t n = data.size();

    if (n > 0 && (n & (n - 1)) == 0) {
        computeRadix2(data, inverse);
    } else {
        computeMixedRadix(data, inverse);
    }

    if (inverse) {
        const double scale = 1.0 / static_cast<double>(n);
        for (auto& sample: data) {
            sample *= scale;
        }
    }
}

void FFT::computeRadix2(std::vector<std::complex<double>>& data, const bool inverse) { // Fastest when input length is power of two
    const size_t n = data.size();

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

    for (size_t len = 2; len <= n; len <<= 1) {
        // -2pi is forward FFT.
        const double ang = (inverse ? 2 : -2) * PI / len;
        const std::complex<double> twiddleFactorStep(std::cos(ang), std::sin(ang));

        // `i += len` refers to next group of samples.
        for (size_t i = 0; i < n; i += len) {
            std::complex<double> twiddle(1);

            for (size_t j = 0; j < len / 2; j++) {
                std::complex<double> u = data[i + j];
                std::complex<double> v = twiddle * data[i + j + len / 2];

                data[i + j] = u + v;
                data[i + j + len / 2] = u - v;
                twiddle *= twiddleFactorStep;
            }
        }
    }
}

// TODO: optimize mixed radix
void FFT::computeMixedRadix(std::vector<std::complex<double>>& data, const bool inverse) { // Slower, but for flexibility
    const size_t n = data.size();
    if (n <= 1) {
        return;
    }

    size_t p = 2;
    while (n % p != 0) p++;

    const size_t m = n / p;
    std::vector subData(p, std::vector<std::complex<double>>(m)); // todo optimize

    for (size_t i = 0; i < p; i++) {
        for (size_t j = 0; j < m; j++) {
            subData[i][j] = data[i + j * p];
        }

        if (m > 0 && (m & (m - 1)) == 0) {
            computeRadix2(subData[i], inverse);
        } else {
            computeMixedRadix(subData[i], inverse); // Otherwise, keep factoring
        }
    }

    for (size_t k = 0; k < m; ++k) {
        for (size_t j = 0; j < p; ++j) {
            std::complex<double> sum(0, 0);

            for (size_t i = 0; i < p; ++i) {
                const double angle = (inverse ? 2.0 : -2.0) * PI * (i * (j * m + k)) / n;
                std::complex twiddle(std::cos(angle), std::sin(angle));
                sum += subData[i][k] * twiddle;
            }
            data[j * m + k] = sum;
        }
    }
}
