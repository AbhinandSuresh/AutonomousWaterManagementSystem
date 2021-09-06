#include <string.h>
#include "FS.h"

struct water
{
  unsigned long savetime;
  float level;
};

void readfile(char * filename) {
  String line;
  unsigned int lineNumber = 0;
  File MyFile = SPIFFS.open(filename, "r");
  if (!MyFile) {
    Serial.println(F("File not found"));
  }
  while (MyFile.available()) {  // Read line by line from the file
    lineNumber++;
    line = MyFile.readStringUntil('\n');
  }
}


void writeFile(char * filename, struct water * tankdata)
{
    File f = SPIFFS.open(filename, "a");
    if (!f) {
    Serial.println(F("File not found"));
  }
    f.printf("%ld,%f\n", tankdata->savetime, tankdata->level);
}

void closeFile(char * filename)
{
filename.close();
}
