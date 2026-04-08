#ifndef RADARSIGNALPROCESSOR_PROCESSOR_H
#define RADARSIGNALPROCESSOR_PROCESSOR_H
#include <complex>
#include <vector>

class Processor {
public:
    Processor(int numThreads);

    std::vector<std::complex<double>> process(const std::vector<std::complex<double>>& signal);

private:
    int numThreads;
    void processChunk(std::vector<std::complex<double>>& data, size_t start, size_t end, size_t totalN);
};

#endif //RADARSIGNALPROCESSOR_PROCESSOR_H
