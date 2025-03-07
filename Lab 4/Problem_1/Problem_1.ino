// Microprocessors I - Lab 4 - Problem 1
// Code written by: Rana Seif
// Converts several values from Analog to Digital and then prints that quatized value.

#define BITSIZE 14

float gVref = 3;
float gVin [4] = [0.42, 0.83, 1.65, 2.752];
float gThresh;

float gQuantized [4] = 0;


void setup() {

  gVref /= 2;
  gThresh = gVref;
  Serial.begin(9600);

}

void loop() {
  // put infinite loop here (replaces while(1) in original code):

  int count;
  int bits[BITSIZE];
  int bitVal;
  
  for (i=0; i<4 ; i++)
  {
    for(count=0; count<BITSIZE; count++)
    {
      gVref /= 2;
      if(gVin[i]>=gThresh)
      {
        gThresh += gVref;
        bits[count] = 1;
        gQuantized[i] += 2*gVref;
      }
      else
      {
        gThresh -= gVref;
        bits[count] = 0;
      }

    }
    Serial.print("\nQuantized Voltage is: ");
    Serial.print(gQuantized[i]);
    Serialprint(" for Vin: ");
    Serial.println(gVin[i]);   
  }
}
