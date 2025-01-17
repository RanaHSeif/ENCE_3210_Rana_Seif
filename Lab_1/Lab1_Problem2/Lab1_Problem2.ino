// ENCE 3210 - Microprocessor Systems 1
// Lab 1 - Problem 2
// By Rana Seif
// This code find the cosine if integer degrees between 0 and 360 and stores the results in an array. 

#include <math.h>        // Adds the math.h library to include mathematical functions
#define ARRAY_SIZE 361   // Creates a Macro for the Size of the Array
float gRadianAngles = 0;  // Declares and Initializes variable to store radian equivalents of angles

float gCosine_angles[ARRAY_SIZE] = {0};  // Declares and initializes Array to store cosine of angles

void setup() 
{
  // sets up serial communication
  Serial.begin(9600);

  // for loop sweeps through integers from 0 to 360 with integer intervals
  for (int i=0; i<ARRAY_SIZE; i++) 
  {
    gRadianAngles = i*M_PI/180;            // Converts Angles from Degrees to Radians
    gCosine_angles[i] = cos(gRadianAngles); // Calculates cosine of angle and places it in correct array term
    Serial.println (gCosine_angles[i]);    // Displays Array term added in serial moniter
  }
}

void loop() {

}