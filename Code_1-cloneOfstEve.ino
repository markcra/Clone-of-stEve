/* 
Project: Clone of stEve, MAKLab workshop robot
Author: Mark Craig
File: cloneOfstEve
Description:
  Code to demonstrate the robot heading for the light, checking everything is wired correctly. This would not be included with the templates that are provided to the students.
  Includes some code for making noises with the piezo: a startup tune, a beep every time it reads the light sensors and an SOS when the light levels are too low.

*/
const int statusLED = 13;
const int piezoSounder = 3;
int motor1Pins[] = {4, 5, 6, 7};
int motor2Pins[] = {8, 9, 10, 11};

const int FULL_ROTATION = 64 * 64 / 8;
const int HALF_ROTATION = 32 * 64 / 8;
const int QUARTER_ROTATION = 16 * 64 / 8; 

const int minThreshold = 15;
const int differenceThreshold = 15;

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
  soundBugle();
}

void loop() {
  // each loop we check the status of the two LDRs (light sensors)
  digitalWrite(statusLED, HIGH); // so we know when the analog sensor is read
  delay(50);
  int leftLight = analogRead(A0);
  int rightLight = analogRead(A1);
  digitalWrite(statusLED, LOW);
  if (leftLight > minThreshold && rightLight > minThreshold) {
    // both sensors are getting enough light (more than the minimum threshold)
    if (leftLight > rightLight) {
      // more light to our left
      if (leftLight - rightLight > differenceThreshold) {
        ForwardRight(HALF_ROTATION, 6);
      }
      else {
        // not a big difference, lets go straight
        FastForward(HALF_ROTATION, 6);
      }
    }
    else {
      // more light to our right
      if (rightLight - leftLight > differenceThreshold) {
        ForwardLeft(HALF_ROTATION, 6);
      }
      else {
        // not a big difference, lets go straight
        FastForward(HALF_ROTATION, 6);
      }
    }
  }
  else {
    // not enough light on one or both sensors, let's stop and await our human master to set things straight.
    StopMotors();
    morseCode();
    delay(50);
  }
  StopMotors();
  //soundOneUp();
  dot();
}

void FastForward(int steps, int stepDelay) // both motors simultaneously
{
  // variable 'steps' is a misnomer, the number of steps this fuction executes is actually (8 * 'steps').
  // for a full rotation we therefore only need 'steps' = (64/8)*64 = 8*64.
  for (int i=0; i<steps; i++) {
    digitalWrite(motor1Pins[0], HIGH);
    digitalWrite(motor1Pins[1], LOW);
    digitalWrite(motor1Pins[2], LOW);
    digitalWrite(motor1Pins[3], LOW);
    digitalWrite(motor2Pins[0], LOW);
    digitalWrite(motor2Pins[1], LOW);
    digitalWrite(motor2Pins[2], LOW);
    digitalWrite(motor2Pins[3], HIGH);
    delay(stepDelay);
    digitalWrite(motor1Pins[0], HIGH);
    digitalWrite(motor1Pins[1], HIGH);
    digitalWrite(motor1Pins[2], LOW);
    digitalWrite(motor1Pins[3], LOW);
    digitalWrite(motor2Pins[0], LOW);
    digitalWrite(motor2Pins[1], LOW);
    digitalWrite(motor2Pins[2], HIGH);
    digitalWrite(motor2Pins[3], HIGH);
    delay(stepDelay);
    digitalWrite(motor1Pins[0], LOW);
    digitalWrite(motor1Pins[1], HIGH);
    digitalWrite(motor1Pins[2], LOW);
    digitalWrite(motor1Pins[3], LOW);
    digitalWrite(motor2Pins[0], LOW);
    digitalWrite(motor2Pins[1], LOW);
    digitalWrite(motor2Pins[2], HIGH);
    digitalWrite(motor2Pins[3], LOW);
    delay(stepDelay);
    digitalWrite(motor1Pins[0], LOW);
    digitalWrite(motor1Pins[1], HIGH);
    digitalWrite(motor1Pins[2], HIGH);
    digitalWrite(motor1Pins[3], LOW);
    digitalWrite(motor2Pins[0], LOW);
    digitalWrite(motor2Pins[1], HIGH);
    digitalWrite(motor2Pins[2], HIGH);
    digitalWrite(motor2Pins[3], LOW);
    delay(stepDelay);
    digitalWrite(motor1Pins[0], LOW);
    digitalWrite(motor1Pins[1], LOW);
    digitalWrite(motor1Pins[2], HIGH);
    digitalWrite(motor1Pins[3], LOW);
    digitalWrite(motor2Pins[0], LOW);
    digitalWrite(motor2Pins[1], HIGH);
    digitalWrite(motor2Pins[2], LOW);
    digitalWrite(motor2Pins[3], LOW);
    delay(stepDelay);
    digitalWrite(motor1Pins[0], LOW);
    digitalWrite(motor1Pins[1], LOW);
    digitalWrite(motor1Pins[2], HIGH);
    digitalWrite(motor1Pins[3], HIGH);
    digitalWrite(motor2Pins[0], HIGH);
    digitalWrite(motor2Pins[1], HIGH);
    digitalWrite(motor2Pins[2], LOW);
    digitalWrite(motor2Pins[3], LOW);
    delay(stepDelay);
    digitalWrite(motor1Pins[0], LOW);
    digitalWrite(motor1Pins[1], LOW);
    digitalWrite(motor1Pins[2], LOW);
    digitalWrite(motor1Pins[3], HIGH);
    digitalWrite(motor2Pins[0], HIGH);
    digitalWrite(motor2Pins[1], LOW);
    digitalWrite(motor2Pins[2], LOW);
    digitalWrite(motor2Pins[3], LOW);
    delay(stepDelay);
    digitalWrite(motor1Pins[0], HIGH);
    digitalWrite(motor1Pins[1], LOW);
    digitalWrite(motor1Pins[2], LOW);
    digitalWrite(motor1Pins[3], HIGH);
    digitalWrite(motor2Pins[0], HIGH);
    digitalWrite(motor2Pins[1], LOW);
    digitalWrite(motor2Pins[2], LOW);
    digitalWrite(motor2Pins[3], HIGH);
    delay(stepDelay);
  }
}

void ReverseLeft(int steps, int stepDelay)
{
  for (int i=0; i<steps; i++) {
    digitalWrite(motor1Pins[0], LOW);
    digitalWrite(motor1Pins[1], LOW);
    digitalWrite(motor1Pins[2], LOW);
    digitalWrite(motor1Pins[3], HIGH);
    delay(stepDelay);
    digitalWrite(motor1Pins[0], LOW);
    digitalWrite(motor1Pins[1], LOW);
    digitalWrite(motor1Pins[2], HIGH);
    digitalWrite(motor1Pins[3], HIGH);
    delay(stepDelay);
    digitalWrite(motor1Pins[0], LOW);
    digitalWrite(motor1Pins[1], LOW);
    digitalWrite(motor1Pins[2], HIGH);
    digitalWrite(motor1Pins[3], LOW);
    delay(stepDelay);
    digitalWrite(motor1Pins[0], LOW);
    digitalWrite(motor1Pins[1], HIGH);
    digitalWrite(motor1Pins[2], HIGH);
    digitalWrite(motor1Pins[3], LOW);
    delay(stepDelay);
    digitalWrite(motor1Pins[0], LOW);
    digitalWrite(motor1Pins[1], HIGH);
    digitalWrite(motor1Pins[2], LOW);
    digitalWrite(motor1Pins[3], LOW);
    delay(stepDelay);
    digitalWrite(motor1Pins[0], HIGH);
    digitalWrite(motor1Pins[1], HIGH);
    digitalWrite(motor1Pins[2], LOW);
    digitalWrite(motor1Pins[3], LOW);
    delay(stepDelay);
    digitalWrite(motor1Pins[0], HIGH);
    digitalWrite(motor1Pins[1], LOW);
    digitalWrite(motor1Pins[2], LOW);
    digitalWrite(motor1Pins[3], LOW);
    delay(stepDelay);
    digitalWrite(motor1Pins[0], HIGH);
    digitalWrite(motor1Pins[1], LOW);
    digitalWrite(motor1Pins[2], LOW);
    digitalWrite(motor1Pins[3], HIGH);
    delay(stepDelay);
  }
}

void ReverseRight(int steps, int stepDelay)
{
  for (int i=0; i<steps; i++) {
    digitalWrite(motor2Pins[0], HIGH);
    digitalWrite(motor2Pins[1], LOW);
    digitalWrite(motor2Pins[2], LOW);
    digitalWrite(motor2Pins[3], LOW);
    delay(stepDelay);
    digitalWrite(motor2Pins[0], HIGH);
    digitalWrite(motor2Pins[1], HIGH);
    digitalWrite(motor2Pins[2], LOW);
    digitalWrite(motor2Pins[3], LOW);
    delay(stepDelay);
    digitalWrite(motor2Pins[0], LOW);
    digitalWrite(motor2Pins[1], HIGH);
    digitalWrite(motor2Pins[2], LOW);
    digitalWrite(motor2Pins[3], LOW);
    delay(stepDelay);
    digitalWrite(motor2Pins[0], LOW);
    digitalWrite(motor2Pins[1], HIGH);
    digitalWrite(motor2Pins[2], HIGH);
    digitalWrite(motor2Pins[3], LOW);
    delay(stepDelay);
    digitalWrite(motor2Pins[0], LOW);
    digitalWrite(motor2Pins[1], LOW);
    digitalWrite(motor2Pins[2], HIGH);
    digitalWrite(motor2Pins[3], LOW);
    delay(stepDelay);
    digitalWrite(motor2Pins[0], LOW);
    digitalWrite(motor2Pins[1], LOW);
    digitalWrite(motor2Pins[2], HIGH);
    digitalWrite(motor2Pins[3], HIGH);
    delay(stepDelay);
    digitalWrite(motor2Pins[0], LOW);
    digitalWrite(motor2Pins[1], LOW);
    digitalWrite(motor2Pins[2], LOW);
    digitalWrite(motor2Pins[3], HIGH);
    delay(stepDelay);
    digitalWrite(motor2Pins[0], HIGH);
    digitalWrite(motor2Pins[1], LOW);
    digitalWrite(motor2Pins[2], LOW);
    digitalWrite(motor2Pins[3], HIGH);
    delay(stepDelay);
  }
}

void ForwardLeft(int steps, int stepDelay)
{
  for (int i=0; i<steps; i++) {
    digitalWrite(motor1Pins[0], HIGH);
    digitalWrite(motor1Pins[1], LOW);
    digitalWrite(motor1Pins[2], LOW);
    digitalWrite(motor1Pins[3], LOW);
    delay(stepDelay);
    digitalWrite(motor1Pins[0], HIGH);
    digitalWrite(motor1Pins[1], HIGH);
    digitalWrite(motor1Pins[2], LOW);
    digitalWrite(motor1Pins[3], LOW);
    delay(stepDelay);
    digitalWrite(motor1Pins[0], LOW);
    digitalWrite(motor1Pins[1], HIGH);
    digitalWrite(motor1Pins[2], LOW);
    digitalWrite(motor1Pins[3], LOW);
    delay(stepDelay);
    digitalWrite(motor1Pins[0], LOW);
    digitalWrite(motor1Pins[1], HIGH);
    digitalWrite(motor1Pins[2], HIGH);
    digitalWrite(motor1Pins[3], LOW);
    delay(stepDelay);
    digitalWrite(motor1Pins[0], LOW);
    digitalWrite(motor1Pins[1], LOW);
    digitalWrite(motor1Pins[2], HIGH);
    digitalWrite(motor1Pins[3], LOW);
    delay(stepDelay);
    digitalWrite(motor1Pins[0], LOW);
    digitalWrite(motor1Pins[1], LOW);
    digitalWrite(motor1Pins[2], HIGH);
    digitalWrite(motor1Pins[3], HIGH);
    delay(stepDelay);
    digitalWrite(motor1Pins[0], LOW);
    digitalWrite(motor1Pins[1], LOW);
    digitalWrite(motor1Pins[2], LOW);
    digitalWrite(motor1Pins[3], HIGH);
    delay(stepDelay);
    digitalWrite(motor1Pins[0], HIGH);
    digitalWrite(motor1Pins[1], LOW);
    digitalWrite(motor1Pins[2], LOW);
    digitalWrite(motor1Pins[3], HIGH);
    delay(stepDelay);
  }
}

void ForwardRight(int steps, int stepDelay)
{
  for (int i=0; i<steps; i++) {
    digitalWrite(motor2Pins[0], LOW);
    digitalWrite(motor2Pins[1], LOW);
    digitalWrite(motor2Pins[2], LOW);
    digitalWrite(motor2Pins[3], HIGH);
    delay(stepDelay);
    digitalWrite(motor2Pins[0], LOW);
    digitalWrite(motor2Pins[1], LOW);
    digitalWrite(motor2Pins[2], HIGH);
    digitalWrite(motor2Pins[3], HIGH);
    delay(stepDelay);
    digitalWrite(motor2Pins[0], LOW);
    digitalWrite(motor2Pins[1], LOW);
    digitalWrite(motor2Pins[2], HIGH);
    digitalWrite(motor2Pins[3], LOW);
    delay(stepDelay);
    digitalWrite(motor2Pins[0], LOW);
    digitalWrite(motor2Pins[1], HIGH);
    digitalWrite(motor2Pins[2], HIGH);
    digitalWrite(motor2Pins[3], LOW);
    delay(stepDelay);
    digitalWrite(motor2Pins[0], LOW);
    digitalWrite(motor2Pins[1], HIGH);
    digitalWrite(motor2Pins[2], LOW);
    digitalWrite(motor2Pins[3], LOW);
    delay(stepDelay);
    digitalWrite(motor2Pins[0], HIGH);
    digitalWrite(motor2Pins[1], HIGH);
    digitalWrite(motor2Pins[2], LOW);
    digitalWrite(motor2Pins[3], LOW);
    delay(stepDelay);
    digitalWrite(motor2Pins[0], HIGH);
    digitalWrite(motor2Pins[1], LOW);
    digitalWrite(motor2Pins[2], LOW);
    digitalWrite(motor2Pins[3], LOW);
    delay(stepDelay);
    digitalWrite(motor2Pins[0], HIGH);
    digitalWrite(motor2Pins[1], LOW);
    digitalWrite(motor2Pins[2], LOW);
    digitalWrite(motor2Pins[3], HIGH);
    delay(stepDelay);
  }
}

void StopMotors()
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

uint16_t midiTable[] = {
  27,29,31,32,34,36,38,41,43,46, // midi note 21, 22, 23, 24...30
  48,51,54,58,61,65,69,73,77,82, // midi note 31...40
  86,92,97,103,109,115,122,129,137,145, // midi note 41...50
  154,163,173,183,194,206,218,231,244,259, // midi note 51...60
  274,291,308,326,346,366,388,411,435,461, // midi note 61...70
  489,518,549,581,616,652,691,732,776,822, // midi note 71...80
  871,923,978,1036,1097,1163,1232,1305,1383,1465, // midi note 81...90
  1552,1644,1742,1845,1955,2071,2195,2325,2463,2610, // midi note 91...100
  2765,2930,3104,3288,3484,3691,3910,4143,4389,4650, // midi note 101...110
  4927,5220,5530,5859,6207,6577,6968,7382,7821,8286, // midi note 111...120
  8779,9301,9854,10440,11060,11718,12415,13153,13935,14764, // midi note 121...130
  15642,16572,17557,18601,19708,20879,22121,23436,24830,26306 // midi note 131...140
};

uint16_t midiToFreq(uint16_t input) {
  return midiTable[input - 21];
  //return (midiTable[(1023-input) >> 3]);
}

void soundOneUp()
{
  float tempo = 272.72 / 50;
  // play a sound on the piezo to attract attention
  tone(piezoSounder, midiToFreq(88)); // note on
  delay((int)(30.0*tempo));
  noTone(piezoSounder); // note off
  delay((int)(30.0*tempo));
  tone(piezoSounder, midiToFreq(91)); // note on
  delay((int)(30.0*tempo));
  noTone(piezoSounder); // note off
  delay((int)(30.0*tempo));
  tone(piezoSounder, midiToFreq(100)); // note on
  delay((int)(30.0*tempo));
  noTone(piezoSounder); // note off
  delay((int)(30.0*tempo));
  tone(piezoSounder, midiToFreq(96)); // note on
  delay((int)(30.0*tempo));
  noTone(piezoSounder); // note off
  delay((int)(30.0*tempo));
  tone(piezoSounder, midiToFreq(98)); // note on
  delay((int)(30.0*tempo));
  noTone(piezoSounder); // note off
  delay((int)(30.0*tempo));
  tone(piezoSounder, midiToFreq(103)); // note on
  delay((int)(30.0*tempo));
  noTone(piezoSounder); // note off
}

void soundBugle()
{
  float tempo = 2; //400000;
  //tempo = tempo / 1000 / 60;
  tone(piezoSounder,midiToFreq(67));
  delay(142*tempo);
  noTone(piezoSounder);
  delay(2*tempo);
  tone(piezoSounder,midiToFreq(67));
  delay(46*tempo);
  noTone(piezoSounder);
  delay(2*tempo);
  tone(piezoSounder,midiToFreq(72));
  delay(142*tempo);
  noTone(piezoSounder);
  delay(2*tempo);
  tone(piezoSounder,midiToFreq(67));
  delay(46*tempo);
  noTone(piezoSounder);
  delay(2*tempo);
  tone(piezoSounder,midiToFreq(72));
  delay(142*tempo);
  noTone(piezoSounder);
  delay(2*tempo);
  tone(piezoSounder,midiToFreq(76));
  delay(46*tempo);
  noTone(piezoSounder);
  delay(2*tempo);
  tone(piezoSounder,midiToFreq(72));
  delay(160*tempo);
  noTone(piezoSounder);
  delay(32*tempo);
  tone(piezoSounder,midiToFreq(72));
  delay(142*tempo);
  noTone(piezoSounder);
  delay(2*tempo);
  tone(piezoSounder,midiToFreq(72));
  delay(46*tempo);
  noTone(piezoSounder);
  delay(2*tempo);
  tone(piezoSounder,midiToFreq(76));
  delay(142*tempo);
  noTone(piezoSounder);
  delay(2*tempo);
  tone(piezoSounder,midiToFreq(72));
  delay(46*tempo);
  noTone(piezoSounder);
  delay(2*tempo);
  tone(piezoSounder,midiToFreq(76));
  delay(142*tempo);
  noTone(piezoSounder);
  delay(2*tempo);
  tone(piezoSounder,midiToFreq(79));
  delay(46*tempo);
  noTone(piezoSounder);
  delay(2*tempo);
  tone(piezoSounder,midiToFreq(76));
  delay(160*tempo);
  noTone(piezoSounder);
  delay(32*tempo);
  tone(piezoSounder,midiToFreq(72));
  delay(142*tempo);
  noTone(piezoSounder);
  delay(2*tempo);
  tone(piezoSounder,midiToFreq(76));
  delay(46*tempo);
  noTone(piezoSounder);
  delay(2*tempo);
  tone(piezoSounder,midiToFreq(79));
  delay(160*tempo);
  noTone(piezoSounder);
  delay(32*tempo);
  tone(piezoSounder,midiToFreq(76));
  delay(142*tempo);
  noTone(piezoSounder);
  delay(2*tempo);
  tone(piezoSounder,midiToFreq(72));
  delay(46*tempo);
  noTone(piezoSounder);
  delay(2*tempo);
  tone(piezoSounder,midiToFreq(67));
  delay(160*tempo);
  noTone(piezoSounder);
  delay(32*tempo);
  tone(piezoSounder,midiToFreq(67));
  delay(142*tempo);
  noTone(piezoSounder);
  delay(2*tempo);
  tone(piezoSounder,midiToFreq(67));
  delay(46*tempo);
  noTone(piezoSounder);
  delay(2*tempo);
  tone(piezoSounder,midiToFreq(72));
  delay(160*tempo);
  noTone(piezoSounder);
  delay(32*tempo);
  tone(piezoSounder,midiToFreq(72));
  delay(142*tempo);
  noTone(piezoSounder);
  delay(2*tempo);
  tone(piezoSounder,midiToFreq(72));
  delay(46*tempo);
  noTone(piezoSounder);
  delay(2*tempo);
  tone(piezoSounder,midiToFreq(72));
  delay(160*tempo);
  noTone(piezoSounder);
  delay(2*tempo);
  noTone(piezoSounder);
}

// tone frequency C
const int tonefreq = 523;
// constants for tone and rest durations
const int dotlength = 100;
const int dashlength = dotlength * 3;
// inter-element gap - between each dot or dash of a letter
const int inter = dotlength; 
// letter gap is 3 dots - the inter gap is always added - so this is one fewer
const int lgap = dotlength * 2; // inter-letter gap
// word gap is 7 dots - with letter and inter gap already counted, this is -1
const int wgap = dotlength * 4; //inter-word gap

void dot()
{
  // play a dot
  tone(piezoSounder, tonefreq);
  digitalWrite(statusLED, HIGH);
  delay(dotlength);
  noTone(piezoSounder);
  digitalWrite(statusLED, LOW);
  delay(inter);
}

void dash()
{
  // play a dash
  tone(piezoSounder, tonefreq);
  digitalWrite(statusLED, HIGH);
  delay(dashlength);
  noTone(piezoSounder);
  digitalWrite(statusLED, LOW);
  delay(inter);
}

void morseCode() {
  char message[] = {'S', 'O', 'S'};
  int message_length = 3;
  
  for(int i=0; i<message_length; i++) {
    // letters are in order of frequency
    switch(message[i])
    {
      case 'A':
        dot();
        dash();
        break;
      case 'E':
        dot();
        break; 
      case 'I':
        dot();
        dot();
        break;
      case 'O':
        dash();
        dash();
        dash();
        break; 
      case 'U':
        dot();
        dot();
        dash();
        break;
      case 'N':
        dash();
        dot();
        break;
      case 'S':
        dot();
        dot();
        dot();
        break;
      case 'T':
        dash();
        break; 
      case 'H':
        dot();
        dot();
        dot();
        dot();
        break;
      case 'R':
        dot();
        dash();
        dot();
        break;
      case 'D':
        dash();
        dot();
        dot();
        break;
      case 'L':
        dot();
        dash();
        dot();
        dot();
        break;
      case 'C':
        dash();
        dot();
        dash();
        dot();
        break;
      case 'M':
        dash();
        dash();
        break;
      case 'W':
        dot();
        dash();
        dash();
        break;
      case 'F':
        dot();
        dot();
        dash();
        dot();
        break;
      case 'G':
        dash();
        dash();
        dot();
        break;
      case 'Y':
        dash();
        dot();
        dash();
        dash();
        break;
      case 'P':
        dot();
        dash();
        dash();
        dot();
        break;
      case 'B':
        dash();
        dot();
        dot();
        dot();
        break;
      case 'V':
        dot();
        dot();
        dot();
        dash();
        break;
      case 'K':
        dash();
        dot();
        dash();
        break;
      case 'J':
        dot();
        dash();
        dash();
        dash();
        break;
      case 'X':
        dash();
        dot();
        dot();
        dash();
        break;
      case 'Q':
        dash();
        dash();
        dot();
        dash();
        break;
      case 'Z':
        dash();
        dash();
        dot();
        dot();
        break;
      case ' ':
        delay(wgap);
        break; 
    }
    if (message[i] != ' ')
      delay(lgap); // letter gap
  }
}
