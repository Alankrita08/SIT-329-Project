char t;
// Include the Servo library
#include <Servo.h> 
int water; //random variable 

// Declare the Servo pin
int servoPin = 4;
// Create a servo object
Servo Servo1;
void setup() {
pinMode(13,OUTPUT);   //left motors forward
pinMode(12,OUTPUT);   //left motors reverse
pinMode(11,OUTPUT);   //right motors forward
pinMode(10,OUTPUT); 
pinMode(3,OUTPUT); //output pin for relay board, this will sent signal to the relay
pinMode(6,INPUT); //input pin coming from soil sensor//right motors reverse
Serial.begin(9600);
 // We need to attach the servo to the used pin number
  Servo1.attach(servoPin);
}
 
void loop() {
 
if(t == 'F'){            //move forward(all motors rotate in forward direction)
  digitalWrite(13,HIGH);
  digitalWrite(11,HIGH);
}
 
else if(t == 'B'){      //move reverse (all motors rotate in reverse direction)
  digitalWrite(12,HIGH);
  digitalWrite(10,HIGH);
}
 
else if(t == 'L'){      //turn right (left side motors rotate in forward direction, right side motors doesn't rotate)
  digitalWrite(11,HIGH);
}
 
else if(t == 'R'){      //turn left (right side motors rotate in forward direction, left side motors doesn't rotate)
  digitalWrite(13,HIGH);
}

else if(t == 'W'){    //turn led on or off)
  digitalWrite(9,HIGH);
}
else if(t == 'w'){
  digitalWrite(9,LOW);
}
 
else if(t == 'S'){      //STOP (all motors stop)
  digitalWrite(13,LOW);
  digitalWrite(12,LOW);
  digitalWrite(11,LOW);
  digitalWrite(10,LOW);
}
delay(100);

if(Serial.available()){
  t = Serial.read();
  Serial.println(t);
}
 // Make servo go to 0 degrees
  Servo1.write(0);
  delay(1000);
  // Make servo go to 90 degrees
  Servo1.write(90);
  delay(1000);
  // Make servo go to 180 degrees
  Servo1.write(180);
  delay(1000);
   water = digitalRead(6);  // reading the coming signal from the soil sensor
  if(water == HIGH) // if water level is full then cut the relay 
  {
  digitalWrite(3,LOW); // low is to cut the relay
  }
  else
  {
  digitalWrite(3,HIGH); //high to continue proving signal and water supply
  }
  delay(400); 
}
