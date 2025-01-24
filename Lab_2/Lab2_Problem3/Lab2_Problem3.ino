// ENCE 3210 - Microprocessor Systems 1
// Lab 2 - Problem 3
// By Rana Seif
//
// This code acts as a calculator (1press ==> Addition | 2presses ==> Subtraction | 3presses ==> Multiplication)
// And accordingly apply the calculation onto Array1 and Array2

// Define LED light pins using macros
# define RED_LED 3
# define GREEN_LED 4
# define BLUE_LED 5

// Define Button pins using macros
# define BUTTON_1 2
# define BUTTON_2 3

// Defines Array size using a macro
# define ARRAY_SIZE 10

// Declares and initializes the three global arrays (both inputs and the output) 
int gArray1[ARRAY_SIZE] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
int gArray2[ARRAY_SIZE] = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
signed int gResultsArray[ARRAY_SIZE] = {0};

// Declares and initializes the counter that will use button1 presses to identify the correct operation to apply
// And the flag that triggers the button2 press response
int gOperationCounter = 0;
int gButton2Flag = 0;

void setup() 
{
  
  // Sets up Serial Communication
  Serial.begin(9600);

  // Initializes I/Os
  pinMode(RED_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);
  pinMode(BLUE_LED, OUTPUT);

  // Pullup insures the button is only triggered when needed and not randomly
  pinMode(BUTTON_1, INPUT_PULLUP);
  pinMode(BUTTON_2, INPUT_PULLUP);

  // Attaches 2 interrupts to detect button 1 and button 2 presses
  attachInterrupt(digitalPinToInterrupt(BUTTON_1), isr_button_1, CHANGE);
  attachInterrupt(digitalPinToInterrupt(BUTTON_2), isr_button_2, CHANGE);

}

void loop() 
{
  // This is the main loop that applies the ledControl and the operationAmplifier based on button 1 and 2 presses

  if(gOperationCounter == 1 || gOperationCounter == 2 || gOperationCounter == 3)
  {
    ledControl(gOperationCounter);
  }

  // If button2 is pressed, the operation is applied to arrays
  if(gButton2Flag == 1)
  {
    gButton2Flag == 0;
    operationApplier(gOperationCounter);
    Serial.println("Results Array is:");
    for (int i=0; i<ARRAY_SIZE; i++)
    {
      Serial.println(gResultsArray[i]);   // Prints resultant array
    }  
  }

}

void isr_button_1()
{
  // Attend to Button1 press (Interrupt)
  gOperationCounter++;
}

void isr_button_2()
{
  // Attend to Button2 press (Interrupt)
  gButton2Flag = 1;
}

void operationApplier(int operationCounter)
{
  // This function uses the operationCounter to apply the required operation to the first 2 values, turing off all LEDs, 
  // applying operation to rest of array then turning on all LEDs

  gButton2Flag = 0;     // Resets Flag to prepare for next button press
  if (operationCounter == 1)
  {
    for (int i=0; i<3; i++)
    {
      gResultsArray[i] = gArray1[i]+gArray2[i];
    }

    digitalWrite(RED_LED, LOW);
    digitalWrite(GREEN_LED, LOW);
    digitalWrite(BLUE_LED, LOW);
    delay (500);

    for (int i=3; i<ARRAY_SIZE; i++)
    {
      gResultsArray[i] = gArray1[i]+gArray2[i];
    }

    digitalWrite(RED_LED, HIGH);
    digitalWrite(GREEN_LED, HIGH);
    digitalWrite(BLUE_LED, HIGH);
    delay (500);
    gOperationCounter = 0;

  }

  else if(operationCounter == 2)
  {
    for (int i=0; i<3; i++)
    {
      gResultsArray[i] = gArray1[i]-gArray2[i];
    }

    digitalWrite(RED_LED, LOW);
    digitalWrite(GREEN_LED, LOW);
    digitalWrite(BLUE_LED, LOW);
    delay (500);

    for (int i=3; i<ARRAY_SIZE; i++)
    {
      gResultsArray[i] = gArray1[i]-gArray2[i];
    }

    digitalWrite(RED_LED, HIGH);
    digitalWrite(GREEN_LED, HIGH);
    digitalWrite(BLUE_LED, HIGH); 
    gOperationCounter = 0;  
  }

  else if(operationCounter == 3)
  {
    for (int i=0; i<3; i++)
    {
      gResultsArray[i] = gArray1[i]*gArray2[i];
    }

    digitalWrite(RED_LED, LOW);
    digitalWrite(GREEN_LED, LOW);
    digitalWrite(BLUE_LED, LOW);
    delay(500);

    for (int i=3; i<ARRAY_SIZE; i++)
    {
      gResultsArray[i] = gArray1[i]*gArray2[i];
    }

    digitalWrite(RED_LED, HIGH);
    digitalWrite(GREEN_LED, HIGH);
    digitalWrite(BLUE_LED, HIGH);
    gOperationCounter = 0; 
  }
}

void ledControl (int operationCounter)
{
  // Function takes an integer for operation counter as a parameter 
  // and turns on correct light accordingly

  // If statements check for correct light to turn on (1 for Red, 2 for Green and 3 for Blue) 
  if (operationCounter == 1)
  {
    digitalWrite(RED_LED, HIGH);
    delay(500);
    digitalWrite(RED_LED, LOW);
  }

  else if(operationCounter == 2)
  {
    digitalWrite(GREEN_LED, HIGH);
    delay(500);
    digitalWrite(GREEN_LED, LOW);
  }

  else if(operationCounter == 3)
  {
    digitalWrite(BLUE_LED, HIGH);
    delay(500);
    digitalWrite(BLUE_LED, LOW); 
  }
}
