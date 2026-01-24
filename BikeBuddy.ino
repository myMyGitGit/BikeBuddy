// use Nano
// BikeBuddy
const int echoPin=5;
const int trigPin=6;
const int sigPin=2;
// for ranging
const int rngSw1 = 7;
const int rngSw2 = 9;
const int rngSw3 = 10;

long duration;
int distance;
 
int thresh = 100; //100; // 100 cm = 1000 mm = 1 meter=default
#define InterValCheck 10000  //every 10 seconds
void setup() {
  pinMode(trigPin, OUTPUT); // Set TRIG as output
  pinMode(echoPin, INPUT); // Set ECHO as input
  pinMode(sigPin, OUTPUT);
  //
  pinMode(rngSw1, INPUT);
  pinMode(rngSw2, INPUT);
  pinMode(rngSw3, INPUT);
  
 
  Serial.begin(9600); // Initialize serial communication
  Serial.println("Test Ultra Sonic");
  digitalWrite(sigPin, HIGH);
  delay(5000);
  digitalWrite(sigPin, LOW);
  checkRangeAdjustments();
  //testSensor();
}
void checkRangeAdjustments()
{
  if(digitalRead(rngSw1)) thresh+=50;
  if(digitalRead(rngSw2)) thresh+=50;
  if(digitalRead(rngSw3)) thresh+=100;
 
}
void execSensor()
{
    // Clear TRIG pin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Trigger ultrasonic pulse
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Measure echo duration
  duration = pulseIn(echoPin, HIGH);
  // Calculate distance (cm)
  distance = duration * 0.034 / 2;
  // Print distance to Serial Monitor
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");
  Serial.print("Range is:"); Serial.println(thresh);
 
   if(distance > thresh)
   {
    Serial.println("distance > thresh");
    delay(100);
    digitalWrite(sigPin, HIGH);
   // delayMicroseconds(10);
    delay(10000);
    // 
    digitalWrite(sigPin, LOW); // turn off  
   }
  delay(5000); // Wait before next measurement  
} 
void loop() {
  delay(InterValCheck); //every ten seconds
  
  execSensor();
}
