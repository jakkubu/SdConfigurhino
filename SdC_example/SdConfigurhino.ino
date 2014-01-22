const int chipSelect = 10;


void setupSD(){
  bool isSdInitilized  = false;
  Serial.println("Initializing SD card...");
  pinMode(10, OUTPUT); // for SD
  
  // try to init SD card until succes
  do {
    if (!SD.begin(chipSelect)) {
      Serial.println("Card failed, or not present");
      // don't do anything more:
      isSdInitilized = false;
    } else {
      Serial.println("card initialized.");
      isSdInitilized = true;
    }
  } while(!isSdInitilized);  
}


void readConfigFile(String fileName){
  File _configFile;
  if (SD.exists(fileName)){
    _configFile = SD.open(fileName);
    if (_configFile){
      parseConfigFile(_configFile);
    }      
  } else {
    Serial.println("couldn't read config file: " + fileName);
  }
  _configFile.close();
  delay(100);
}

void parseConfigFile(File _myFile){
  char _character;
  String _description = "";  
    // read from the file until there's nothing else in it:
    while (_myFile.available()) {
      _character = _myFile.read();
      
             if(_character == '/')         {
               // Comment - ignore this line
               while(_character != '\n'){
                 _character = _myFile.read();
               };
      } else if(isalnum(_character))      {  // Add a _character to the _description
        _description.concat(_character);
      } else if(_character =='=')         {  // start checking the value for possible results
        // First trim out all trailing white spaces
        do {
           _character = _myFile.read();
        } while(_character == ' '); 


        //parse value - if description was not find read until the end of the line/file
        if(!mapValues(_description, _myFile,_character)){
          Serial.println("description not found: " + _description)
          while(_character != '\n' && _myFile.available()){
            _character = _myFile.read();
          }
        }


        _description = "";
      } else {
        // Ignore this character (could be space, tab, newline, carriage return or something else)
      }
    }
}


bool parseBool(char _character){
  if (_character=='1') {
    return true;
  } else {
    return false;
  } 
}

String parseString(File _myFile, char _character){
  String _value = "";
  bool _bConcat = false;
  do {
    if (_character == '\"'){//detect " _character
      if(_bConcat){break;}
      _bConcat = true;
    } else if(_bConcat){
      _value.concat(_character);
    }
    _character = _myFile.read();
  } while(_character != '\n');
  //Serial.println(_value);
  return _value;
}

int parseInteger(int _defaultVal, File _myFile, char _character){
  char _value[5];
  int _counter =0;
    while(_character != '\n' && _character != '/' ) {
      // Serial.print(_character);
      if(isdigit(_character)) {
        _value[_counter] = _character;
        _counter++;
      } 
      _character = _myFile.read(); 
      
    };
      // Convert chars to integer
      //Serial.print("\n1st val = ");
      //Serial.println(String(atoi(_value)));
    if (_counter>0) {
      return atoi(_value);
      
          //  return atoi(charBuf);
    } else {
      // revert to default value for invalid entry in config
      Serial.println("integer not found!");
      return _defaultVal;
    }
}

