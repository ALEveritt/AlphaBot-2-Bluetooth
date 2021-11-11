#include <SoftwareSerial.h>

SoftwareSerial mySerial(10, 11); // RX, TX

#define PWMA   6           //Left Motor Speed pin (ENA)
#define AIN2   A0          //Motor-L forward (IN2).
#define AIN1   A1          //Motor-L backward (IN1)
#define PWMB   5           //Right Motor Speed pin (ENB)
#define BIN1   A2          //Motor-R forward (IN3)
#define BIN2   A3          //Motor-R backward (IN4)
#define PIN 7

String comdata = "";
int Speed = 60;
uint16_t i, j;
unsigned long lasttime = 0;

void forward();
void backward();
void right();
void left();
void stop();

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  mySerial.begin(115200);

  pinMode(PWMA,OUTPUT);                     
  pinMode(AIN2,OUTPUT);      
  pinMode(AIN1,OUTPUT);
  pinMode(PWMB,OUTPUT);       
  pinMode(AIN1,OUTPUT);     
  pinMode(AIN2,OUTPUT);  

  Serial.println("Bluetooth control example");
  stop();
}

void loop() {
  // put your main code here, to run repeatedly:
  while (mySerial.available() > 0)  
  {
    comdata += char(mySerial.read());
    delay(2);
  }
  if (comdata.length() > 0)
  {
    Serial.println(comdata);
    comdata.trim();
    const char* command = comdata.c_str();

    if(comdata == "Forward")          //Forward
    {
      forward();
    }
    else if(strcmp(command,"Backward") == 0)    //Backward
    {
      backward();
    }
    else if(strcmp(command,"Left") == 0)        //Left
    {
      left();
    }
    else if(strcmp(command,"Right") == 0)       //Right
    {
      right();
    }
    else if(strcmp(command,"Stop") == 0)        //Stop
    {
      stop();
    }
    else if(strcmp(command,"Low") == 0)
    {                                           //Low
      Speed = 40;
    }
    else if(strcmp(command,"Medium") == 0)   
    {                                           //Medium
      Speed = 60;
    }
    else if(strcmp(command,"High") == 0)  
    {                                           //High
      Speed = 75;
    }
    comdata = "";
  }
}

void forward()
{
  analogWrite(PWMA,Speed);
  analogWrite(PWMB,Speed);
  digitalWrite(AIN1,LOW);
  digitalWrite(AIN2,HIGH);
  digitalWrite(BIN1,LOW);  
  digitalWrite(BIN2,HIGH); 
}

void backward()
{
  analogWrite(PWMA,Speed);
  analogWrite(PWMB,Speed);
  digitalWrite(AIN1,HIGH);
  digitalWrite(AIN2,LOW);
  digitalWrite(BIN1,HIGH); 
  digitalWrite(BIN2,LOW);  
}

void right()
{
  analogWrite(PWMA,40);
  analogWrite(PWMB,40);
  digitalWrite(AIN1,LOW);
  digitalWrite(AIN2,HIGH);
  digitalWrite(BIN1,HIGH); 
  digitalWrite(BIN2,LOW);  
}

void left()
{
  analogWrite(PWMA,40);
  analogWrite(PWMB,40);
  digitalWrite(AIN1,HIGH);
  digitalWrite(AIN2,LOW);
  digitalWrite(BIN1,LOW); 
  digitalWrite(BIN2,HIGH);  
}

void stop()
{
  analogWrite(PWMA,0);
  analogWrite(PWMB,0);
  digitalWrite(AIN1,LOW);
  digitalWrite(AIN2,LOW);
  digitalWrite(BIN1,LOW); 
  digitalWrite(BIN2,LOW);  
}
