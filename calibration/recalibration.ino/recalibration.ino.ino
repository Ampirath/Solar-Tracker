#include <Servo.h>
 
// Control and feedback pins
int servoPin = 9;
int feedbackPin = A0;
int angle; 
// Value from feedback signal
int feedbackValue;
 
// Create a servo object
Servo myservo;
 
void setup()
{
  // Setup Serial Monitor
  Serial.begin(9600);
  
  // Attach myservo object to control pin
  myservo.attach(servoPin);
  
  // Home the servo motor
  myservo.write(0);
  
  
 
    for (int servoPos = 0; servoPos <=180; servoPos = servoPos + 3){
    
    // Position servo motor
    myservo.write(servoPos);
    // Allow time to get there
    delay(2000);
    
    // Read value from feedback signal
    feedbackValue = analogRead(feedbackPin);
    angle=map(feedbackValue,80,400,0,180);
    // Write value to serial monitor
    Serial.print("Position = ");
    Serial.print(angle);
    Serial.print("\t");
    Serial.println(feedbackValue);
  
  }
 
  // Move back to home position
  myservo.write(0);
  
  // Print to serial monitor when done
  Serial.println("Finished!");
 
}  
 
void loop()
{ 
myservo.write(0);
  
  
    for (int servoPos = 0; servoPos <=180; servoPos = servoPos + 3){
    
    // Position servo motor
    myservo.write(servoPos);
    // Allow time to get there
    delay(2000);
    
    // Read value from feedback signal
    feedbackValue = analogRead(feedbackPin);
    angle=map(feedbackValue,80,400,0,180);
 
    // Write value to serial monitor
    Serial.print("Position = ");
    Serial.print(angle);
    Serial.print("\t");
    Serial.println(feedbackValue);
  
  }
 
  // Move back to home position
  myservo.write(0);
  
  // Print to serial monitor when done
  Serial.println("Finished!");
  
}
