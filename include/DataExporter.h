#ifndef RADARSIGNALPROCESSOR_DATAEXPORTER_H
#define RADARSIGNALPROCESSOR_DATAEXPORTER_H
#include <string>
#include <vector>
#include <complex>


class DataExporter {
public:
    static void exportToCSV(const std::string& filename, const std::vector<std::complex<double>>& data);

    /*
    static bool exportComplexSignalCsv(
        const std::string& path,
        const std::vector<std::complex<double>>& signal
    );

    static bool exportMagnitudeCsv(
        const std::string& path,
        const std::vector<double>& magnitude
    );

    static bool exportDetectedFrequenciesCsv(
        const std::string& path,
        const std::vector<double>& frequencies
    );
    */
};

#endif //RADARSIGNALPROCESSOR_DATAEXPORTER_H
