#include "../include/DataExporter.h"

#include <fstream>

void DataExporter::exportToCSV(const std::string& filename, const std::vector<std::complex<double>>& data) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open file: " + filename);
    }

    file << "Real,Imaginary\n";
    for (const auto& value : data) {
        file << value.real() << "," << value.imag() << "\n";
    }
}
/*
bool DataExporter::exportComplexSignalCsv(const std::string& path, const std::vector<std::complex<double>>& signal) {
    std::ofstream file(path);
    if (!file.is_open()) {
        return false;
    }

    file << "index,real,imag\n";
    for (size_t i = 0; i < signal.size(); ++i) {
        file << i << ',' << signal[i].real() << ',' << signal[i].imag() << '\n';
    }

    return true;
}

bool DataExporter::exportMagnitudeCsv(const std::string& path, const std::vector<double>& magnitude) {
    std::ofstream file(path);
    if (!file.is_open()) {
        return false;
    }

    file << "index,magnitude\n";
    for (size_t i = 0; i < magnitude.size(); ++i) {
        file << i << ',' << magnitude[i] << '\n';
    }

    return true;
}

bool DataExporter::exportDetectedFrequenciesCsv(const std::string& path, const std::vector<double>& frequencies) {
    std::ofstream file(path);
    if (!file.is_open()) {
        return false;
    }

    file << "frequency_hz\n";
    for (double f : frequencies) {
        file << f << '\n';
    }

    return true;
}
*/