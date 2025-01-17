// ENCE 3210 - Microprocessor Systems 1
// Lab 1 - Problem 3
// By Rana Seif
// This code searches for the second maximum of a given integer array with 50 elements 
// and writes the result in the memory location right after the array.

// Define the size of the array
#define ARRAY_SIZE 50

// Global array with 50 elements
unsigned int gdataArray[ARRAY_SIZE];

// Declares a variable called memory pointer to store pointer location
int *memoryPointer = 0;

// Function to find the second maximum value
void findSecondMaximum() 
{
  // Initialize local variables for 1st max and 2nd max
  unsigned int max1;
  unsigned int max2;

  // Iterate through the array to find the largest and second largest values
  for (int i = 0; i < ARRAY_SIZE; i++) 
  {
    if (gdataArray[i] > max1) 
    {     
      //If it is largest value so far
      max2 = max1;
      max1 = gdataArray[i];
    } 

    else if (gdataArray[i] > max2 && gdataArray[i] < max1) 
    { 
      // If it is second largest so far
        max2 = gdataArray[i];
    }
  }

  Serial.println(max2);     //Displays max2 in serial monitor

  // Assigns the memoryPointer variable the location just after the array
  memoryPointer = gdataArray + 50;
  // Places the second max in the memory location right after the array
  *memoryPointer = max2;
}

void setup() {
  // Initialize serial communication
  Serial.begin(9600);

  // Fills gdataArray with integers
  for (int i=0; i<ARRAY_SIZE; i++) 
  {
    gdataArray[i] = i;
  }

    // Calls the function to find the second maximum, store it in the correct place and display it
    findSecondMaximum();
}

void loop() {

}