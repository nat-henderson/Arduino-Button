int inPin;
int outPin;
int recentIn[4];
boolean sent;

void setup()
{
  // alter based on your own setup
  inPin = 9;
  outPin = 5;


  Serial.begin(9600);
  pinMode(inPin, INPUT);
  pinMode(outPin, OUTPUT);
  digitalWrite(inPin, HIGH);
  recentIn[0] = HIGH;
  recentIn[1] = HIGH;
  recentIn[2] = HIGH;
  recentIn[3] = HIGH;
  sent = false;
}

void loop()
{
  digitalWrite(outPin, LOW);
  // slide everything back a bit
  recentIn[0] = recentIn[1];
  recentIn[1] = recentIn[2];
  recentIn[2] = recentIn[3];
  recentIn[3] = digitalRead(inPin);
  // confirm that we're not seeing a fluctuation
  // basically a low-pass filter
  if (recentIn[0] + recentIn[1] + recentIn[2] + recentIn[3] == LOW)
  {
    if (!sent)
    {
      Serial.println("Input Received");
      sent = true;
    }
  }
  else if (recentIn[0] + recentIn[1] + recentIn[2] + recentIn[3] == 4 * HIGH)
  {
    sent = false;
  }
}
