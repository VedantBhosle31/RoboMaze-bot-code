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

typedef struct Motor{
  int in1;
  int in2;
  int en;
};
Motor right={PIN_6,PIN_2,PIN_10};
Motor left={PIN_5,PIN_3,PIN_11};
void MotorSetup(Motor motor){
  pinMode(motor.en, OUTPUT);
  pinMode(motor.in1, OUTPUT);
  pinMode(motor.in2, OUTPUT);
  digitalWrite(motor.in1, LOW);
  digitalWrite(motor.in2, LOW);
}

void setup() {
	// Set all the motor control pins to outputs
  MotorSetup(right);
  MotorSetup(left);
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

// This function lets you control spinning direction of motors
void directionControl(bool direction) {
	// Set motors to maximum speed
	// For PWM maximum possible values are 0 to 255
	analogWrite(right.en, 255);
	analogWrite(left.en, 255);

	// Turn on motor A & B

	if(direction){
    digitalWrite(right.in1, LOW);
    digitalWrite(right.in2, HIGH);
    digitalWrite(left.in1, HIGH);
    digitalWrite(left.in2, LOW);
    delay(2000);

  }else{	
    digitalWrite(right.in1, LOW);
	  digitalWrite(right.in2, HIGH);
	  digitalWrite(left.in1, LOW);
    digitalWrite(left.in2, HIGH);
    delay(2000);
  }

	// Turn off motors
	digitalWrite(right.in1, LOW);
	digitalWrite(right.in2, LOW);
	digitalWrite(left.in1, LOW);
	digitalWrite(left.in2, LOW);
}

// This function lets you control speed of the motors
void speedControl(bool direction) {

	// Turn on motors
	if(direction){
    digitalWrite(right.in1, LOW);
    digitalWrite(right.in2, HIGH);
    digitalWrite(left.in1, LOW);
    digitalWrite(left.in2, HIGH);
    delay(2000);

  }else{	
    digitalWrite(right.in1, HIGH);
	  digitalWrite(right.in2, LOW);
	  digitalWrite(left.in1, HIGH);
    digitalWrite(left.in2, LOW);
    delay(2000);
  }

	
	// Accelerate from zero to maximum speed
	for (int i = 0; i < 256; i++) {
		analogWrite(right.en, i);
		analogWrite(left.en, i);
		delay(20);
	}
	
	// Decelerate from maximum speed to zero
	for (int i = 255; i >= 0; --i) {
		analogWrite(right.en, i);
		analogWrite(left.en, i);
		delay(20);
	}
	
	// Now turn off motors
	digitalWrite(right.in1, LOW);
	digitalWrite(right.in2, LOW);
	digitalWrite(left.in1, LOW);
	digitalWrite(left.in2, LOW);
}

void loop() {
  // forward(false);
  // Turn(true);
  delay(10000);
  stop();
  delay(1000);



}