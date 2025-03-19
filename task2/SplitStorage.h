#ifndef SPLIT_STORAGE_H
#define SPLIT_STORAGE_H

#include "BackupAlgorithm.h"

class SplitStorage : public BackupAlgorithm {
public:
    void backup(const std::vector<std::string>& files, const std::string& storagePath) override;
};

#endif