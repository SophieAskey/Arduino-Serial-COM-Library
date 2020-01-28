

#include "Serial_COM.h"

Serial_COM serial_com;

// Sample data to be read and written by instruction interpreter
String instrID = "instrID";
int data_set[] = {1, 2, 3};
int data_set_size = sizeof(data_set) / sizeof(data_set[0]);


void setup() {
  serial_com.start();
  Serial.print("Using sendInstruction and makeInstruction: ");
  serial_com.sendInstruction(serial_com.makeInstruction(instrID, data_set, data_set_size));
}


void loop() { 
  if(Serial.available()){ serial_com.instructionInterpreter(Serial.readStringUntil('\n')); } 
}


// Example method that sets a set of data from data received as an instruction. 
void setValues(int data[], int num_data){
  // It is important to verify the size of your instruction. 
  if(num_data != data_set_size){ Serial.println("Invalid number of data values."); return; }     
  for(int i=0; i<data_set_size; i++){ data_set[i] = data[i]; } 
}


// Example method that sends the set of current values as an instruction, using "values" as the instructionID.
void getValues(){ serial_com.sendInstruction(serial_com.makeInstruction("values", data_set, data_set_size)); }


// When an instruction is received it is sent to the instruction interpreter where it will
// be parsed to determine the instructionID and arguments. If the instruction is valid, the 
// instructionID will be used to determine which branch to execute. 
//
// This function is declared as virtual which allows it to be defined in this file. This allows 
// the instruction interpreter to execute public methods of global objects. For example, an object 
// can be designed to interface a piece of hardware. The instruction interpreter can execute 
// a method to set the pins of this piece of hardware through the object.  
void Serial_COM::instructionInterpreter(String input){
  int instr_size = getSize(input); // instr_size = 1 instrID + num(data)
  if(instr_size == -1){ return;}   // invalid instruction, invalid number of data. 

  // At this point, cannot be certain that the input is a valid instruction. 
  // Must extract instructionID and data members to validate instruction.
       
  // Extracting instruction ID and instruction arguments
  String parsed_instr[instr_size];
  parseInstruction(input, parsed_instr, instr_size, " "); 
  String instructionID = parsed_instr[0]; 

  // At this point, the input has been parsed into tokens and stored in parsed_instr. 
  // Still cannot be certain of a valid instruction until the decision structure executing 
  // instruction methods recognizes an instructionID. 

  int num_data = instr_size-1; // subtracting instructionID
  int data[num_data]; 

  if(instr_size > 1){ extractIntData(parsed_instr, data, instr_size); }

  // At this point, if the input is a valid instruction the decision structure below 
  // will execute based upon the instructionID. 

  // Executing based on instructionID.
       if(instructionID == "setValues"){ setValues(data, num_data); }
  else if(instructionID == "getValues"){ getValues();               }
  else{ Serial.print("Sending back: "); Serial.println(input);      }
}
