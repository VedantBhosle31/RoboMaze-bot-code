#define PIN_A0   (14)
#define PIN_A1   (15)
#define PIN_A2   (16)
#define PIN_A3   (17)
#define PIN_A4   (18)
#define PIN_A5   (19)
#define PIN_0   (0)
#define PIN_1   (1)
#define PIN_2   (2)
#define PIN_3   (3)
#define PIN_4   (4)
#define PIN_5   (5)
#define PIN_6   (6)
#define PIN_7   (7)
#define PIN_8   (8)
#define PIN_9   (9)
#define PIN_10   (10)
#define PIN_11   (11)
#define PIN_12   (12)


typedef struct UltraSonicSensor{
  int trig;
  int echo;
};
UltraSonicSensor USS1={PIN_A5,PIN_A4};
UltraSonicSensor USS2={PIN_A3,PIN_A2};
UltraSonicSensor USS3={PIN_A1,PIN_A0};
int IRSensor = PIN_4;
long timetaken;
int distance;
typedef struct Motor{
  int in1;
  int in2;
  int en;
};
Motor right={PIN_6,PIN_2,PIN_10};
Motor left={PIN_5,PIN_3,PIN_11};

bool rightWall, leftWall,frontWall;

bool TestWall(UltraSonicSensor test){
    digitalWrite(test.trig,LOW);
  delay(2);
  // delay()
  digitalWrite(test.trig,HIGH);
  delay(10);
  digitalWrite(test.trig,LOW);
  // timetaken = pulseN(echo_1,HIGH);
  timetaken = pulseIn(test.echo,HIGH);
  distance = timetaken*0.034/2;
  if (distance<=30&& distance>=3){
    return true;
  }
  return false;
}
void MotorSetup(Motor motor){
  pinMode(motor.en, OUTPUT);
  pinMode(motor.in1, OUTPUT);
  pinMode(motor.in2, OUTPUT);
  digitalWrite(motor.in1, LOW);
  digitalWrite(motor.in2, LOW);
}
void Forward(bool direction){
  analogWrite(right.en, 255);
	analogWrite(left.en, 255);
  	if(direction){
    digitalWrite(right.in1, LOW);
    digitalWrite(right.in2, HIGH);
    digitalWrite(left.in1, HIGH);
    digitalWrite(left.in2, LOW);
  }else{	
    digitalWrite(right.in1, LOW);
	  digitalWrite(right.in2, HIGH);
	  digitalWrite(left.in1, LOW);
    digitalWrite(left.in2, HIGH);
  }
}
void Turn(bool direction){
  analogWrite(right.en, 255);
	analogWrite(left.en, 255);
  	if(direction){
    digitalWrite(right.in1, LOW);
    digitalWrite(right.in2, HIGH);
    digitalWrite(left.in1, LOW);
    digitalWrite(left.in2, HIGH);
  }else{	
    digitalWrite(right.in1, HIGH);
	  digitalWrite(right.in2, LOW);
	  digitalWrite(left.in1, HIGH);
    digitalWrite(left.in2, LOW);
  }
  delay(860);
  stop();
}
void stop(){
  analogWrite(right.en, 0);
	analogWrite(left.en, 0);

  	// Now turn off motors
	digitalWrite(right.in1, LOW);
	digitalWrite(right.in2, LOW);
	digitalWrite(left.in1, LOW);
	digitalWrite(left.in2, LOW);

}
void UltraSonicSensorSetup(){
  pinMode(USS1.trig,OUTPUT);
  pinMode(USS1.echo,INPUT);
  pinMode(USS2.trig,OUTPUT);
  pinMode(USS2.echo,INPUT);
  pinMode(USS3.trig,OUTPUT);
  pinMode(USS3.echo,INPUT);
}
  int SensorValue = digitalRead (IRSensor);
bool IRDetect(){
  SensorValue = digitalRead (IRSensor);
  if (SensorValue == HIGH) {
        Serial.println("IR sensor not working");
    // digitalWrite (LED, LOW);
    return false;

  } else {
        Serial.println("IR sensor working");
    // digitalWrite (LED, HIGH);
    return true;

  }
}

void setup() {
  pinMode (IRSensor, INPUT);
  UltraSonicSensorSetup();
  MotorSetup(right);
  MotorSetup(left);
  Serial.begin(9600);

  // put your setup code here, to run once:

}

void loop() {
  rightWall= TestWall(USS3);
  leftWall= TestWall(USS1);
  frontWall= TestWall(USS2);
  Serial.print(leftWall);
  Serial.print(" ");
  Serial.print(frontWall);
  Serial.print(" ");
  Serial.println(rightWall);

  if(!frontWall){
    Serial.println("Detected no front wall so going front");
    Forward(false);
  }
  else if(!rightWall){
    Serial.println("Detected no right wall so going right");
    Turn(true);
    Forward(false);
  }
  else if(!leftWall){
    Serial.println("Detected no left wall so going left");
    Turn(false);
    Forward(false);
  }
  else{
    Serial.println("Detected wall in all direction so taking U-Turn");
    Turn(false);
    Turn(false);
    Forward(false);
  }
  while(true){
    if(IRDetect()){
      Serial.println("Detected black strip");
      delay(300);
      if(IRDetect()){
        Serial.println("We are on END");
      }
      break;
    }else{
      Serial.println("No Black strip detected");
    }
  }


  // put your main code here, to run repeatedly:

}
