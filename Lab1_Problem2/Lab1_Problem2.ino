#include <math.h>
#define ARRAY_SIZE 361
int j = 0;

float cosine_angles[ARRAY_SIZE] = {0};

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  for (int i=0; i<ARRAY_SIZE; i++) {
    j = i*M_PI/180;
    cosine_angles[i] = cos(j);
    Serial.println (cosine_angles[i]);
  }
}

void loop() {

}