// ENCE 3210 - Microprocessor Systems 1
// Lab 1 - Problem 6
// By Rana Seif
// In this code, when a button is pressed, a specific sequence of lights turns on 
// and keeps repeating until the button is pressed again 


// Define pins for LEDs using macros
# define RED_LED 3
# define GREEN_LED 5
# define BLUE_LED 6

// Define pin for button using macros
# define BUTTON 2

// Global variable (Flag) to track button presses
int gButtonPressFlag = 0;

void ledSequence () 
{
  // Runs through the sequence of LED lights (R-RG-RGB-GB-B-RB)
  digitalWrite(RED_LED, HIGH);
  delay(500);
  digitalWrite(RED_LED, LOW);
  delay(100);

  digitalWrite(RED_LED, HIGH);
  digitalWrite(GREEN_LED, HIGH);
  delay(500);
  digitalWrite(RED_LED, LOW);  
  digitalWrite(GREEN_LED, LOW);
  delay(100);

  digitalWrite(RED_LED, HIGH);
  digitalWrite(GREEN_LED, HIGH);
  digitalWrite(BLUE_LED, HIGH);
  delay(500);
  digitalWrite(RED_LED, LOW);  
  digitalWrite(GREEN_LED, LOW);
  digitalWrite(BLUE_LED, LOW);
  delay(100);

  digitalWrite(GREEN_LED, HIGH);
  digitalWrite(BLUE_LED, HIGH);
  delay(500);
  digitalWrite(GREEN_LED, LOW);
  digitalWrite(BLUE_LED, LOW);
  delay(100);

  digitalWrite(BLUE_LED, HIGH);
  delay(500);
  digitalWrite(BLUE_LED, LOW);
  delay(100);

  digitalWrite(RED_LED, HIGH);
  digitalWrite(BLUE_LED, HIGH);
  delay(500);
  digitalWrite(RED_LED, LOW);
  digitalWrite(BLUE_LED, LOW);
  delay(100);

}

void setup() 
{
  // Initialize LED pins as outputs
  pinMode(RED_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);
  pinMode(BLUE_LED, OUTPUT);

  // Initialize button pin as input with pull-up resistor to prevent button errors
  pinMode(BUTTON, INPUT_PULLUP);

}

void loop() 
{
  // In this main function, the button is read and accordingly the sequence is played

  // Read the button state
  gButtonPressFlag = digitalRead(BUTTON);

  if (gButtonPressFlag == 1) 
  {
    // First button press causes start of playing LED Sequence
    ledSequence();
    gButtonPressFlag = digitalRead(BUTTON);  
    while (gButtonPressFlag == 0)
    {
      // Keeps playing the sequence until button is pressed again
      ledSequence();
      gButtonPressFlag = digitalRead(BUTTON);     
    }
  }
}