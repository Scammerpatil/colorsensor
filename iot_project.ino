#include <Servo.h>
#define S0 2
#define S1 3
#define S2 4
#define S3 5
#define sensorOut 6
Servo topServo;
Servo bottomServo;
int frequency = 0;
int color=0;
void setup() {
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(sensorOut, INPUT);
  // Setting frequency-scaling to 20%
  digitalWrite(S0, HIGH);
  digitalWrite(S1, LOW);
  topServo.attach(7);
  bottomServo.attach(8);
  Serial.begin(9600);
}
void loop() {
  topServo.write(115);
  delay(5000);
  
  for(int i = 115; i > 65; i--) {
    topServo.write(i);
    delay(2);
  }
  delay(10000);
  
  color = readColor();
  delay(10);  
  switch (color) {
    case 1:
    Serial.print(color);
    bottomServo.write(50);
    break;
    case 2:
    Serial.print(color);
    bottomServo.write(75);
    break;
    case 3:
    Serial.print(color);
    bottomServo.write(100);
    break;
    case 4:
    Serial.print(color);
    bottomServo.write(125);
    break;
    case 5:
    Serial.print(color);
    bottomServo.write(150);
    break;
    case 6:
    Serial.print(color);
    bottomServo.write(175);
    break;
    case 0:
    break;
  }
  delay(300);
  
  for(int i = 65; i > 29; i--) {
    topServo.write(i);
    delay(2);
  } 
  delay(200);
  
  for(int i = 29; i < 115; i++) {
    topServo.write(i);
    delay(2);
  }
  color=0;
}
// Custom Function - readColor()
int readColor() {
  // Variables to store frequencies for R, G, and B
  int R, G, B;

  // Setting red filtered photodiodes to be read
  digitalWrite(S2, LOW);
  digitalWrite(S3, LOW);
  // Reading the output frequency
  R = pulseIn(sensorOut, LOW);
  // Printing the value on the serial monitor
  Serial.print("R= ");
  Serial.print(R);
  Serial.print("  ");
  delay(50);

  // Setting Green filtered photodiodes to be read
  digitalWrite(S2, HIGH);
  digitalWrite(S3, HIGH);
  // Reading the output frequency
  G = pulseIn(sensorOut, LOW);
  // Printing the value on the serial monitor
  Serial.print("G= ");
  Serial.print(G);
  Serial.print("  ");
  delay(50);

  // Setting Blue filtered photodiodes to be read
  digitalWrite(S2, LOW);
  digitalWrite(S3, HIGH);
  // Reading the output frequency
  B = pulseIn(sensorOut, LOW);
  // Printing the value on the serial monitor
  Serial.print("B= ");
  Serial.print(B);
  Serial.println("  ");
  delay(50);

  // Checking which color is detected based on frequency readings
   if(R<80 & R>50 & G<110 & G>80){
    color = 1; // Red
  }
  if(G<55 & G>43 & B<47 &B>35){
    color = 2; // Orange
  }
  if(R<60 & R>80 & G<103 & G>80){
    color = 3; // Green
  }
  if(R<70 & R>60 & G<90 & G>75){
    color = 4; // Yellow
  }
  if(R<56 & R>46 & G<65 & G>55){
    color = 5; // Brown
  }
  if (G<80 & G>105 & B<60 &B>96){
    color = 6; // Blue
  }
  return color;  
}
