// ENCE 3210 - Microprocessor Systems 1
// Lab 1 - Problem 4
// By Rana Seif
// This code finds the letters R,  G and B in an array and turns on the associated LED light.
// It also counts the number of times R, G and B are each detected.

// Define the size of the array as a macro
#define ARRAY_SIZE 50

// Define the pins for the LEDs as Macros
#define RED_LED 7
#define GREEN_LED 6
#define BLUE_LED 5

// Global array with 50 characters previously assigned
char gcharArray[ARRAY_SIZE] = {'R', 'A', 'G', 'B', 'R', 'B', 'G', 'R', 'R', 'G', 'B', 'A', 'C', 'G', 'R', 'B', 'G', 'B', 'A', 'R',
                              'G', 'B', 'R', 'G', 'B', 'A', 'R', 'G', 'B', 'R', 'A', 'C', 'R', 'B', 'G', 'R', 'B', 'G', 'B', 'R',
                              'R', 'G', 'A', 'B', 'C', 'R', 'G', 'B', 'R', 'G'};

// Global variables to count the occurrences of R, G, and B
int gcountR = 0;
int gcountG = 0;
int gcountB = 0;

// Function to count the occurrences and control LEDs
void letter_Read() 
{
  // This function reads letters in the array and turns on corretc lights.

  gcountR = 0;    // Initializes counts for red here
  gcountG = 0;    // Initializes counts for green here
  gcountB = 0;    // Initializes counts for blue here

  // Iterate through the array
  for (int i = 0; i < ARRAY_SIZE; i++) 
  {
    if (gcharArray[i] == 'R') 
    {
      digitalWrite(RED_LED, HIGH);    // Turns on Red LED
      gcountR++;                      // Adds one to Red counter
      delay(500);                     // Waits half a second
      digitalWrite(RED_LED, LOW);     // Turns off Red LED
      Serial.print("RED Flashes");
    } 

    else if (gcharArray[i] == 'G') 
    {
      digitalWrite(GREEN_LED, HIGH);  // Turns on Green LED
      gcountG++;                      // Adds one to Green counter
      delay(500);                     // Waits half a second
      digitalWrite(GREEN_LED, LOW);   // Turns off Green LED
      Serial.print("GREEN Flashes");
    } 

    else if (gcharArray[i] == 'B') 
    {
      digitalWrite(BLUE_LED, HIGH);   // Turns on Blue LED
      gcountB++;                      // Adds one to Blue counter
      delay(500);                     // Waits half a second
      digitalWrite(BLUE_LED, LOW);    // Turns off Blue LED
      Serial.print("BLUE Flashes");
    }
  }
}

void setup() 
{
    // Initialize the LED pins as outputs
    pinMode(RED_LED, OUTPUT);
    pinMode(GREEN_LED, OUTPUT);
    pinMode(BLUE_LED, OUTPUT);

    // Initialize serial communication
    Serial.begin(9600);

    // Calls function Read letters in the array and control LEDs and count accordingly
    letter_Read();

    // Print the counts for debugging
    Serial.print("Count of R: ");
    Serial.println(gcountR);
    Serial.print("Count of G: ");
    Serial.println(gcountG);
    Serial.print("Count of B: ");
    Serial.println(gcountB);
}

void loop() {

}
