// ENCE 3210 - Microprocessor Systems 1
// Lab 2 - Problem 1
// By Rana Seif
//
// This Code counts the number of each button presses, compares them and accordingly turns on the correct LED

// defines macros for LEDs and Buttons 
#define RED_LED 4
#define GREEN_LED 5

#define BUTTON_1 2
#define BUTTON_2 3 

// Initialises global variables that count button presses for Button1 and Button2
int gButton1Count = 0;
int gButton2Count = 0;

void setup() 
{
  // Sets up Serial Communication
  Serial.begin(9600);

  // Initializes I/Os
  pinMode(RED_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);

  // Pullup insures the buttons are only triggered when needed and not randomly
  pinMode(BUTTON_1, INPUT_PULLUP);
  pinMode(BUTTON_2, INPUT_PULLUP);

  // Attaches 2 interrupt routines (1 for each button)
  attachInterrupt(digitalPinToInterrupt(BUTTON_1), isr_button_1, CHANGE);
  attachInterrupt(digitalPinToInterrupt(BUTTON_2), isr_button_2, CHANGE);

}

void loop() {

  // This is the main loop where the button counters are compared 

  if (gButton1Count > gButton2Count){
    // For Button1 presses more than button2 presses, Red LED turns on
    digitalWrite(RED_LED, HIGH);
    digitalWrite(GREEN_LED, LOW);
  }
  else if (gButton1Count == gButton2Count){
    // For Button1 presses equal to button2 presses, blue LED turns on
    // Using the provided shield blue is represented by both red and green turning on at the same time
    digitalWrite(RED_LED, HIGH);
    digitalWrite(GREEN_LED, HIGH);
  }
  else if (gButton1Count < gButton2Count){
    // For Button1 presses less than button2 presses, Green LED turns on
    digitalWrite(RED_LED, LOW);
    digitalWrite(GREEN_LED, HIGH);
  }

  // Displays Button Counters
  Serial.println(gButton1Count);
  Serial.println(gButton2Count);

}

void isr_button_1()
{
  // Attend to Button1 press (Interrupt)
    gButton1Count++;
}

void isr_button_2()
{
  // Attend to Button2 press (Interrupt)
    gButton2Count++;
}
