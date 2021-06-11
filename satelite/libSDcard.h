//Source: https://randomnerdtutorials.com/esp32-data-logging-temperature-to-microsd-card/

#include "FS.h"
#include "SD.h"
#define SD_CS 5

String dataMessage;
void appendFile(fs::FS &fs, const char * path, const char * message);
void initSD();

void logSDCard(String dataMessage) {

  appendFile(SD, "/data.csv", dataMessage.c_str());
}

void writeFile(fs::FS &fs, const char * path, const char * message) {
  File file = fs.open(path, FILE_WRITE);
  file.close();
}

void appendFile(fs::FS &fs, const char * path, const char * message) {

  File file = fs.open(path, FILE_APPEND);
  file.close();
}

void initSD() {

  SD.begin(SD_CS);
  File file = SD.open("/data.csv");
  writeFile(SD, "/data.csv", "Temp., Press, GPSLat, GPSLong \r\n");
  file.close();
}
