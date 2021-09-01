#include <ESP8266WiFi.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
#include <string.h>
#include "FS.h"


// Replace with your network credentials
const char* ssid = "Kaldrago";
const char* password = "Bakabakabaka";

// Define NTP Client to get time
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org");

// Variable to save current epoch time
unsigned long lastsnap;
unsigned long currenttime;
unsigned long nowtime;
unsigned long epoch;
unsigned long newepoch;
unsigned long lastHourlySavedTime = 0;
unsigned long lastDailySavedTime = 0;
unsigned long lastMonthlySavedTime = 0;
bool  spiffsActive = false;


#define HOURLYFILE "/hourlyfile.txt"
#define MONTHLYFILE "/monthlyfile.txt"
#define DAILYFILE "/dailyfile.txt"
#define BATTERYSTATUS "/batteryfile.txt"

struct water
{
  unsigned long savetime;
  float level;
};
// Function that gets current epoch time
void getTime() {
  timeClient.update();
  epoch = timeClient.getEpochTime();
}

void times() {
  if (lastsnap < nowtime) {
    currenttime = epoch - (lastsnap / 1000) + (nowtime / 1000);
  }
 if (lastsnap > nowtime) {
    newepoch = currenttime;
    currenttime = newepoch - (lastsnap / 1000) + (nowtime / 1000);
  }
}
// Initialize WiFi
void initWiFi() {
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi ..");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print('.');
    delay(1000);
  }
  Serial.println(WiFi.localIP());
}
void readfile(char * filename, float *average) {
  String line;
  float sumWaterlevel = 0;
  unsigned int lineNumber = 0;
  File MyFile = SPIFFS.open(filename, "r");
  if (!MyFile) {
    Serial.println(F("File not found"));
  }
  while (MyFile.available()) {  // Read line by line from the file
    lineNumber++;
    line = MyFile.readStringUntil('\n');
    //Serial.println(line);
    int coma = line.indexOf(",");
    String savedtime = line.substring(0, coma);
    float waterlevel = line.substring(coma + 1).toInt();
    sumWaterlevel += waterlevel;
    //Serial.println(lineNumber);
    //Serial.println(sumWaterlevel);
  }
  *average = sumWaterlevel / lineNumber;
  //Serial.println(*average);
  MyFile.close();
  SPIFFS.remove(filename);
}
void writeFile(char * filename, struct water * tankdata)
{
  if (spiffsActive) {
    File f = SPIFFS.open(filename, "a");
    if (!f) {
      Serial.print("Unable To Open '");
      Serial.print(filename);
      Serial.println("' for writing");
      Serial.println();
    } else {
      f.printf("%ld,%f\n", tankdata->savetime, tankdata->level);
      Serial.print("data saved in: ");
      Serial.println(filename);
      f.close();
    }
  }
  else {
    Serial.print("Unable To Find ");
    Serial.println(filename);
    Serial.println();
  }
}
void SaveHourlyData( struct water * tankdata) {

  writeFile(HOURLYFILE, tankdata);
  lastHourlySavedTime = currenttime;


}
void SaveDialyData() {
  struct water tankdata;
  float average;
  readfile(HOURLYFILE, &average);
  tankdata.savetime = currenttime;
  tankdata.level = average;
  writeFile(DAILYFILE, &tankdata);
  lastDailySavedTime = currenttime;
  Serial.println("data saved in daily file");

}

void SaveMonthlyData() {
  struct water tankdata;
  float average;
  readfile(DAILYFILE, &average);
  tankdata.savetime = currenttime;
  tankdata.level = average;
  writeFile(MONTHLYFILE, &tankdata);
  lastMonthlySavedTime = currenttime;
  Serial.println("data saved in daily file");
}

void setup() {

  Serial.begin(115200);
  //connect to your local wi-fi network
  initWiFi();
  delay(1000);
  timeClient.begin();
  getTime();
  Serial.println(epoch);
  lastsnap = millis();
  // Start filing subsystem
  if (SPIFFS.begin()) {
    Serial.println("SPIFFS Active");
    Serial.println();
    spiffsActive = true;
  } else {
    Serial.println("Unable to activate SPIFFS");
  }
  delay(2000);
}

void loop() {
  times();
  struct water tankdata;
  tankdata.savetime = 126798247;
  tankdata.level = 10;
  if ((currenttime - lastHourlySavedTime) >= 10) {
    SaveHourlyData(&tankdata);
  }
  if ((currenttime - lastDailySavedTime) >= 20) {

    SaveDialyData();

  }
  if ((currenttime - lastMonthlySavedTime) >= 100) {

    SaveMonthlyData();

  }
  //Serial.println(epoch);
 //Serial.println(newepoch); 
  //Serial.println(currenttime);
  nowtime = millis();
}
