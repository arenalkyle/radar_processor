#ifndef RADARSIGNALPROCESSOR_VALIDATOR_H
#define RADARSIGNALPROCESSOR_VALIDATOR_H
#include <vector>

// Compare:
//      - True frequencies (from signalsource)
//      - Detected peaks

struct Result {
    bool passed{};
    std::vector<double> matchedTrueFrequencies;
    std::vector<double> missedTrueFrequencies;
    std::vector<double> falseDetectedFrequencies;
};

class Validator {
public:
    static Result validate(
        const std::vector<double>& trueFrequencies,
        const std::vector<double>& detectedFrequencies,
        double tolerance
        );

    static void printResult(const Result& result);
};

#endif //RADARSIGNALPROCESSOR_VALIDATOR_H
