
/*
   Ultrasonic sensor Pins:
       VCC: +5VDC
       Trig : Trigger (INPUT) - Pin11
       Echo: Echo (OUTPUT) - Pin 12
       GND: GND
*/
int lowdistancePin = 8;
int meddistancePin = 7;
int highdistancePin = 2;
int trigPin = 11;    // Trigger
int echoPin = 12;    // Echo
long duration, cm, inches;

void setup() {
  //Serial Port begin
  Serial.begin (9600);
  //Define inputs and outputs
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(lowdistancePin, OUTPUT);
  pinMode(meddistancePin, OUTPUT);
  pinMode(highdistancePin, OUTPUT);
}

void loop() {
  // The sensor is triggered by a HIGH pulse of 10 or more microseconds.
  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
  digitalWrite(trigPin, LOW);
  delayMicroseconds(5);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Read the signal from the sensor: a HIGH pulse whose
  // duration is the time (in microseconds) from the sending
  // of the ping to the reception of its echo off of an object.
  pinMode(echoPin, INPUT);
  duration = pulseIn(echoPin, HIGH);

  // Convert the time into a distance
  cm = (duration / 2) / 29.1;   // Divide by 29.1 or multiply by 0.0343
  Serial.print(cm);
  Serial.print("cm");
  Serial.println();
  if (cm > 360) {
    digitalWrite(highdistancePin, HIGH);
    digitalWrite(meddistancePin, LOW);
    digitalWrite(lowdistancePin, LOW);
  } else if ( cm <= 360 && cm > 40) {
    digitalWrite(highdistancePin, HIGH);
    digitalWrite(meddistancePin, HIGH);
    digitalWrite(lowdistancePin, LOW);
  }
  else if (cm <= 40) {
    digitalWrite(highdistancePin, HIGH);
    digitalWrite(meddistancePin, HIGH);
    digitalWrite(lowdistancePin, HIGH);
  } else {
    digitalWrite(highdistancePin, LOW);
    digitalWrite(meddistancePin, LOW);
    digitalWrite(lowdistancePin, LOW);
  }
  delay(100);
}
