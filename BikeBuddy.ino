// use Nano
// BikeBuddy 
// Version 1.0 2-18-2026
#define TESTMODE
#ifdef TESTMODE
  #define debugSerial(x) Serial.begin(9600)
  #define debug(x)  Serial.print(x)
  #define debugln(x) Serial.println(x)
#else
  #define debugSerial(x) 
  #define debug(x)  
  #define debugln(x) 
#endif

const int echo1Pin=2;
const int trig1Pin=3;
const int echo2Pin=4;
const int trig2Pin=5;

const int sigPin=6;  // MOTOR ON
// for interval
const int rngSw1 = 7;
const int rngSw2 = 8;
const int rngSw3 = 9;
const int rngSw4 = 10;

long duration;
int distance;
#define defaultCheck 5000;
int thresh = 300;  // 3 meters -- 300 cm
int InterValCheck = defaultCheck;  //every 5 seconds
void setup() {
  pinMode(trig1Pin, OUTPUT); // Set TRIG as output
  pinMode(echo1Pin, INPUT); // Set ECHO as input
  pinMode(trig2Pin, OUTPUT); // Set TRIG as output
  pinMode(echo2Pin, INPUT); // Set ECHO as input
  
  pinMode(sigPin, OUTPUT);
  //
  pinMode(rngSw1, INPUT);
  pinMode(rngSw2, INPUT);
  pinMode(rngSw3, INPUT);
  pinMode(rngSw4, INPUT);
 
  debugSerial(9600); // Initialize serial communication
  debugln("Test Ultra Sonic");
  digitalWrite(sigPin, HIGH);
  delay(5000);
  digitalWrite(sigPin, LOW);
  
  #ifdef TESTMODE
  if(InterValCheck > 5000)
  {
    debug("InterValCheck = "); debugln(InterValCheck);
     
  }
  #endif
}
void checkIntervalAdjustments()
{
  debugln("Check Interval Switches");
  InterValCheck = defaultCheck; // start at default value
  if(digitalRead(rngSw1)) InterValCheck+=5000;
  if(digitalRead(rngSw2)) InterValCheck+=5000;
  if(digitalRead(rngSw3)) InterValCheck+=5000;
  if(digitalRead(rngSw4)) InterValCheck+=5000;
   
    debug("InterValCheck = "); debugln(InterValCheck);
   

}
 
void execSensor(int echoSensor, int trigSensor)
{
  debugln("Check Sensor");
    // Clear TRIG pin
  digitalWrite(trigSensor, LOW);
  delayMicroseconds(2);
  // Trigger ultrasonic pulse
  digitalWrite(trigSensor, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigSensor, LOW);
  // Measure echo duration
  duration = pulseIn(echoSensor, HIGH);
  // Calculate distance (cm)
  distance = duration * 0.034 / 2;  
  if(distance < thresh)
   {
    debug ("distance calc = ");debug(distance);
    debug(" thresh = ");debug(thresh);
    debugln(" distance < thresh");
    delay(10);    
    digitalWrite(sigPin, HIGH);
//    delayMicroseconds(10);
    delay(10000);
    // 
    digitalWrite(sigPin, LOW); // turn off   
   }
 
} 

void loop() {
  checkIntervalAdjustments();
  
  delay(InterValCheck);    
  execSensor(echo1Pin, trig1Pin);
  delay(10);
  execSensor(echo2Pin, trig2Pin);
}
