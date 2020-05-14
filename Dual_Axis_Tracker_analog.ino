
#include <Servo.h> // include Servo library 

// 180 horizontal MAX
Servo horizontal; // horizontal servo
int servoh = 65;   // 65;     // stand horizontal servo
int servohLimitHigh = 130;
int servohLimitLow = 0;
int servoPinh = 9;
int feedbackPinh = A4;
int feedbackValueh;
int angle; 
 
// 180 degrees MAX
Servo vertical;   // vertical servo 
int servov = 114;    //   114;     // stand vertical servo

int servovLimitHigh = 135;
int servovLimitLow = 5;
// Control and feedback pins
int servoPinv = 10;
int feedbackPinv = A5;
int altitude; 
int feedbackValuev;
// LDR pin connections
//  name  = analogpin;
int ldrlt =A0; //LDR top left - BOTTOM LEFT    <--- BDG
int ldrrt =A1; //LDR top right - BOTTOM RIGHT 
int ldrld =A2; //LDR down left - TOP LEFT
int ldrrd =A3; //ldr down right - TOP RIGHT

void setup()
{
  Serial.begin(9600);
// servo connections
// name.attacht(pin);
  horizontal.attach(9); 
  vertical.attach(10);
  horizontal.write(65);
  vertical.write(114);
  //horizontal
    // Read value from feedback signal
   // feedbackValueh = analogRead(feedbackPinh);
   // angle=map(feedbackValueh,84,424,-90,90);
    // Write value to serial monitor
  /*  Serial.print("Position = ");
    Serial.print(angle);
    Serial.print("\t");
    Serial.println(feedbackValueh);*/
    
  //vertical
  
    
    // Read value from feedback signal
  //  feedbackValuev = analogRead(feedbackPinv);
  //  altitude=map(feedbackValuev,127,492,8,120);
    // Write value to serial monitor
 /*   Serial.print("Position = ");
    Serial.print(servoPos);
    Serial.print("\t");
    Serial.print(" altitude = ");
    Serial.print(altitude);
    Serial.print("\t");
    Serial.println(feedbackValuev);*/
  //micro analogservo 8moires ->127 , ,90MOIRES  392,120moires ->487
   delay(3000);
   
  Serial.print(" altitude ,");Serial.println("azimuth = ");
  }
 
  
  


void loop() 
{
  feedbackValueh = analogRead(feedbackPinh);
    angle=map(feedbackValueh,84,424,-90,90);
    feedbackValuev = analogRead(feedbackPinv);
    altitude=map(feedbackValuev,127,492,8,120);
  int lt = analogRead(ldrlt); // top left
  int rt = analogRead(ldrrt); // top right
  int ld = analogRead(ldrld); // down left
  int rd = analogRead(ldrrd); // down rigt
  
  // int dtime = analogRead(4)/20; // read potentiometers  
  // int tol = analogRead(5)/4;
  int dtime = 10;
  int tol = 50;
  
  int avt = (lt + rt) / 2; // average value top
  int avd = (ld + rd) / 2; // average value down
  int avl = (lt + ld) / 2; // average value left
  int avr = (rt + rd) / 2; // average value right

  int dvert = avt - avd; // check the diffirence of up and down
  int dhoriz = avl - avr;// check the diffirence og left and rigt
  
  
 /*  Serial.print(lt);
  Serial.print(" ");
  Serial.print(rt);
  Serial.print(" ");
  Serial.print(ld);
  Serial.print(" ");
  Serial.print(rd);
  Serial.print("   ");
 // Serial.print(avt);
 // Serial.print("   ");
 // Serial.print(avd);
 // Serial.println(" ");
  Serial.print(avt);
  Serial.print("   ");
  Serial.print(avd);
  Serial.println(" ");*/
  
    
  if (-1*tol > dvert || dvert > tol) // check if the diffirence is in the tolerance else change vertical angle
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
 // Serial.print(" altitude = ");
    Serial.print(altitude);
    Serial.print(" , ");
    Serial.println(angle);
    delay(35);
  }
  
  if (-1*tol > dhoriz || dhoriz > tol) // check if the diffirence is in the tolerance else change horizontal angle
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
    // nothing
  }
  horizontal.write(servoh);
 // Serial.print("azimuth = ");
 Serial.print(altitude);
    Serial.print(" , ");
    Serial.println(angle);
    
    
  }
   delay(dtime);

}
