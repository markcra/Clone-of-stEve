// define some global variables
const int statusLED = 13; // an LED for simple feedback
const int piezoSounder = 3; // a buzzer if we need audible feedback

int motor1Pins[] = {4, 5, 6, 7}; // an array holding the pin numbers for the first motor
int motor2Pins[] = {8, 9, 10, 11}; // a separate array for the second motors pins

void setup()
{
  // Setup Output Pins (all pins start as inputs by default)
  pinMode(statusLED, OUTPUT);
  pinMode(piezoSounder, OUTPUT);
  for (int i=0; i<4; i++)
  { 
    pinMode(motor1Pins[i], OUTPUT);
    pinMode(motor2Pins[i], OUTPUT);
  }
}

void loop()
{
  // test your code by using each function in turn or comment out all but the one you're working on
  halfRotationFwdLeft();
  delay(100);
  halfRotationFwdRight();
  delay(100);
  halfRotationFwdBoth();
  delay(100);
  stopMotors();
  delay(500);
}

void stopMotors()
{
  digitalWrite(motor1Pins[0], LOW);
  digitalWrite(motor1Pins[1], LOW);
  digitalWrite(motor1Pins[2], LOW);
  digitalWrite(motor1Pins[3], LOW);
  digitalWrite(motor2Pins[0], LOW);
  digitalWrite(motor2Pins[1], LOW);
  digitalWrite(motor2Pins[2], LOW);
  digitalWrite(motor2Pins[3], LOW);
}

// Develop the following functions. When complete copy them across to the final template.

void halfRotationFwdBoth()
{
  // your code
}

void halfRotationFwdLeft()
{
  // your code
}

void halfRotationFwdRight()
{
  // your code
}