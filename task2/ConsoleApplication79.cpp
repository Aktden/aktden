#include <iostream>
#include <memory>
#include <stdexcept>
#include "BackupJob.h"
#include "SplitStorage.h"
#include "SingleStorage.h"

void validateFiles(const std::vector<std::string>& files) {
    for (const auto& file : files) {
        std::ifstream f(file);
        if (!f.good()) {
            throw std::runtime_error("File not found: " + file);
        }
    }
}

int main() {
    try {
        std::vector<std::string> files = { "file1.txt", "file2.txt" };
        validateFiles(files);

        auto splitStorage = std::make_unique<SplitStorage>();
        BackupJob job1("/backup/path", std::move(splitStorage));
        job1.addRestorePoint(files);
        job1.executeBackup();

        auto singleStorage = std::make_unique<SingleStorage>();
        BackupJob job2("/backup/path", std::move(singleStorage));
        job2.addRestorePoint(files);
        job2.executeBackup();

    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}