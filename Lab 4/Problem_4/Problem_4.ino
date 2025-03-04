// Microprocessors I - Lab 4 - Problem 4
// Code written by: Rana Seif

#define TEMP_SENSOR A0  // Analog pin for temperature sensor
#define FAN_LEVEL 9       // PWM pin for fan (LED simulation)
#define ONOFF_BUTTON 2       // Button 1: Fan ON/OFF (INT0)
#define FAN_SENSITIVITY_BUTTON 3       // Button 2: Sensitivity control (INT1)

#define TIMER_COMPARE_VALUE 25000;     // (16MHz*0.05s)/64 = 25000

volatile float gTempTotal = 0;   // Sum of temperature readings
volatile unsigned int gSampleCount = 0;// Number of samples taken
float gAverageTemperature = 0.0; // Stored average temperature

volatile char gSensitivityIndicator = 1; // Sensitivity level (1-3)
volatile unsigned int gFanOnFlag = 0;    // Fan ON/OFF state

void setup() {
  pinMode(FAN_LEVEL, OUTPUT);
  pinMode(ONOFF_BUTTON, INPUT);
  pinMode(FAN_SENSITIVITY_BUTTON, INPUT);
  
  Serial.begin(9600); // Debugging output

  TCCR1A = 0;                             // Resets Timer1 Control Register A to begin with
  TCCR1B = 0;                             // Resets Timer1 Control Register B to begin with
  OCR1A = TIMER_COMPARE_VALUE;            // Set Timer Compare value to 25000 to trigger every 0.05s (100 times every 5s)
  TCCR1B |= (1 << WGM12);                 // CTC mode
  TCCR1B |= (1 << CS11) | (1 << CS10);    // Set prescaler to 64
  TIMSK1 |= (1 << OCIE1A);                // Enable Timer1 compare interrupt

  // Attach button interrupts
  attachInterrupt(digitalPinToInterrupt(ONOFF_BUTTON), isr_button_1, CHANGE);
  attachInterrupt(digitalPinToInterrupt(FAN_SENSITIVITY_BUTTON), isr_button_2, CHANGE);
}

void loop() {
  // Check if 100 samples collected (every 5 seconds)
  if (gSampleCount >= 100) {
    gAverageTemperature = gTempTotal / 100.0;
    gTempTotal = 0;  // Reset sum
    gSampleCount = 0;  // Reset count
    Serial.print("Avg Temperature: ");
    Serial.println(gAverageTemperature);
  }

  // Compute and set fan speed
  int fanSpeed = (gAverageTemperature/32767) * 255;     // pwm is a value out of 255 while gAverageTemperature is a 16-bit int
  if (gFanOnFlag) {
    analogWrite(FAN_LEVEL, fanSpeed);
  } 
  else {
    analogWrite(FAN_LEVEL, 0);  // Fan OFF
  }

  delay(100);
}

// Timer1 ISR - Runs every 50ms (20Hz sample rate)
ISR(TIMER1_COMPA_vect) {
  gTempTotal += analogRead(TEMP_SENSOR);
  gSampleCount++;
}

// Interrupt Service Routine for Button 1 (Toggle Fan ON/OFF)
void isr_button_1() {
  gFanOnFlag = !gFanOnFlag;
}

// Interrupt Service Routine for Button 2 (Change Sensitivity)
void isr_button_2() 
{
  gSensitivityIndicator = (gSensitivityIndicator % 3) + 1;
}
