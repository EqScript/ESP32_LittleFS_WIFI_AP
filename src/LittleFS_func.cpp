#include "LittleFS_func.h"

void createDir(const char* path) {
  Serial.printf("Creating directory: %s\n", path);
  LittleFS.mkdir(path);
}

void writeFile(const char* path, const char* message) {
  Serial.printf("Writing file: %s\n", path);
  File file = LittleFS.open(path, "w");
  if (!file) {
    Serial.println("Failed to open file for writing");
    return;
  }
  file.print(message);
  file.close();
}

void appendFile(const char* path, const char* message) {
  Serial.printf("Appending to file: %s\n", path);
  File file = LittleFS.open(path, "a");
  if (!file) {
    Serial.println("Failed to open file for appending");
    return;
  }
  file.print(message);
  file.close();
}

void readFile(const char* path) {
  Serial.printf("Reading file: %s\n", path);
  File file = LittleFS.open(path, "r");
  if (!file) {
    Serial.println("Failed to open file for reading");
    return;
  }

  while (file.available()) {
    Serial.write(file.read());
  }
  Serial.println();
  file.close();
}