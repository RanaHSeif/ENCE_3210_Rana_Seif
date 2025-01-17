// ENCE 3210 - Microprocessor Systems 1
// Lab 1 - Problem 1
// By Rana Seif
// This code contains a function that calculates twice the square of an integer
// Then uses that function to calculate that value for numbers from 0 to 511 and stores them in an array

// Creates a macro for array size
#define ARRAY_SIZE 512

int gTwice_Square_Array[ARRAY_SIZE] = {0};  // Declares and initializes array

int twice_Square(int value) 
{ 
  // Receives an integer value as a parameter
  // function then returns the value of twice the square of an integer
  return 2*value*value;   
}

void setup() 
{
  // Sets up serial communication
  Serial.begin(9600);

  for (int i=0; i<ARRAY_SIZE; i++) {

    //Iterates from 0 to 511 with increments of 1

    gTwice_Square_Array[i] = twice_Square(i);  // Assigns value of returned twice of square to array teerm
    Serial.print(i);                          // Prints input integer
    Serial.print(":");                        
    Serial.println(gTwice_Square_Array[i]);    // Prints corresponding array term
  }

}

void loop() {
}