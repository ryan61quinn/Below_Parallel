#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
//constrast of LCD screen
int con = 75;
//trig and echo pins on arduino
int trigP = 10;
int echoP = 13;
//array variables
const int arrayLen = 10;
int distArray[arrayLen];
float avg;
//distance = speed * time
int buz = 8;

int endtime;
int interval;
int startTime;
void setup() {
  Serial.begin(9600);
  analogWrite(6, con);
  lcd.begin(16, 2);
  pinMode(13, INPUT);
  pinMode(10, OUTPUT);

  interval = 0; //1000 millis = 1 sec, this sets how long before timer starts 
  startTime = millis(); //creates timer lets timer be equal to milliseconds
}
void loop() {
  endtime = millis(); //eupdates every frame gets bigger till hits interval for timer to start
  //tells arduino to read val of anailog everyframe
  lcd.clear();
  lcd.print("Distance: ");
  lcd.print(avg);
  getDist(echoP, trigP);
  delay(1000);
  //Serial.println(getDist(echoP, trigP));
  fillArray();
  avg = avgArray(distArray, arrayLen);
  Serial.println(avg);
  belowParallel();
}
float getDist(int aEchoP, int aTrigP){
  //local variables
  float duration;
  float distance;
  //makes sure that it is off before starting
  digitalWrite(aTrigP, LOW);
  delayMicroseconds(2);
  //send out signal for 10 microsec
  digitalWrite(aTrigP, HIGH);
  delayMicroseconds(2);
  digitalWrite(aTrigP, LOW);
  //pulseIn gets the amount of echopin runs for
  //reads as HIGH
  duration = pulseIn(aEchoP, HIGH);
  //only care about distance one way
  //convert time it takes to travel that one way
  //cm = distance = rate/time
  distance = duration/2*0.0344;
  //reutrns results
  return distance;
}
float avgArray(int * anArray, int aArrayLen){
  float sum = 0;
  for(int i=0;i<aArrayLen;i++){
    sum += anArray[i];
  }
   return((float) sum)/aArrayLen; 
}
void fillArray(){
  for(int i=0; i<arrayLen; i++){
    distArray[i]=getDist(echoP, trigP);
  }
}
void belowParallel(){
  if(avg <= 5){
    tone(buz, 2000);
    delay(1000);
    noTone(buz);
  }
}
