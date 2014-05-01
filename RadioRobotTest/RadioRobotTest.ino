#include <BFFRadioReceiver.h>
#include <SPI.h>
#include <Mirf.h>
#include <nRF24L01.h>
#include <MirfHardwareSpiDriver.h>
#include <Servo.h>

boolean ButtonAPressed = false;
boolean ButtonBPressed = false;
boolean ButtonJoystickPressed = false;
boolean RadioInContact = false;
byte Throttle = 127;
int JoystickForwardBack = 0;
int JoystickLeftRight = 0;

#define RadioMISO 12
#define RadioMOSI 11
#define RadioSCK 13

#define RadioCE 8
#define RadioCSN 7

#define ServoPinA 4
Servo ServoA;

BFFRadioReceiver radio(RadioMISO, RadioMOSI, RadioSCK, RadioCE, RadioCSN);

void setup(){
  Serial.begin(9600);
  radio.init(&ButtonAPressed, &ButtonBPressed, &ButtonJoystickPressed, &RadioInContact,
             &Throttle, &JoystickForwardBack, &JoystickLeftRight);
  
  ServoA.attach(ServoPinA, 1000, 2000);
  
  Serial.println("Beginning ... "); 
}

void loop(){
  int rad = radio.update();
  
  Serial.println(rad);
  
  Serial.print("A: ");
  Serial.print(ButtonAPressed);
  Serial.print(" B: ");
  Serial.print(ButtonBPressed);
  Serial.print(" J: ");
  Serial.println(ButtonJoystickPressed);
  
  Serial.print("Throttle: ");
  Serial.print(Throttle);
  Serial.print(" X: ");
  Serial.print(JoystickLeftRight);
  Serial.print(" Y: ");
  Serial.println(JoystickForwardBack);
  
  ServoA.writeMicroseconds(map(Throttle, 0, 255, 1000, 2000));
  
  delay(200);
 }