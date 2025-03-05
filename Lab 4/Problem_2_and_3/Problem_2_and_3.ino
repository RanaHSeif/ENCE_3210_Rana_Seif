// Microprocessors I - Lab 4 - Problem 2 and 3 combined
// Code written by: Rana Seif
// This problem implements a power switching system based on the voltages received from the solar panel and the battery
// Due to the lack of an atual power-switching component, the OLED screen was used to indicate the power connections

#define SOLARPANEL_POT A0
#define BATTERY A1

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
// The pins for I2C are defined by the Wire-library. 
// On an arduino UNO:       A4(SDA), A5(SCL)
// On an arduino MEGA 2560: 20(SDA), 21(SCL)
// On an arduino LEONARDO:   2(SDA),  3(SCL), ...
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void setup() {
  Serial.begin(9600);

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
  
}

void loop() {
  display.clearDisplay();

  float solarPanel = analogRead(SOLARPANEL_POT);
  float battery = analogRead(BATTERY);
  char charging = 0;       // 0-->Not charging | 1-->Charging
  char powerState = 1;     // 1-->Battery to system | 2-->SolarPanel to system | 3-->SolarPanel to battery

  display.setTextColor(SSD1306_WHITE);
  if (solarPanel > battery || 1 == charging)
  {
    if (1024 > battery)
    {
      charging = 0;   // Indicates charging is done
    }
    display.setTextSize(1); //Draw 1X-scale text
    display.setCursor(10,0);
    display.print("Solar Panel to Battery");
  }
  else if (solarPanel<512){    // The max value for analogRead is 1024. 1024/2 = 512 is the equivalent of 5V/2=2.5V
    display.setTextSize(1); //Draw 1X-scale text
    display.setCursor(10,0);
    display.print("Battery to System");
  }
  else if (battery>512){
    display.setTextSize(1); //Draw 1X-scale text
    display.setCursor(10,0);
    display.print("Solar Panel to System");
  }

  display.display();
  delay(100);
}

