#ifndef RESTORE_POINT_H
#define RESTORE_POINT_H

#include <string>
#include <vector>
#include <ctime>

class RestorePoint {
private:
    std::vector<std::string> backupFiles;
    std::time_t creationTime;

public:
    RestorePoint(const std::vector<std::string>& files);
    std::vector<std::string> getBackupFiles() const;
    std::time_t getCreationTime() const;
};

#endif 