int IRSensor = 3; // connect ir sensor to arduino pin 3
int LED = 11; // connect LED to arduino pin 11

void setup () {
  pinMode (IRSensor, INPUT); // sensor pin INPUT
  pinMode (LED, OUTPUT); // LED pin OUTPUT
}

void loop () {
  int SensorValue = digitalRead (IRSensor);
  if (SensorValue == HIGH) {
    println("IR sensor working")
    digitalWrite (LED, HIGH);
  } else {
    println("IR sensor not working")
    digitalWrite (LED, LOW);
  }
}
