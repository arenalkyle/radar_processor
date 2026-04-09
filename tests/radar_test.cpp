#include <gtest/gtest.h>
#include <cmath>
#include "../include/FFT.h"
#include "../include/PeakDetector.h"
#include "../include/SignalSource.h"
#include "../include/Validator.h"

// Test FFT to ensure it works.
TEST(FFTTests, IdentityTransform) {
    std::vector<std::complex<double>> data = {1, 0, 0, 0};
    FFT::fft(data, false);
    FFT::fft(data, true);

    EXPECT_NEAR(std::abs(data[0]), 1.0, 1e-9);
    EXPECT_NEAR(std::abs(data[1]), 0.0, 1e-9);
    EXPECT_NEAR(std::abs(data[2]), 0.0, 1e-9);
    EXPECT_NEAR(std::abs(data[3]), 0.0, 1e-9);
}

// Test PeakDetector for single peak detection
TEST(PeakDetectorTests, SinglePeakDetection) {
    std::vector<double> magnitudes = {0, 1, 5, 1, 0};
    auto peaks = PeakDetector::detectPeaks(magnitudes, 2.0);
    ASSERT_EQ(peaks.size(), 1);
    EXPECT_EQ(peaks[0], 2);
}

// Test SignalSource for proper signal generation
TEST(SignalSourceTests, SignalGeneration) {
    const SignalSource source(Config::DefaultSampleRate, Config::DefaultSeed);
    const auto signal = source.generate(Config::DefaultSignalSize);

    ASSERT_EQ(signal.size(), Config::DefaultSignalSize);

    double maxAmplitude = 0.0;
    for (const auto& value : signal) {
        maxAmplitude = std::max(maxAmplitude, std::abs(value));
    }

    EXPECT_GT(maxAmplitude, 0.0);
}

// Test signal validation logic
TEST(ValidatorTests, FrequencyValidation) {
    const std::vector trueFrequencies = {150.0, 165.0, 125.0};
    const std::vector detectedFrequencies = {150.5, 164.8, 126.0};
    constexpr double tolerance = 2.0;

    const auto [passed, matchedTrueFrequencies, missedTrueFrequencies, falseDetectedFrequencies] = Validator::validate(trueFrequencies, detectedFrequencies, tolerance);
    EXPECT_TRUE(passed);

    EXPECT_EQ(matchedTrueFrequencies.size(), trueFrequencies.size());
    EXPECT_EQ(missedTrueFrequencies.size(), 0);
    EXPECT_EQ(falseDetectedFrequencies.size(), 0);
}

// Test peak detection fails without high enough threshold
TEST(PeakDetectorTests, ThresholdExceedsSignal) {
    const std::vector<double> magnitudes = {0, 1, 2, 1, 0};
    const auto peaks = PeakDetector::detectPeaks(magnitudes, 5.0);
    EXPECT_TRUE(peaks.empty());
}

// Test configuration-driven signal generation
TEST(SignalSourceTests, ConfigTargetDefinition) {
    const SignalSource source(Config::DefaultSampleRate, Config::DefaultSeed);

    const auto signal = source.generate(Config::DefaultSignalSize);

    ASSERT_EQ(signal.size(), Config::DefaultSignalSize);
    ASSERT_EQ(Config::Targets.size(), 3);
    EXPECT_NEAR(std::get<0>(Config::Targets[0]), 150.0, 1e-9);
}

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}