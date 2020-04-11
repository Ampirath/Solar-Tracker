#include <Servo.h> 

int feedbackPinv = A5;
int feedbackValuev;
int feedbackPinh = A4;
int feedbackValueh;

int altitude;
int angle;  


Servo horizontal; 
int servoh = 65;  
int servohLimitHigh = 130;
int servohLimitLow = 0;
int servoPin = 9;


Servo vertical;   
int servov = 114;   
int servovLimitHigh = 135;
int servovLimitLow = 5;
int servoPinv = 10;


int ldrlt =A0;   
int ldrrt =A1;
int ldrld =A2; 
int ldrrd =A3; 

void setup()
{
  Serial.begin(9600);
// servo connections
// name.attacht(pin);
  horizontal.attach(9); 
  vertical.attach(10);
  horizontal.write(65);
  vertical.write(114);
  delay(3000);

  Serial.print( ' altitude = ,');
  Serial.println('azimuth = ');
  
}

void loop() 
{
   feedbackValueh = analogRead(feedbackPinh);
   angle=map(feedbackValueh,84,424,-90,90);
   feedbackValuev = analogRead(feedbackPinv);
   altitude=map(feedbackValuev,127,492,8,120);
   
  int lt = analogRead(ldrlt); 
  int rt = analogRead(ldrrt); 
  int ld = analogRead(ldrld); 
  int rd = analogRead(ldrrd);
  
  
  int dtime = 10;
  int tol = 50;
  
  int avt = (lt + rt) / 2; 
  int avd = (ld + rd) / 2; 
  int avl = (lt + ld) / 2; 
  int avr = (rt + rd) / 2;
  
  int dvert = avt - avd; 
  int dhoriz = avl - avr;
  
  
    
  if (-1*tol > dvert || dvert > tol) 
  {
  if (avt > avd)
  {
    servov = ++servov;
     if (servov > servovLimitHigh) 
     { 
      servov = servovLimitHigh;
     }
  }
  else if (avt < avd)
  {
    servov= --servov;
    if (servov < servovLimitLow)
  {
    servov = servovLimitLow;
  }
  }
  vertical.write(servov);
  Serial.print(altitude);
  Serial.print(",");
  Serial.print(angle);
  delay(35);
  }
  
  if (-1*tol > dhoriz || dhoriz > tol) 
  {
  if (avr > avl)
  {
    servoh = ++servoh;
    if (servoh > servohLimitHigh)
    {
    servoh = servohLimitHigh;
    }
  }
  else if (avr < avl)
  {
    servoh = --servoh;
     if (servoh < servohLimitLow)
     {
     servoh = servohLimitLow;
     }
  }
  else if (avl = avr)
  {
    
  }
  horizontal.write(servoh);
  Serial.print(altitude);
  Serial.print(",");
  Serial.print(angle);
  
  }
   delay(dtime);

}
