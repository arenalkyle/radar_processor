#ifndef RADARSIGNALPROCESSOR_CONFIG_H
#define RADARSIGNALPROCESSOR_CONFIG_H
#include <vector>


namespace Config {
    // Sampling defaults
    inline constexpr double DefaultSampleRate = 2000.0;
    inline constexpr int DefaultSignalSize = 1024;

    // Signal generation
    inline constexpr double DefaultTargetFreq = 150.0;
    inline constexpr unsigned int DefaultSeed = 12345;

    // Peak detection & validation
    inline constexpr double DefaultThreshold = 20.0;
    inline constexpr double DefaultToleranceHz = 5.0;

    // Window params
    inline constexpr double HammingAlpha = 0.54;
    inline constexpr double HammingBeta = 0.46;

    // Thread pool size
    inline constexpr int DefaultThreadCount = 4;

    // Targets
    inline const std::vector<std::tuple<double, double, double>> Targets = {
        {150.0, 0.8, 0.7},
        {165.0, 0.3, 1.6},
        {125.0, 0.4, 0.6}
    };
};

#endif //RADARSIGNALPROCESSOR_CONFIG_H
