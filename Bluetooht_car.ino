
#include <AFMotor.h>
#include <SoftwareSerial.h>
SoftwareSerial port(9,10);


AF_DCMotor motor1(1);
AF_DCMotor motor2(2);
AF_DCMotor motor3(3);
AF_DCMotor motor4(4);

int Speed = 250;
char value;
char val,valeur ;
const int ledPin = 13; // the pin that the LED is attached to
int incomingByte;      // a variable to read incoming serial data into


void setup() {
  Serial.begin(9600);
port.begin(9600);

  motor1.setSpeed(Speed);
  motor2.setSpeed(Speed);
  motor3.setSpeed(Speed);
  motor4.setSpeed(Speed);



}

void loop() {
  if (Serial.available() > 0) {
    // read the oldest byte in the serial buffer:
 

  
 
    val = Serial.read();
}
  if ((val == 'U')or (val == 'F')) {
    motor1.run(FORWARD);
    motor2.run(FORWARD);
    motor3.run(FORWARD);
    motor4.run(FORWARD);
  Serial.println("FFF");
    Serial.println("FFF");
    Serial.println("FFF");
    Serial.println("FFF");
    Serial.println("FFF");
    Serial.println("FFF");
     
  }
   
  else if ((val == 'D')or (val == 'B')) {
    motor1.run(BACKWARD);
    motor2.run(BACKWARD);
    motor3.run(BACKWARD);
    motor4.run(BACKWARD);
   Serial.println("BBB");
    Serial.println("BBB");
    Serial.println("BBB");
    Serial.println("BBB");
    Serial.println("BBB");
    Serial.println("BBB");
    
  } else if (val == 'R') {
    motor1.run(BACKWARD);
    motor2.run(BACKWARD);
    motor3.run(FORWARD);
    motor4.run(FORWARD);
      Serial.println("RRR");
    Serial.println("RRR");
    Serial.println("RRR");
    Serial.println("RRR");
    Serial.println("RRR");
    Serial.println("RRR");
    
  } else if (val == 'L') {
    motor1.run(FORWARD);
    motor2.run(FORWARD);
    motor3.run(BACKWARD);
    motor4.run(BACKWARD);
 
    Serial.println("LLL");
    Serial.println("LLL");
    Serial.println("LLL");
     Serial.println("LLL");
    Serial.println("LLL");
    Serial.println("LLL");
    
  }
  
  else {
    motor1.run(RELEASE);
    motor2.run(RELEASE);
    motor3.run(RELEASE);
    motor4.run(RELEASE);
  }

 if (port.available() > 0) {
    // read the oldest byte in the serial buffer:
 

  
 
    valeur = port.read();
}
  if ((valeur == 'U')or(valeur == 'F')) {
    motor1.run(FORWARD);
    motor2.run(FORWARD);
    motor3.run(FORWARD);
    motor4.run(FORWARD);
  Serial.println("FFF");
    Serial.println("FFF");
    Serial.println("FFF");
    Serial.println("FFF");
    Serial.println("FFF");
    Serial.println("FFF");
     
  }
   
  else if ((valeur == 'D')or(valeur == 'B')) {
    motor1.run(BACKWARD);
    motor2.run(BACKWARD);
    motor3.run(BACKWARD);
    motor4.run(BACKWARD);
   Serial.println("BBB");
    Serial.println("BBB");
    Serial.println("BBB");
    Serial.println("BBB");
    Serial.println("BBB");
    Serial.println("BBB");
    
  } else if (valeur == 'L') {
   motor1.run(FORWARD);
    motor2.run(FORWARD);
    motor3.run(BACKWARD);
    motor4.run(BACKWARD);
 
    Serial.println("LLL");
    Serial.println("LLL");
    Serial.println("LLL");
     Serial.println("LLL");
    Serial.println("LLL");
    Serial.println("LLL");
    
  } else if (valeur == 'R') {
     motor1.run(BACKWARD);
    motor2.run(BACKWARD);
    motor3.run(FORWARD);
    motor4.run(FORWARD);
      Serial.println("RRR");
    Serial.println("RRR");
    Serial.println("RRR");
    Serial.println("RRR");
    Serial.println("RRR");
    Serial.println("RRR");
    
  }
  
  else {
    motor1.run(RELEASE);
    motor2.run(RELEASE);
    motor3.run(RELEASE);
    motor4.run(RELEASE);
  }
 
  
}


    

    
    
