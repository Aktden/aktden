#ifndef BACKUP_JOB_H
#define BACKUP_JOB_H

#include <vector>
#include <memory>
#include <string>
#include "RestorePoint.h"
#include "BackupAlgorithm.h"

class BackupJob {
private:
    std::vector<std::shared_ptr<RestorePoint>> restorePoints;
    std::string storagePath;
    std::unique_ptr<BackupAlgorithm> algorithm;

public:
    BackupJob(const std::string& path, std::unique_ptr<BackupAlgorithm> algo);
    void addRestorePoint(const std::vector<std::string>& files);
    void removeRestorePoint(int index);
    void executeBackup();
};

#endif 
