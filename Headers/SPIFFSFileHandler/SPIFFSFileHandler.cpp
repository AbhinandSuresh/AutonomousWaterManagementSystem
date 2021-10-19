/*
   This  library is  created with necessary functions to use SPIFFS in ESP8266.
*/

#include <string.h>
#include <ESP8266WiFi.h>
#include "FS.h"
#include "SPIFFSFileHandler.h"

*
 * Define DEBUG for Debug Mode
 * DEBUG_LEVEL 0,1,2 can be used for various debugging levels
 * 2: Verbose mode
 * 1: Debug mode
 * 0: End user mode
*/
#define DEBUG 
#define DEBUG_LEVEL 1
#ifdef DEBUG
#define debug_Println(level,msg) { \
        if(DEBUG_LEVEL >= level) \
        debug_Println(1,msg); \
        }
#define debug_Print(level,msg) { \
        if(DEBUG_LEVEL >= level) \
        debug_Println(1,msg); \
        }
#else
#define debug_Println(x)
#define debug_Print(x)
#endif

/*
   This function reads data from a file. the Function accepts filename and String variable to store the data
   Parameters
   1)char * filename:- name of the file to be read.
   2)String data :- to store the data read from the file
*/
void readFile(char * filename, String data)
{
  unsigned int lineNumber = 0;
  File MyFile = SPIFFS.open(filename, "r");// open the file in read mode
  if (!MyFile)
  {
    debug_Println(1,"File not found"));
  }
  while (MyFile.available()) // Read line by line from the file
  {
    lineNumber++;
    data += MyFile.readStringUntil('\n');
    data += '\n';
  }
  MyFile.close();
}

/*
   This function Write data to a file. The Function accepts filename and String variable to write the data to the file
   Parameters
   1)char * filename:- name of the file.
   2)String data :-  the data to bewritten to the file.
*/
void writeFile(char * filename, String data)
{
  File f = SPIFFS.open(filename, "a");// create or open the file in append mode.
  if (!f)
  {
    debug_Println(1,"File not found");
  }
  else
  {
    f.printf("%s\n", data); //Write the data in the file
    debug_Println(1,"data saved in: ");
    debug_Println(1,filename);
  }

  f.close();
}

/*
   This function remove the File. The Function accepts filename as input.
   Parameters
   1)char * filename:- name of the file to be removed
*/
void removeFile(char * filename) 
{
  SPIFFS.remove(filename);
  debug_Println(1,"File is removed");
}
