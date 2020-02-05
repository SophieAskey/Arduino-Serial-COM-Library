# Arduino-Serial-COM-Library 

The Serial_COM class is a library designed to send and receive string instructions via Serial communication. When serial input is received, it is passed into the instructionInterpreter which parses and executes instructions. An instruction is made up of an instructionID followed by data values seperated by a delimiter, ex: spaces. Ex: "instrID 1 2 3". The instruction intepreter parses the serial input by attempting to extract the instructionID and data members.
