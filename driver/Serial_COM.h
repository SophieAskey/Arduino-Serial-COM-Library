// This is a Serial communication library designed to send and receive instructions to 
// and from another microcontroller or program.  


class Serial_COM{
  public:
    virtual void instructionInterpreter(String); 
    String makeInstruction(String, String[], int, char*);
    String makeInstruction(String, int[], int, char*);
    int sendInstruction(String);
    void start();

  private:
    const int BUFFER_LENGTH = 256; // Maximum number of characters read from Serial at one time. 
    const int INSTR_DELAY   = 100; // Minimum delay time to send an instruction.
    const int MAX_DATA      = 20;  // Maximum number of expected data members. SUBJECT TO CHANGE BY PROGRAMMER.
  
    int getSize(String, char*);
    void parseInstruction(String, String[], int, char*);
    void extractIntData(String[], int[], int);
};


// Initialization method for the Serial_COM class. Cannot set Serial baud rate (Serial.begin()) in constructor. 
void Serial_COM::start(){ Serial.begin(9600); }


// Returns the number of tokens an instruction has. Each token is seperated by a 
// a delimiter; the default delimiter is a space " ". If the number of tokens is 
// larger than the maximum number of expected tokens, the method will return -1.
// This can be caught to terminate analyzing the Serial input as it is not a 
// valid instruction. 
int Serial_COM::getSize(String instruction, char *delimiter=" "){    
  int instr_size = 0;
  char input[BUFFER_LENGTH];
  char *pch;
    
  instruction.toCharArray(input, BUFFER_LENGTH);
  pch = strtok(input, delimiter);
  for(;pch != NULL && instr_size < MAX_DATA; instr_size++){ String token(pch); pch = strtok(NULL, delimiter); }
  if(instr_size >= MAX_DATA){return -1;}
  
  return instr_size;
}


// Sends the instruction via Serial; delay is to ensure instruction is completely sent.
int Serial_COM::sendInstruction(String instruction){ Serial.println(instruction); delay(INSTR_DELAY); }


// Makes an instruction from a set of int data.  
String Serial_COM::makeInstruction(String instructionID, int data[], int arrSize, char *delimiter=" "){
  String instruction = instructionID;
  for(int i=0; i<arrSize; i++){ instruction = instruction + delimiter + String(data[i]); }
  return instruction;
}


// Makes an instruction from a set of String data.
String Serial_COM::makeInstruction(String instructionID, String data[], int arrSize, char *delimiter=" "){
  String instruction = instructionID;
  for(int i=0; i<arrSize; i++){ instruction = instruction + delimiter + data[i]; }
  return instruction;
}


// Parses an instruction received from Serial. The first token, the zeroeth element of parsed_instr, 
// is the instructionID which is used to specify which instruction to execute. The tokens following the
// instructionID are the arguments to the instruction. 
void Serial_COM::parseInstruction(String instruction, String parsed_instr[], int arrSize, char *delimiter=" "){
  char input[BUFFER_LENGTH];
  instruction.toCharArray(input, BUFFER_LENGTH);
  char *pch;

  pch = strtok(input, delimiter);
  for(int i=0; i<arrSize && pch != NULL; i++){
     String token(pch);    
     parsed_instr[i] = token;
     pch = strtok(NULL, delimiter);
  }
}  


// Extracts integer values from parsed_instr. The zeroeth element of parsed_instr is the instructionID 
// and the rest are the data values.  
void Serial_COM::extractIntData(String parsed_instr[], int extractedData[], int arrSize){
  for(int i=0; i<arrSize; i++){ extractedData[i] = parsed_instr[i+1].toInt(); }
}
