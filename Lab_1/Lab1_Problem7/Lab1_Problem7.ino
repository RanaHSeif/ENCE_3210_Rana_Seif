// ENCE 3210 - Microprocessor Systems 1
// Lab 1 - Problem 7
// By Rana Seif
// This code acts as a basic calculator that adds, subtracts or multiplies 10 sets of numbers.
// It uses two buttons: 
// Button1 to determine what operation will be done and creates an LED output
// Button2 to trigger the application of the operation.

// Define LED light pins using macros
# define RED_LED 4
# define GREEN_LED 5
# define BLUE_LED 6

// Define Button pins using macros
# define BUTTON1 7
# define BUTTON2 8

// Defines Array size using a macro
# define ARRAY_SIZE 10

// Declares and initializes the three global arrays (both inputs and the output) 
int gArray1[ARRAY_SIZE] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
int gArray2[ARRAY_SIZE] = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
int gResultsArray[ARRAY_SIZE] = {0};

// Declares and initializes the counter that will use button1 presses to identify the correct operation to apply
int gOperationCounter = 0;

void operationApplier(int operationCounter)
{
  // Function takes an integer for operation counter as a parameter 
  // and changes output array accordingly

  // If statements check for correct operation (1 for addition, 2 for subtraction and 3 for multiplication) 
  // and applies operation
  if (operationCounter == 1)
  {
    for (int i=0; i<ARRAY_SIZE; i++)
    {
      gResultsArray[i] = gArray1[i]+gArray2[i];
    }
  }

  else if(operationCounter == 2)
  {
    for (int i=0; i<ARRAY_SIZE; i++)
    {
      gResultsArray[i] = gArray1[i]-gArray2[i];
    }    
  }

  else if(operationCounter == 3)
  {
    for (int i=0; i<ARRAY_SIZE; i++)
    {
      gResultsArray[i] = gArray1[i]*gArray2[i];
    }    
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


void setup() 
{

  // Initialize LED pins as Outputs
  pinMode(RED_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);
  pinMode(BLUE_LED, OUTPUT);

  // Initialize button pin as input with pull-up resistor to prevent button errors
  pinMode(BUTTON1, INPUT_PULLUP);
  pinMode(BUTTON2, INPUT_PULLUP);

}

void loop() 
{
  // Resets counter to 0 at beginning of loop
  gOperationCounter = 0;

  // for loop with three iterations to check how many times out of 3 button is pressed 
  // Result is then stored in gOperationCounter
  for(int i=0; i<3; i++)
  {
    gOperationCounter = gOperationCounter + digitalRead(BUTTON1);
  }

  // Calls LedControl function to turn on correct LED for the button presses
  ledControl(gOperationCounter);
  
  // If second button is pressed, the operationApplier function is called to fill gResultsArray.
  if(digitalRead(BUTTON2) == 1)
  {
    operationApplier(gOperationCounter);
  }
}
