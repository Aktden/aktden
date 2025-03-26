#include "BackupJob.h"
#include <stdexcept>

BackupJob::BackupJob(const std::string& path, std::unique_ptr<BackupAlgorithm> algo)
    : storagePath(path), algorithm(std::move(algo)) {}

void BackupJob::addRestorePoint(const std::vector<std::string>& files) {
    restorePoints.push_back(std::make_shared<RestorePoint>(files));
}

void BackupJob::removeRestorePoint(int index) {
    if (index >= 0 && index < restorePoints.size()) {
        restorePoints.erase(restorePoints.begin() + index);
    }
}

void BackupJob::executeBackup() {
    for (const auto& point : restorePoints) {
        algorithm->backup(point->getBackupFiles(), storagePath);
    }
}