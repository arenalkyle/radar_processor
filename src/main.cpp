#include "../include/Config.h"
#include "../include/SignalSource.h"
#include "../include/Processor.h"
#include "../include/PeakDetector.h"
#include "../include/Validator.h"
#include "../include/DataExporter.h"
#include <spdlog/spdlog.h>

int main() {
    spdlog::info("Starting radar signal processing.");

    const SignalSource source(Config::DefaultSampleRate, Config::DefaultSeed);
    spdlog::info("Config has {} target(s).", Config::Targets.size());

    const auto rawSignal = source.generate(Config::DefaultSignalSize);
    spdlog::info("Generated signal with {} samples.", Config::DefaultSignalSize);

    Processor processor(Config::DefaultThreadCount);
    const auto processedData = processor.process(rawSignal);
    spdlog::info("Processed signal using FFT.");

    const auto magnitudes = PeakDetector::toMagnitude(processedData);
    const auto peakIndices = PeakDetector::detectPeaks(magnitudes, Config::DefaultThreshold);
    spdlog::info("Detected {} peaks.", peakIndices.size());

    std::vector<double> detectedFrequencies;
    constexpr double resolution = Config::DefaultSampleRate / Config::DefaultSignalSize;
    for (const size_t idx : peakIndices) {
        detectedFrequencies.push_back(static_cast<double>(idx) * resolution);
    }

    std::vector<double> trueFrequencies;
    for (const auto& [freq, amp, phase] : Config::Targets) {
        trueFrequencies.push_back(freq);
    }

    const auto result = Validator::validate(trueFrequencies, detectedFrequencies, Config::DefaultToleranceHz);
    Validator::printResult(result);


    try {
        DataExporter::exportToCSV("processed_data.csv", processedData);
        spdlog::info("Exported processed data to 'processed_data.csv'.");
    } catch (const std::exception& e) {
        spdlog::error("Failed to export data to CSV: {}", e.what());
    }

    spdlog::info("Finished radar signal processing.");
    return result.passed ? 0 : 1;
}