#include <benchmark/benchmark.h>
#include "../include/Config.h"
#include "../include/FFT.h"
#include "../include/Processor.h"
#include "../include/SignalSource.h"

// Benchmark for FFT performance
static void BM_FFT(benchmark::State& state) {
    std::vector<std::complex<double>> data(state.range(0), 1.0);
    for (auto _ : state) {
        FFT::fft(data, false);
    }
}

// Benchmark for Processor with random signals
static void BM_Processor(benchmark::State& state) {
    SignalSource source(Config::DefaultSampleRate, Config::DefaultSeed);
    const auto signal = source.generate(state.range(0));
    Processor processor(Config::DefaultThreadCount);

    for (auto _ : state) {
        processor.process(signal);
    }
}

BENCHMARK(BM_FFT)->RangeMultiplier(2)->Range(Config::DefaultSignalSize, 65536);
BENCHMARK(BM_Processor)->RangeMultiplier(2)->Range(Config::DefaultSignalSize, 65536);

BENCHMARK_MAIN();