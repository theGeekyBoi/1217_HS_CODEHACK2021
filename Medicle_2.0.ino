const int buzz = 2;
#define echoPin 4
#include <dht.h>
#include <Wire.h>
#include "MAX30105.h"
#define DHT11PIN 4
dht DHT11;
MAX30105 particleSensor;
#define trigPin 3
int temperature;
String mock;
#include <SoftwareSerial.h>
int sensorValue; 
int HRV;
int humidity;
int metre;
const int lPlus = 10;
const int lMinus = 11;
long duration; 
char sbuffer[14], ch;
unsigned char pos;
unsigned char read1, read2, read3;
boolean newData=false;
int distance;
int mobile;
int c = 1;  
int a;
String Name;  
int Weight;
int bpm;
int bmi;
int finHeight;
#include <dht.h>
#define dht_apin A0
dht DHT;
void setup() {
  pinMode(buzz, OUTPUT);
  pinMode(lPlus, INPUT);
  pinMode(lMinus, INPUT);
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Serial.println("Please fill in the details");  
  while(!Serial); //We must wait for Teensy to come online
  delay(100);
  Serial.println("");
  Serial.println("MAX30102");
  Serial.println("");
  delay(100);
  // Initialize sensor
  if (particleSensor.begin(Wire, I2C_SPEED_FAST) == false) //Use default I2C port, 400kHz speed
  {
    Serial.println("MAX30105 was not found. Please check wiring/power. ");
    while (1);
}
byte ledBrightness = 70; //Options: 0=Off to 255=50mA
byte sampleAverage = 1; //Options: 1, 2, 4, 8, 16, 32
byte ledMode = 2; //Options: 1 = Red only, 2 = Red + IR, 3 = Red + IR + Green
int sampleRate = 400; //Options: 50, 100, 200, 400, 800, 1000, 1600, 3200
int pulseWidth = 69; //Options: 69, 118, 215, 411
int adcRange = 16384; //Options: 2048, 4096, 8192, 16384
particleSensor.setup(ledBrightness, sampleAverage, ledMode, sampleRate, pulseWidth, adcRange); //Configure sensor with these settings

void loop() {
  Serial.print("Patient ");
  Serial.println(c);
  

  inp();
  
  Serial.println("Stand up straight");   
  delay(3000); 
  height();
  Serial.println("Place finger on Oximeter");
  MAX();
  metre = finHeight/100;
  bmi = Weight/(metre*metre);
  Serial.println("Breathe on the blue sensor");
  temp();
  displayDetails();
  Serial.println("--------------------------------");
  Serial.println("Please exit Medicle");
  Serial.println("--------------------------------");
  Serial.println("");
  c++;
  
  
}  
void height()
{
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;
  if(distance > 250){
    distance = 0;
  }
  finHeight = 250 - distance;

  
}
void inp()
{
  
  if(c == 1)
  {
  Name = "";
  Weight = "";
  Serial.println("Enter your Name");  
  while (Serial.available() == 0) {}  
  Name = Serial.readString();
  Serial.println("Enter your Weight");  
  while (Serial.available() == 0) {}  
  Weight = Serial.parseInt();
  }
  else
  {
  Name = "";
  Weight = "";
  Serial.println("Please fill in the details");  
  while (Serial.available() == 0) {}  
  mock = Serial.readString();
  Serial.println("Enter your Name");  
  while (Serial.available() == 0) {}  
  Name = Serial.parseInt();
  Serial.println("Enter your Weight");  
  while (Serial.available() == 0) {}  
  Weight = Serial.parseInt();
  }
}
void MAX()
{
  particleSensor.check(); //Check the sensor
  while (particleSensor.available()) {
      // read stored IR
      Serial.print(particleSensor.getFIFOIR());
      Serial.print(",");
      // read stored red
      Serial.println(particleSensor.getFIFORed());
      // read next set of samples
      particleSensor.nextSample();      
}
void displayDetails()
{
  Serial.println("");
  Serial.println("__________");
  Serial.println("Report - ");
  Serial.println("");
  Serial.print(Name);
  Serial.print("Weight: ");
  Serial.print(Weight);
  Serial.println(" Kg");
  Serial.print("Height: ");
  Serial.print(finHeight);
  Serial.println(" cm");
  Serial.print("BPM: ");
  Serial.print(bpm);
  Serial.println(" bpm");
  Serial.print("BMI: ");
  Serial.println(bmi);
  if(bmi > 25)
  {
    Serial.println("You have a high BMI, you are Overweight");
  }
  else if(bmi < 18.5)
  {
    Serial.println("You have a low BMI, you are Underweight");
  }
  else
  {
    Serial.println("Healthy BMI");
  }
  Serial.print("Temperature Estimate: ");
  Serial.print(temperature);
  Serial.println(" Celsius");
  if(temperature < 34)
  {
    Serial.println("Body Temperature low, use a thermometer for a more accurate reading");
  }
  else if(temperature > 38.5)
  {
    Serial.println("Body Temperature High, use a thermometer for a more accurate reading");
  }
  else
  {
    Serial.println("Body Temperature Healthy");
  }
  Serial.print("Moisture: ");
  Serial.print(humidity);
  Serial.println(" %");
  if(humidity < 80)
  {
    Serial.println("Dehydrated - drink more water");
  }
  else
  {
    Serial.println("Hydrated - good job");
  }
  Serial.print("Heart Rate Variability ");
  Serial.println(HRV);
  Serial.println("Blood Pressure");
  Serial.println(read1);
  Serial.println(read2);
  Serial.println(read3);
  newData = false;
  delay(3000);
  Serial.println("Would you like to be sent an SMS with all of your details");
  Serial.print("");  
  while (Serial.available() == 0) {}  
  a = Serial.parseInt();
  Serial.println("1 for yes, 2 for no");
  while (Serial.available() == 0) {} 
  a = Serial.parseInt();
  if(a == 1)
  {
    Serial.println("Enter mobile no.");
    while (Serial.available() == 0) {} 
    mobile = Serial.parseInt();
    delay(100);
    delay(4900);
    Serial.println("SMS sent");
    delay(500);
    Serial.println("Thank you for using Medicle");
  }
  else
  {
    Serial.println("Thank you for using Medicle");
  }
  
  delay(2500);
  Serial.println("Thank you for using Medicle");
  Serial.println();
  Serial.println();
  Serial.println();
  Serial.println();
  Serial.println();
  Serial.println();
  Serial.println();
  Serial.println();
  Serial.println();
  Serial.println();
  Serial.println();
  Serial.println();
  Serial.println();
  Serial.println();
  Serial.println();
  Serial.println();
  Serial.println();
  Serial.println();
  Serial.println();
  Serial.println();
  Serial.println();
  Serial.println();
  Serial.println();
  Serial.println();
  Serial.println();
  Serial.println();
  Serial.println();
  Serial.println();
  Serial.println();
  Serial.println();
  Serial.println();
  Serial.println();
  Serial.println();
  Serial.println();
  Serial.println();
  Serial.println();
  Serial.println();
  Serial.println();
  Serial.println();
  Serial.println();
  Serial.println();
  Serial.println();
  Serial.println();
  Serial.println();
  Serial.println();
  Serial.println();
  Serial.println();
  Serial.println();
  Serial.println();
  Serial.println();
  Serial.println();
  Serial.println();
  Serial.println();
  Serial.println();
  Serial.println();
  Serial.println();
  Serial.println();
  Serial.println();
  Serial.println();
  Serial.println();
  Serial.println();
  Serial.println();
  Serial.println();
  Serial.println();
  Serial.println();
  Serial.println();
  Serial.println();
  Serial.println();
  Serial.println();
  Serial.println();
  Serial.println();
  Serial.println();
}
void temp()
{
  humidity = 0;
  temperature = 0;
  DHT.read11(dht_apin);
  DHT.read11(dht_apin);
  DHT.read11(dht_apin);
  humidity = DHT.humidity;
  temperature = DHT.temperature;
  delay(6000);
}
void ecg
{
  if((digitalRead(lPlus)==1)||(digitalRead(lMinus)==1)){
      Serial.print("");
  }
  else{
      HRV = (analogRead(A1));
  }
  delay(100);
}
void recvChar() {
if (Serial.available() > 0)
{

while(Serial.available()>0)
{
ch = Serial.read(); //loop till character received
if(ch==0x0A) // if received character is <LF>, 0x0A, 10 then process buffer
{
pos = 0; // buffer position reset for next reading
newData=true;
// extract data from serial buffer to 8 bit integer value
// convert data from ASCII to decimal
read1 = ((sbuffer[1]-'0')*100) + ((sbuffer[2]-'0')*10) +(sbuffer[3]-'0');
read2 = ((sbuffer[6]-'0')*100) + ((sbuffer[7]-'0')*10) +(sbuffer[8]-'0');
read3 = ((sbuffer[11]-'0')*100) + ((sbuffer[12]-'0')*10) +(sbuffer[13]-'0');
}
else
{ //store serial data to buffer
sbuffer[pos] = ch;
pos++;
}
}
}
}
