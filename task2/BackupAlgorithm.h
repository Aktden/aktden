#ifndef BACKUP_ALGORITHM_H
#define BACKUP_ALGORITHM_H

#include <vector>
#include <string>

class BackupAlgorithm {
public:
    virtual ~BackupAlgorithm() = default;
    virtual void backup(const std::vector<std::string>& files, const std::string& storagePath) = 0;
};

#endif 
