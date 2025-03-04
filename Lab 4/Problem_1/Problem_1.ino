#define BITSIZE 14

float gVref = 3;
float gVin = 2.752;
float gThresh;

float gQuantized = 0;


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
  
  for(count=0; count<BITSIZE; count++)
  {
    gVref /= 2;
    if(gVin>=gThresh)
    {
      gThresh += gVref;
      bits[count] = 1;
      gQuantized += 2*gVref;
    }
    else
    {
      gThresh -= gVref;
      bits[count] = 0;
    }

  }
  Serial.println("\nQuantized Voltage is: ");
  Serial.print(gQuantized);

}
