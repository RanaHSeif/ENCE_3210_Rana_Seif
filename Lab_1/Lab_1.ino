#define LED_PIN 13
#define PORTB5 0x20

// Data Direction Register for Port B
#define myDDRB (*(volatile uint8_t*) 0x24)

// Data Register for Port B
#define myPORTB (*(volatile uint8_t*) 0x25)

void setup() {
  // put your setup code here, to run once:
  // pinMode(LED_PIN, OUTPUT);
  myDDRB |= PORTB5; 

}

void loop() {
  // put your main code here, to run repeatedly:

  //digitalWrite(LED_PIN, HIGH);

  myDDRB |= PORTB5; // Changing bit 5 on myDDRB (Pin Direction) to 1 (Replaces commented line below)
  delay(500);
  
  //digitalWrite(LED_PIN, LOW);  (Replaces commented line below)
  myDDRB &= ~PORTB5;
  delay(500);


}
