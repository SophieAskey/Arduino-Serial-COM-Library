# Arduino-Serial-COM-Library 
<h3> Description </h3>

The Serial_COM class is a library designed to send and receive string instructions via serial communication. When serial input is received, it is passed into the instructionInterpreter which parses and executes instructions. 

An instruction is made up of an instructionID followed by data values, each seperated by a delimiter, ex: white spaces " ".  
Ex: "instrID 1 2 3". The instruction intepreter parses the serial input by attempting to extract the instructionID and data members.

The makeInstruction method is used to create instructions by passing in an instructionID, array of data members (only string and int overloaded methods implemented) and a delimiter. The string array makeInstruction method can be used as the generic method to send instructions of various data types by casting the array of members into a string array. 

The instructionInterpreter must be implemented by the user. However, the methods for extracting the instructionID and data members have already been implemented. An example of instructionInterpreter implementation has been provided in driver.ino.

As of now, there is only an extractIntData method to extract int data from serial input. However, an extractFloatMethod can be make by simply copying extractIntData and changing .toInt() to .toFloat().
