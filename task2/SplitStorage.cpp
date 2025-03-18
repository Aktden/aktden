#include "SplitStorage.h"
#include <iostream>

void SplitStorage::backup(const std::vector<std::string>& files, const std::string& storagePath) {
    for (const auto& file : files) {
        std::string archiveName = storagePath + "/" + file + ".zip";
        std::cout << "Creating archive: " << archiveName << std::endl;
    }
}