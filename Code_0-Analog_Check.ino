/* 
Project: Clone of stEve, MAKLab workshop robot
Author: Mark Craig
File: analogcheck
Description:
  Arrange the following components to build a voltage divider which provides a high voltage for a bright environment and low voltage for low light level.
    GND - resistor (1k or so) - Analog Pin - PhotoResistor - 5V
  Two of these voltage dividers are used as the left and right "eyes" of our robot. The left eye is connected to A0, the right eye is connected to A1.
  To test our circuit and get an idea of the values the Arduino will be reading we can use this simple sketch to read the analog pins to a serial terminal on our PC.

*/
const int statusLED = 13;
const int piezoSounder = 3;
int motor1Pins[] = {4, 5, 6, 7};
int motor2Pins[] = {8, 9, 10, 11};

const int minThreshold = 50;
const int differenceThreshold = 10;

void setup() {
  // Setup Output Pins (all pins start as inputs by default)
  pinMode(statusLED, OUTPUT);
  pinMode(piezoSounder, OUTPUT);
  for (int i=0; i<4; i++) { /* some notes for those of you that haven't seen a for loop before:
    int i=0; ~ this is the starting point for the counter. You can use a variable that's already declared elsewhere but for this one I made a new variable called i and set it to start at zero. Why? because the array index starts at zero. You could start at 1 or any other number if it suits your purpose.
    i<4; ~ this is the condition. As long as this is TRUE then the for loop keeps on repeating. Why did I pick <4? I have 4 elements in my array, when the counter "i" reaches 4 then the condition i<4 is FALSE and we break out (again, array index starts at zero so we only need the numbers 0, 1, 2 & 3).
    i++ ~ this is just shorthand for adding 1 to the value of i. It's the same as i = i + 1. 
    */
    pinMode(motor1Pins[i], OUTPUT);
    pinMode(motor2Pins[i], OUTPUT);
  }
  Serial.begin(9600);
}

void loop() {
  // each loop we check the status of the two LDRs (light sensors)
  int leftLight = analogRead(0);
  int rightLight = analogRead(1);
  Serial.print("analog1: ");
  Serial.print(leftLight);
  Serial.print("analog2: ");
  Serial.println(rightLight);
  delay(100);
}