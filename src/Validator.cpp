#include "../include/Validator.h"

#include <algorithm>
#include <cmath>
#include <iostream>
#include <ostream>
#include <spdlog/spdlog.h>

// Compare:
//      - True frequencies
//      - Detected detections
//      - Tolerance
Result Validator::validate(const std::vector<double>& trueFrequencies, const std::vector<double>& detectedFrequencies, const double tolerance) {

    Result result;

    if (tolerance < 0.0) {
        result.passed = false;
        return result;
    }

    std::vector detectedUsed(detectedFrequencies.size(), false);
    result.matchedTrueFrequencies.reserve(trueFrequencies.size()); // pre-allocate to avoid memory reallocations

    for (double trueFreq : trueFrequencies) {
        bool match = false;

        for (size_t i = 0; i < detectedFrequencies.size(); ++i) {
            if (!detectedUsed[i] && std::fabs(detectedFrequencies[i] - trueFreq) <= tolerance) {
                detectedUsed[i] = true;
                match = true;
                result.matchedTrueFrequencies.push_back(trueFreq);
                break;
            }
        }

        if (!match) {
            result.missedTrueFrequencies.push_back(trueFreq);
        }
    }

    for (size_t i = 0; i < detectedFrequencies.size(); ++i) {
        if (!detectedUsed[i]) {
            result.falseDetectedFrequencies.push_back(detectedFrequencies[i]);
        }
    }

    result.passed = result.missedTrueFrequencies.empty();
    return result;
}

void Validator::printResult(const Result& result) {
    if (result.passed) {
        spdlog::info("Validation passed.");
    } else {
        spdlog::warn("Validation failed.");
    }

    if (!result.matchedTrueFrequencies.empty()) {
        spdlog::info("Matched true frequencies:");
        for (const double f : result.matchedTrueFrequencies) {
            spdlog::info("  - {:>8.2} Hz", f);
        }
    }

    if (!result.missedTrueFrequencies.empty()) {
        spdlog::warn("Missed frequencies:");
        for (const double f : result.missedTrueFrequencies) {
            spdlog::warn("  - {:>8.2} Hz", f);
        }
    }

    if (!result.falseDetectedFrequencies.empty()) {
        spdlog::error("False detections:");
        for (const double f : result.falseDetectedFrequencies) {
            spdlog::error("  - {:>8.2} Hz", f);
        }
    }
}