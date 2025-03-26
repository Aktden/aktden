#include "RestorePoint.h"

RestorePoint::RestorePoint(const std::vector<std::string>& files) : backupFiles(files) {
    creationTime = std::time(nullptr);
}

std::vector<std::string> RestorePoint::getBackupFiles() const {
    return backupFiles;
}

std::time_t RestorePoint::getCreationTime() const {
    return creationTime;
}