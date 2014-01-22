#include <SD.h>
#include <SPI.h>




//--------------SETTINGS TO LOAD------------------
int integer1;
int integer2;
bool boolean1;
bool boolean2;
String string1;
String string2;



void setup(){
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }

  // initialize SD card
  setupSD();
  // read file
  readConfigFile("CONFIG.TXT");

  //print results
  printConfig();
}

void loop() {  
}

bool mapValues(String _description,File _myFile, char _character){
  // do not change valuees starting with underscore
  
  if(_description == "intName1") {
    //first function argument is the default integer value
    integer1 = parseInteger(5000, _myFile,_character);

  } else if(_description == "intName2") {
    integer2 = parseInteger(10,_myFile,_character);

  } else if(_description == "boolName1") {
    boolean1 = parseBool(_character);

  } else if(_description == "boolName1") {
    boolean1 = parseBool(_character);

  } else if(_description == "strName1") {
    string1 = parseString(_myFile,_character);

  } else if(_description == "strName2") {
    string2 = parseString(_myFile,_character);

  }else { // unknown parameter - description not found
    return false;  
  }
  return true;
}

void printConfig(){
  Serial.print("integer1: ");
  Serial.println(integer1);
  Serial.print("integer2: ");
  Serial.println(integer2);
  Serial.print("boolean1: ");
  Serial.println(boolean1);
  Serial.print("boolean2: ");
  Serial.println(boolean2);
  Serial.print("string1: ");
  Serial.println(string1);
  Serial.print("string2: ");
  Serial.println(string2);
}