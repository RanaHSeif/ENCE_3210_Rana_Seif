// ENCE 3210 - Microprocessor Systems 1
// Lab 2 - Problem 2
// By Rana Seif
//
// This code uses an interrupt for a button to trigger a particular LED Sequence to play

// Defines LED and BUTTON pin numbers as macros
#define RED_LED 4
#define GREEN_LED 5
#define BLUE_LED 6

#define BUTTON 2

// Sets up a flag that can be used within the interrupt
int gButtonFlag = 0;

void setup() 
{  
  // Sets up Serial Communication
  Serial.begin(9600);

  // Initializes I/Os
  pinMode(RED_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);
  pinMode(BLUE_LED, OUTPUT);

  // Pullup insures the button is only triggered when needed and not randomly
  pinMode(BUTTON, INPUT_PULLUP);

  // attaches an interrupt to handle the button press
  attachInterrupt(digitalPinToInterrupt(BUTTON), isr_button, CHANGE);

}

void loop() 
{

  // This is the main loop where if the button Flag is triggered, the ledSequence function is called to play the sequence

  if (gButtonFlag == 1)
  {
    gButtonFlag = 0;    // Resets the Flag in preparation for the next button press
    ledSequence();      // Calls the ledSequence function
  }
}

void isr_button()
{
  // Attend to Button press (Interrupt)
    gButtonFlag = 1;
}

void ledSequence () 
{
  // This function outlines the code to turn on the LEDs to run through the sequence of LED lights (R-RG-RGB-GB-B-RB)

  digitalWrite(RED_LED, HIGH);
  Serial.println("R");  
  delay(500);
  digitalWrite(RED_LED, LOW);
  delay(100);

  digitalWrite(RED_LED, HIGH);
  digitalWrite(GREEN_LED, HIGH);
  Serial.println("RG");
  delay(500);
  digitalWrite(RED_LED, LOW);  
  digitalWrite(GREEN_LED, LOW);
  delay(100);

  digitalWrite(RED_LED, HIGH);
  digitalWrite(GREEN_LED, HIGH);
  digitalWrite(BLUE_LED, HIGH);
  Serial.println("RGB");
  delay(500);
  digitalWrite(RED_LED, LOW);  
  digitalWrite(GREEN_LED, LOW);
  digitalWrite(BLUE_LED, LOW);
  delay(100);

  digitalWrite(GREEN_LED, HIGH);
  digitalWrite(BLUE_LED, HIGH);
  Serial.println("GB");  
  delay(500);
  digitalWrite(GREEN_LED, LOW);
  digitalWrite(BLUE_LED, LOW);
  delay(100);

  digitalWrite(BLUE_LED, HIGH);
  Serial.println("B");
  delay(500);
  digitalWrite(BLUE_LED, LOW);
  delay(100);

  digitalWrite(RED_LED, HIGH);
  digitalWrite(BLUE_LED, HIGH);
  Serial.println("RB");
  delay(500);
  digitalWrite(RED_LED, LOW);
  digitalWrite(BLUE_LED, LOW);
  delay(100);

}