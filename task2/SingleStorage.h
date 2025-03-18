#ifndef SINGLE_STORAGE_H
#define SINGLE_STORAGE_H

#include "BackupAlgorithm.h"

class SingleStorage : public BackupAlgorithm {
public:
    void backup(const std::vector<std::string>& files, const std::string& storagePath) override;
};

#endif 
