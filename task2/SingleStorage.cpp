#include "SingleStorage.h"
#include <iostream>

void SingleStorage::backup(const std::vector<std::string>& files, const std::string& storagePath) {
    std::string archiveName = storagePath + "/backup.zip";
    std::cout << "Creating single archive: " << archiveName << std::endl;

}