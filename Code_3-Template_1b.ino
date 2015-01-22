// define some global variables
const int statusLED = 13; // an LED for simple feedback
const int piezoSounder = 3; // a buzzer if we need audible feedback

int motor1Pins[] = {4, 5, 6, 7}; // an array holding the pin numbers for the first motor
int motor2Pins[] = {8, 9, 10, 11}; // a separate array for the second motors pins
/*
Reminder:
Arrays are a way of storing sets of data. In our case we want to store the four integers which correspond to the pins where we've connected a stepper motor. 

Above example shows how to define an array but how do you use it? Where you would normally refer to an integer variable you can reference a single element within the array. You do this by putting the index number in square brackets at the end of the array name:
  motor1Pins[index_number]
in context this might be used as:
  digitalWrite(motor1Pins[0], HIGH);
For our arrays we have 4 elements so the index numbers are 0-3 (most programming languages start indexes at zero).
*/

void setup()
{
  // Setup Output Pins (all pins start as inputs by default)
  pinMode(statusLED, OUTPUT);
  pinMode(piezoSounder, OUTPUT);
  for (int i=0; i<4; i++)
  {  /* some notes for those of you that haven't seen a for loop before:
    int i=0; ~ this is the starting point for the counter. You can use a variable that's already declared elsewhere but for this one I made a new variable called i and set it to start at zero. Why? because the array index starts at zero. You could start at 1 or any other number if it suits your purpose.
    i<4; ~ this is the condition. As long as this is TRUE then the for loop keeps on repeating. Why did I pick <4? I have 4 elements in my array, when the counter "i" reaches 4 then the condition i<4 is FALSE and we break out (again, array index starts at zero so we only need the numbers 0, 1, 2 & 3).
    i++ ~ this is just shorthand for adding 1 to the value of i. It's the same as i = i + 1. 
    */
    pinMode(motor1Pins[i], OUTPUT);
    pinMode(motor2Pins[i], OUTPUT);
  }
}

void loop()
{
  // your code
  digitalWrite(motor1Pins[0], HIGH); // pin 4 HIGH, all others LOW for step 0
  digitalWrite(motor1Pins[1], LOW);
  digitalWrite(motor1Pins[2], LOW)
  digitalWrite(motor1Pins[3], LOW);
  delay(50);
  // step 1 then step 2 ... until you reach step 7
}