// ENCE 3210 - Microprocessor Systems 1
// Lab 1 - Problem 5
// By Rana Seif
// This code detects a specified pattern of 3 values within an array and counts the number of occurances.
// If the pattern is detected, green light flashes, and if not the red light turns on at the very end of the program.

// Declaring macros for the led pins
#define GREEN_LED 7 // Pin for the green LED
#define RED_LED 8   // Pin for the red LED

// Declaring macros for the array sizes (preset in this code).
#define ARRAY_SIZE 9      // Size of the array that you are seaching through
#define PATTERN_SIZE 3    // Size of the array containng the pattern

int gArray[] = {1, 1, 2, 3, 4, 1, 2, 3, 5}; // Input array initialization
int gPattern[] = {1, 2, 3};                 // Pattern array initialization
int gCorrectPatternCount = 0;               // Global Variable to declare the number of times the pattern is detected

int arraySweep(int gArray[], int gPattern[]) {
  // This functioln sweeps through the values in the array to locate the pattern

  int arrayCounter = 0;     // Declares and initializes a local counter variable to be used in for loop.
  gCorrectPatternCount = 0; // Resets global variable for Count everytime the function is called

  for (int arrayCounter = 0; arrayCounter <= (ARRAY_SIZE - PATTERN_SIZE); arrayCounter++) {
    if (gArray[gCorrectPatternCount] == gPattern[1])          // Checks for first value of the pattern
    {
      if (gArray[gCorrectPatternCount + 1] == gPattern[2])    // Checks for second value of the pattern
      {
        if (gArray[gCorrectPatternCount + 2] == gPattern[3])  // Checks for third value of the pattern
        {
          gCorrectPatternCount++;           // Increments counter by 1 if full pattern is detected
          digitalWrite(GREEN_LED, HIGH);    // Turns on Green LED
          delay(500);                       // Waits for 0.5s
          digitalWrite(GREEN_LED, LOW);     // Turns off Green LED     
        }
      }
    }
  }
}

void setup() 
{
  // Initialize LED pins as output
  pinMode(GREEN_LED, OUTPUT);
  pinMode(RED_LED, OUTPUT);

  // Sets serial communication
  Serial.begin(9600);

  // Count occurrences of the pattern in the preset array gArray
  int gCorrectPatternCount = arraySweep(gArray, gPattern);

  // Display the result on Serial Monitor
  Serial.print("Number of occurrences of the pattern: ");
  Serial.println(gCorrectPatternCount);

  if (gCorrectPatternCount == 0)  // If no pattern is detected, Red LED is turned on for 0.5s
  {
    digitalWrite(RED_LED, HIGH);
    delay(500);
    digitalWrite(RED_LED, LOW);
  }
}

void loop() {
    // Nothing to do in the loop for this program
}


