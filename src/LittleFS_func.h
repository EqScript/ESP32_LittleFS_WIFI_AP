#ifndef LITTLEFS_FUNC_h
#define LITTLEFS_FUNC_H

#include <FS.h>
#include <LittleFS.h>

void createDir(const char* path);
void writeFile(const char* path, const char* message);
void appendFile(const char* path, const char* message);
void readFile(const char* path);

#endif