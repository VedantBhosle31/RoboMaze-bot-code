#define PIN_A0   (14)
#define PIN_A1   (15)
#define PIN_A2   (16)
#define PIN_A3   (17)
#define PIN_A4   (18)
#define PIN_A5   (19)


typedef struct UltraSonicSensor{
  int trig;
  int echo;
};
UltraSonicSensor USS1={PIN_A5,PIN_A4};
UltraSonicSensor USS2={PIN_A3,PIN_A2};
UltraSonicSensor USS3={PIN_A1,PIN_A0};
long timetaken;
int distance;

// int USS1.trig =PIN_A5;
// int USS1.echo =PIN_A4;

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


  int i=1;
void setup() {
  // put your setup code here, to run once:
  pinMode(USS1.trig,OUTPUT);
  pinMode(USS1.echo,INPUT);
  pinMode(USS2.trig,OUTPUT);
  pinMode(USS2.echo,INPUT);
  pinMode(USS3.trig,OUTPUT);
  pinMode(USS3.echo,INPUT);
  Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:

  i++;
  Serial.print(i);
  if(TestWall(USS1)){
    Serial.println("Sensor 1  Working");
  }
 if(TestWall(USS2)){
    Serial.println("Sensor 2  Working");
  } 
if(TestWall(USS3)){
    Serial.println("Sensor 3  Working");
  }
  
  
}
