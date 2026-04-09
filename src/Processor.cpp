#include "../include/Processor.h"

#include "Config.h"
#include "FFT.h"
#include "ThreadPool.h"

const double PI = acos(-1.0);

Processor::Processor(const int numThreads) : numThreads(numThreads) {}

std::vector<std::complex<double>> Processor::process(const std::vector<std::complex<double>>& signal) {
    size_t n = signal.size();
    std::vector<std::complex<double>> data = signal;

    // parallel preprocess
    const size_t chunkSize = n / numThreads;
    ThreadPool pool(Config::DefaultThreadCount);  // Thread pool creation

    for (int i = 0; i < numThreads; ++i) {
        size_t start = i * chunkSize;
        size_t end = (i == numThreads - 1) ? n : (i + 1) * chunkSize;
        pool.enqueue(&Processor::processChunk, this, std::ref(data), start, end, n);
    }

    FFT::fft(data, false);

    // todo use threads to calculate magnitude or CFAR detection

    return data;
}

void Processor::processChunk(std::vector<std::complex<double> > &data, const size_t start, const size_t end, const size_t totalN) {

    for (size_t i = start; i < end; ++i) {
        const double window = Config::HammingAlpha - Config::HammingBeta * std::cos(2.0 * PI * static_cast<double>(i) / (static_cast<double>(totalN) - 1));
        data[i] *= window;

        // gain/shifting here
    }
}

