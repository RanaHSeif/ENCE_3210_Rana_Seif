


/*********************************************
* LIBRARY INCLUSIONS AND DEFINITIONS FOR MPU *
*********************************************/

// MPU libraries
#include "I2Cdev.h"
#include "MPU6050.h"

// MPU Definitions and Setups

#if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
    #include "Wire.h"
#endif

// class default I2C address is 0x68
MPU6050 accelgyro;

// Declares outputs of MPU6050 as 16 bit integers
int16_t ax, ay, az;   
int16_t gx, gy, gz;

#define OUTPUT_READABLE_ACCELGYRO

/**********************************************
* LIBRARY INCLUSIONS AND DEFINITIONS FOR OLED *
**********************************************/

// OLED libraries
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "Lock_Img_Array.h"
#include "Units_Img_Array.h"

// OLED Definitions and Setups

// Defines Screen Width and Height as Macros
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
// The pins for I2C are defined by the Wire-library. 
// On an arduino UNO:       A4(SDA), A5(SCL)
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

char gRotation = 0;  // Defines Orientation of Screen. O if normal, 2 if 180 degrees (flipped)

/*****************************************************
* LIBRARY INCLUSIONS AND DEFINITIONS FOR TEMP SENSOR *
*****************************************************/

#include <OneWire.h>
#include <DallasTemperature.h>

// Data wire is plugged into port 2 on the Arduino
#define ONE_WIRE_BUS 8

// Setup a oneWire instance to communicate with any OneWire devices (not just Maxim/Dallas temperature ICs)
OneWire oneWire(ONE_WIRE_BUS);

// Pass our oneWire reference to Dallas Temperature.
DallasTemperature sensors(&oneWire);

volatile float gTempC = 0;   // Stores Temperature in Celsius
volatile float gTempF = 0;   // Stores Temperature in Fahreinheit
volatile int gLedStateFlag = 0;
volatile int gTempReadFlag = 0;

/******************
* PIN DEFINITIONS *
******************/

#define LIGHT_BUTTON 13
#define UNITS_BUTTON 5
#define LOCK_BUTTON 3
#define ONOFF_BUTTON 2
#define LED_PIN 9

/******************************
* ENUMERATE STATE DEFINITIONS *
******************************/

// For state of device
enum DeviceStates_e {IDLE_STATE, OFF_STATE};
enum DeviceStates_e gDeviceState;

/************************************
* TIMER 1 and 2 RELATED DEFINITIONS *
************************************/

// 16MHz/256 = 62.5kHz = 16us | Timer 1-->16 bits = 65536
#define TIMER1_COMPARE_VALUE 62500 
// With the 256 prescaler we can get 1s by counting up to 250 and then multiply by 3. 
#define TIMER2_COMPARE_VALUE 250      // gets 4ms  
// Defines Timer 2 Counter Limit to use to reset timer
#define TIMER_COUNTER_MAX 750

volatile int gCounterTimer = 0;     // To count number of times Timer2 runs start to finish

/****************************
* FLAG VARIABLE DEFINITIONS *
****************************/
volatile char gOnOffFlag = 0; // 0 is off, 1 is on
volatile char gLockFlag = 0;  // 0 is locked, 1 is unlocked

char gUnitsFlag = 0;          // 0 is Celsius and 1 is Fahrenheit
char gBacklightFlag = 1;      // 0 is off, 1 is on


void setup() {
  // Init Serial (TMP)
  Serial.begin(38400);

  noInterrupts();  // Disable Interrupts until Setup is Complete

  /***********************************
  * Buttons, LED and Interrupt Setup *
  ***********************************/

  pinMode(LIGHT_BUTTON, INPUT);
  pinMode(UNITS_BUTTON, INPUT);
  pinMode(LOCK_BUTTON, INPUT);
  pinMode(ONOFF_BUTTON, INPUT);
  pinMode(LED_PIN, OUTPUT);

  //Enable External Interrupt
  attachInterrupt(digitalPinToInterrupt(LOCK_BUTTON), isr_lock_button, RISING);
  attachInterrupt(digitalPinToInterrupt(ONOFF_BUTTON), isr_onoff_button, RISING);

  /******************************************
  * Timer 1 (Reading Sensor - 16bits) Setup *
  *******************************************/

  // Speed of Timer 1 = 16MHz/256 = 62.5kHz (16us)
  TCCR1A = 0;                   // Resets Timer1 Control Register A to begin with
  TCCR1B = 0;                   // Resets Timer1 Control Register B to begin with
  OCR1A = TIMER1_COMPARE_VALUE;  // Set Timer Compare to 62500
  TCCR1B |= (1 << WGM12);       // CTC mode
  // Start Timer only when turns on
  //  TCCR1B |= (1 << CS12);        // Set prescaler to 256 
  TIMSK1 |= (1 << OCIE1A);      // Enable Timer1 compare interrupt

  /****************************************
  * Timer 2 (Units and Cal - 8bits) Setup *
  ****************************************/

  // Speed of Timer 1 = 16MHz/256 = 62.5kHz (1.6us)
  TCCR2A = 0;                   // Resets Timer2 Control Register A to begin with
  TCCR2B = 0;                   // Resets Timer2 Control Register B to begin with
  OCR2A = TIMER2_COMPARE_VALUE;  // Set Timer Compare to 250 to be able to reset at 1s to be run 3 times
  TCCR2B |= (1 << WGM21);       // CTC mode
  // TCCR2B |= (1 << CS21) | (1 << CS22);        // Set prescaler to 256  --> Disabled to only start when units or cal buttons are pressed
  TIMSK2 |= (1 << OCIE2A);      // Enable Timer2 compare interrupt

  /************
  * MPU Setup *
  ************/

  // join I2C bus (I2Cdev library doesn't do this automatically)
  #if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
    Wire.begin();
  #elif I2CDEV_IMPLEMENTATION == I2CDEV_BUILTIN_FASTWIRE
    Fastwire::setup(400, true);
  #endif

  // initialize device
  Serial.println("Initializing I2C devices...");
  accelgyro.initialize();

  // verify connection
  Serial.println("Testing device connections...");
  Serial.println(accelgyro.testConnection() ? "MPU6050 connection successful" : "MPU6050 connection failed");
  
  /*************
  * OLED Setup *
  *************/

  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }

  // Show initial display buffer contents on the screen --
  // the library initializes this with an Adafruit splash screen.
  display.display();
  delay(2000); // Pause for 2 seconds

  // Clear the buffer
  display.clearDisplay();

  /********************
  * TEMP SENSOR Setup *
  ********************/
  sensors.begin();

  // Enable Interrupts
  interrupts();

}

void loop() {
  switch(gDeviceState){

    case IDLE_STATE:

      checkButtons();
 
      // Adjusting Orientation based on MPU
      // read raw accel/gyro measurements from device
      accelgyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);

      #ifdef OUTPUT_READABLE_ACCELGYRO
        // display tab-separated accel/gyro x/y/z values
        if (ax < 0){
          gRotation = 2;
        }
        else{
          gRotation = 0;
        }
      #endif
      
      if (gTempReadFlag = 1)
      {
        gTempReadFlag = 0;
        sensors.requestTemperatures();          // Send the command to get temperatures
        gTempC = sensors.getTempCByIndex(0);    // Reads Sensor in Celsius
        gTempF = gTempC*(9.0/5.0) + 32;             // Converts sensor reading to Fahrenheit
      }

      // Displays Lock and Units as defined by Flag
      if (1 == gLockFlag)
      {
        display.drawBitmap(0, 0, lockimages[0], SCREEN_WIDTH, SCREEN_HEIGHT, WHITE);
      }
      else
      {
        display.drawBitmap(0, 0, lockimages[1], SCREEN_WIDTH, SCREEN_HEIGHT, WHITE);
      }

      if (0 == gUnitsFlag)
      {
        display.drawBitmap(0, 0, unitsimages[0], SCREEN_WIDTH, SCREEN_HEIGHT, WHITE);   // Celsius Image
        // Displays Temp Reading in Celsius
        display.setTextColor(SSD1306_WHITE);
        display.setTextSize(1); //Draw 1X-scale text
        display.setCursor(10,0);
        display.print(gTempC);
      }
      else
      {
        display.drawBitmap(0, 0, unitsimages[1], SCREEN_WIDTH, SCREEN_HEIGHT, WHITE);   // Fahrenheit Image
        // Displays Temp Reading in Celsius
        display.setTextColor(SSD1306_WHITE);
        display.setTextSize(1); //Draw 1X-scale text
        display.setCursor(10,0);
        display.print(gTempF);
      }

      // Sets Screen Orientation and Displays Result
      display.setRotation(gRotation);
      display.display();
    break;

    case OFF_STATE:
      digitalWrite(LED_PIN, LOW); // Turn off Backlight LED
      display.clearDisplay();     // Clear OLED
      display.display();
    break;

  }

}

/*****************
* ISR FUNCTIONS *
*****************/
void isr_lock_button()
{
  gLockFlag = !gLockFlag;
  if (1 == gLockFlag)
  {
    // Unlock - Start Timer 1 (Read Sensor)
    TCCR2B |= (1 << CS21) | (1 << CS22);
  }
  else
  {
    // Lock - Stop Timer 1 (Stop Reading Sensor)
    TCCR2B |= (0 << CS21) | (0 << CS22);
  }
}

void isr_onoff_button()
{
  gOnOffFlag = !gOnOffFlag;
  if (1 == gOnOffFlag)
  {
    gDeviceState = IDLE_STATE;
    TCCR1B |= (1 << CS12);      // Start Timer 1 (Start Reading Sensor)
  }
  else
  {
    gDeviceState = OFF_STATE;
    TCCR1B &= ~(1 << CS12);     // Stop Timer1 (Stop Reading Sensor)
  }
}

ISR (TIMER1_COMPA_vect)
{
  gTempReadFlag = 1;
}

ISR (TIMER2_COMPA_vect)
{
  gCounterTimer ++;
  if (gCounterTimer >= TIMER_COUNTER_MAX)
  {
    // Reset Counter when get to limit
    gCounterTimer = 0; 
    if (1 == digitalRead(UNITS_BUTTON))
    {
      gUnitsFlag = !gUnitsFlag;
    }
  }
}

/****************
* AUX FUNCTIONS *
****************/
void checkButtons()
{
  // Check Light Button (CHANGE TO VARIABLE THAT TOGGLES - TODO)
  if (1 == digitalRead(LIGHT_BUTTON))
  {
    delay(50);    // To Debounce
    if (digitalRead(LIGHT_BUTTON) == HIGH) 
    {  
        gLedStateFlag = !gLedStateFlag;  
        digitalWrite(LED_PIN, gLedStateFlag);
    }
  }

  // Check Units Button and enters correct state to change units
  if (1 == digitalRead(UNITS_BUTTON))
  {
    delay (50); // To Debounce
    if(1 == digitalRead(UNITS_BUTTON))
    {
      gCounterTimer = 0; // Reset counter
      TCCR2B |= (1 << CS21) | (1 << CS22);    // Starts Timer
    }
  }
}
