#ifndef SPIFFSFILEHANDLER_H_
#define SPIFFSFILEHANDLER_H_

/*
 * The headers required for SPIFFS.
 */
#include <ESP8266WiFi.h>
#include <string.h>
#include "FS.h"


/*
 * This function reads data from a file. the Function accepts filename and String variable to store the data
 * Parameters 
 * 1)char * filename:- name of the file to be read.
 * 2)String data :- to store the data read from the file
 */
void readFile(char * filename,String data);

/*
 * This function Write data to a file. The Function accepts filename and String variable to write the data to the file
 * Parameters 
 * 1)char * filename:- name of the file.
 * 2)String data :-  the data to bewritten to the file.
 */
void writeFile(char * filename,String data);

/*
 * This function remove the File. The Function accepts filename as input.
 * Parameters 
 * 1)char * filename:- name of the file to be removed
 */
void removeFile(char * filename);

#endif
