#include <BlynkSimpleEsp32.h>
#include <WiFi.h>
#include <WiFiClient.h>
#include <HCSR04.h>

#define BLYNK_TEMPLATE_ID "TMPL6pWt7q3BD"
#define BLYNK_TEMPLATE_NAME "syringe"
#define BLYNK_AUTH_TOKEN "Y_BEAfdwT7RQ1k17l8V2sgODGxK488bg"
char auth[] = "Y_BEAfdwT7RQ1k17l8V2sgODGxK488bg";
#define BLYNK_PRINT Serial
#define DIR 22
#define STEP 23
#define ENABLE 21

HCSR04 hc(12, 13); 
WidgetTerminal terminal(V8);
WidgetLED ledOn(V0);
WidgetLED ledAlarm(V6);
BlynkTimer timer;

//#include "SparkTime.h"
//UDP UDPClient;
//SparkTime rtc;

String Start,Stop,Day;
int Distance = 0;
double Dist =0;
long mlpersec = 2; 
// 1ml/sec = 500 count per delay 1000 ms -- 1 count delay 2 ms
// 10 ml/sec = 5000 count per 1000 ms  -- 1 count delay 1/5 ms

int state = 0; // 0 stop on 1 purge 2 return
int ml2count = 500; // need to find out 
double volume = 1; // 1 ml
double Speed  = 1; // 1ml/sec

char ssid[] = "iPhone (3)";
char pass[] = "12345679";


BLYNK_WRITE(V1) // pumpon
{
  int value = param.asInt();
  Serial.print("PUMPON : ");
  Serial.println(value);
  digitalWrite(2, value);
  state = 1; 
//  if (value = 1){ledOn.on();}
//  else if(value = 0){ledOn.off();}
}
BLYNK_WRITE(V2) //purge
{
  int value = param.asInt();
  Serial.print("PURGE : ");
  Serial.println(value);
  digitalWrite(2, value);
  state = 2;
}
BLYNK_WRITE(V3) //return
{
  int value = param.asInt();
  Serial.print("RETURN : ");
  Serial.println(value);
  digitalWrite(2, value);
  state = 3;
}
BLYNK_WRITE(V4) //volume
{
  volume = param.asDouble();
  Serial.print("Volume : ");
  Serial.println(volume);
 
}
BLYNK_WRITE(V5) //speed
{
  Speed = param.asDouble();
  Serial.print("Speed : ");
  Serial.println(Speed);
  //mlpersec = f(speed)
//  Speed = mlpersec/ml2count;
  mlpersec = (Speed/ml2count)*100;
//  mlpersec = ml2count/Speed;
  Serial.print("Delay : ");
  Serial.println(mlpersec);
}

void myTimerEvent()
{
  Blynk.virtualWrite(V7, Distance/750); // injectMl
}


void setup()
{
  // Debug console
  Serial.begin(115200);
  Serial.println("Syringe Pump Release 1.0 ");
  terminal.println("Syringe Pump Release 1.0 ");
  
  pinMode(DIR, OUTPUT); // dir
  pinMode(STEP, OUTPUT); // step
  pinMode(ENABLE, OUTPUT); // enable
  digitalWrite(DIR, LOW);
  digitalWrite(STEP, LOW);
  digitalWrite(ENABLE, HIGH); // HIGH motor enable
  pinMode(2,OUTPUT);
  
  Blynk.begin(auth, ssid, pass, "blynk.cloud", 80);
  // Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
  timer.setInterval(1000L, myTimerEvent);
  //terminal.clear();
}

 

void loop()
{
  Blynk.run();
  timer.run();
  
  Dist = hc.dist();
  Serial.print("Dist : ");
  Serial.print(Dist);
  Serial.print(" mlpersec Delay : ");
  Serial.print(mlpersec);
  //terminal.print("Dist : ");
  //terminal.println(Dist);
  
//  Serial.println(Distance);
//  delay(50);
  if (state ==0){
    MotorStoP();}
    
  else if (state ==1){ 
  digitalWrite(ENABLE,HIGH);
  MotorOneStep();}
  
  else if (state ==2){
  digitalWrite(ENABLE,HIGH);
  MotorPurge();}  
  
  else if (state ==3){
  digitalWrite(ENABLE,HIGH); 
  MotorReturn();}
  
  else{MotorStoP();}

  myTimerEvent();
}


 
void MotorOneStep(){
  Dist = hc.dist();
  Serial.println("  Motor: one step is working ");
  // terminal.println("Motor: one step is working ");
  digitalWrite(DIR, HIGH);
  digitalWrite(STEP, HIGH);
  delayMicroseconds(50);
  digitalWrite(STEP, LOW);
  delayMicroseconds(50);
  delay(mlpersec); 
  
  Distance = Distance +1 ;
  if  (Dist >= volume*ml2count){ // 1 ml or 500 count stop motor stop
    state = 0;
    Serial.print("Dist : ");
    Serial.println(Dist);
    }



  }
  
void MotorPurge(){
  Dist = hc.dist();
  Serial.println(" Motor: Purge is working ");
  // terminal.println("Motor: Purge is working ");
  digitalWrite(DIR, HIGH);
  digitalWrite(STEP, HIGH);
  delayMicroseconds(25);
  digitalWrite(STEP, LOW);
  delayMicroseconds(25);
  delay(2);
  
  if( Dist >= 9.2)
  { state =0;
    Serial.println("In max --- stop");
    Serial.print("Dist : ");
    Serial.println(Dist);
   }
 }
  
void MotorReturn(){
  Serial.println(" Motor: Return is working ");
  // terminal.println("Motor: Return is working ");
  Dist = hc.dist();
  digitalWrite(DIR, LOW);
  digitalWrite(STEP, HIGH);
  delayMicroseconds(25);
  digitalWrite(STEP, LOW);
  delayMicroseconds(25);
  delay(2);
  
  if(Dist <= 2.5)
  { state =0;
    Serial.println("out max --- stop");
    Serial.print("Dist : ");
    Serial.println(Dist);
    }
  }
  
void MotorStoP(){
  digitalWrite(ENABLE,LOW);
  Serial.println(" Motor: stop ");
  }
