// Rana Seif
// ENCE 3210 - Lab 3

// Defining Values for RED_LED, GREEN_LED, BUTTON and Timer Compare values as macros

# define RED_LED 5
# define GREEN_LED 4
# define BUTTON 2

#define TIMER1COMPARE 62500     // 16MHz/256*1Hz
#define TIMER2COMPARE 156       // 16MHz/(1024*100Hz) --> Prescaler is now maxed out, so this Timer is then run 10 times to get 10Hz

// Defining the Flags and Counters as Volatile Global Variables 
volatile unsigned int gISRFlag1 = 0;
volatile unsigned int gISRFlag2 = 0;
volatile unsigned int gTimerRepeatCount = 0;  // Counts Number of times Timer 2 was repeated
unsigned int gTimeCounter = 0;                // Keeps count of time in seconds in Timer 1

void setup() {

  // initializes pins for Red LED, Green LED as Output and button as Input  
  pinMode(RED_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);
  pinMode(BUTTON, INPUT);

  Serial.begin(9600);   // Initialize serial communication

  // Initialize First Timer at 1Hz (Uses 1Hz Counter)
  TCCR1A = 0;                   // Resets Timer1 Control Register A to begin with
  TCCR1B = 0;                   // Resets Timer1 Control Register B to begin with
  OCR1A = TIMER1COMPARE;        // Set Timer Compare to 62500 to be able to reset at 1s to achieve 1Hz frequency
  TCCR1B |= (1 << WGM12);       // CTC mode
  TCCR1B |= (1 << CS12);        // Set prescaler to 256
  TIMSK1 |= (1 << OCIE1A);      // Enable Timer1 compare interrupt

  // Initialize Timer2 (100 Hz for button state checking)
  // The button state will be slowed down using a global counter
  TCCR2A = 0;                   // Resets Timer2 Control Register A to begin with
  TCCR2B = 0;                   // Resets Timer2 Control Register B to begin with
  OCR2A = TIMER2COMPARE;        // Set Timer Compare to 156
  TCCR2A |= (1 << WGM21);       // CTC mode
  
  // Set prescaler to 1024
  TCCR2B |= (1 << CS22);        
  TCCR2B |= (1 << CS21);
  TCCR2B |= (1 << CS20);
  TIMSK2 |= (1 << OCIE2A);      // Enable Timer2 compare interrupt
}

void loop() {
  // put your main code here, to run repeatedly:
  if(gISRFlag1)   // Checks Flag for Timer 1
  {
    // Blinks LED
    digitalWrite(GREEN_LED, HIGH);
    delay(50);
    digitalWrite(GREEN_LED, LOW);

    gISRFlag1 = 0;      // Resets Timer 1 Flag
    
    if(gTimeCounter == 3)   // Checks for every 3 seconds
    {
      Serial.println("Music is awesome!");
      gTimeCounter = 0;     // Resets 3Second counter
    }
  }

  if(gISRFlag2)   //Checks Flag for Timer 2
  {
    // Increments Timer 2 Repeat Counter 
    gTimerRepeatCount++;
    if (gTimerRepeatCount == 10)    // If Counter is 10 (at 10Hz), turn on Red LED
    {
      digitalWrite(RED_LED, HIGH);
      gISRFlag2 = 0;            // Resets Timer 2 Flag
      gTimerRepeatCount = 0;    // Rests Repeat Counter
    }
  }
  else      // Turn off Red LED if Button is not pressed
  {
    digitalWrite(RED_LED, LOW);
  }

}

ISR(TIMER1_COMPA_vect) // Timer1 ISR (1 Hz)
{
  gISRFlag1 = 1;    // Set flag for the main loop
  gTimeCounter++;   // Increments Time counter to count to 3
}

ISR(TIMER2_COMPA_vect) // Timer2 ISR (100 Hz)
{
  if(digitalRead(BUTTON))
  {
    gISRFlag2 = 1; // Set flag for the main loop
  }

}
