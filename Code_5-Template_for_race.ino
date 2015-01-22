const int statusLED = 13;
const int piezoSounder = 3;
int motor1Pins[] = {4, 5, 6, 7};
int motor2Pins[] = {8, 9, 10, 11};

const int minThreshold = 15;
const int differenceThreshold = 15;

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
  // each loop we check the status of the two LDRs (light sensors)
  digitalWrite(statusLED, HIGH); // so we know when the analog sensor is read
  delay(50);
  int leftLight = analogRead(A0);
  int rightLight = analogRead(A1);
  digitalWrite(statusLED, LOW);
  if (leftLight > minThreshold && rightLight > minThreshold)
  {
    // both sensors are getting enough light (more than the minimum threshold)
    if (leftLight > rightLight)
    {
      // more light to our left
      if (leftLight - rightLight > differenceThreshold)
      {
        halfRotationFwdRight();
      }
      else
      {
        // not a big difference, lets go straight
        halfRotationFwdBoth();
      }
    }
    else
    {
      // more light to our right
      if (rightLight - leftLight > differenceThreshold)
      {
        halfRotationFwdLeft();
      }
      else
      {
        // not a big difference, lets go straight
        halfRotationFwdBoth();
      }
    }
  }
  else
  {
    // not enough light on one or both sensors, let's stop and await our human master to set things straight.
    stopMotors();
  }
  stopMotors();
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

// Bring across the functions you worked on in Template_3, don't forget any global variables you have created.