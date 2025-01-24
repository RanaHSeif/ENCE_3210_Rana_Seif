// ENCE 3210 - Microprocessor Systems 1
// Lab 2 - Problem 4
// By Rana Seif
//
// This code uses input array x to calculate array y when button is pressed

// Define LED light pins using macros
# define RED_LED 3
# define GREEN_LED 4
# define BLUE_LED 5

// Define Button pins using macros
# define BUTTON 2

// Defines Array size using a macro
# define ARRAY_SIZE 10

// Declares and initializes the global arrays (both input and output) 
int gXArray[ARRAY_SIZE] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
signed int gYArray[ARRAY_SIZE] = {0};

// Declares Flag to determine if button is presses
int gButtonFlag = 0;

void setup() 
{
  // Sets Up Serial Communication
  Serial.begin(9600);

  // Initializes I/Os
  pinMode(RED_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);
  pinMode(BLUE_LED, OUTPUT);

  // Pullup insures the button is only triggered when needed and not randomly
  pinMode(BUTTON, INPUT_PULLUP);

  // Attaches interrupt to handle button presses
  attachInterrupt(digitalPinToInterrupt(BUTTON), isr_button_1, CHANGE);

}

void loop() 
{
  // Main loop that calculates YArray if button was pressed
  if(gButtonFlag == 1)
  {
    gButtonFlag = 0;      // Resets Flag to prepare for next button press
    for (int i=1; i<ARRAY_SIZE; i++)
    {
      gYArray[i]=2*gXArray[i]*gXArray[i-1];
    }
  }

}

void isr_button_1()
{
  // Attend to Button press (Interrupt)
  gButtonFlag = 1;
}
