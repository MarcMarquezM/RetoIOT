// INTENTO DE AGREGAR SENSORES DE TEMPERATURA Y LUZ
// AGREGAR FUNCIONES DE CODIGO AL IGUAL QUE CON BLYNK
// MOVIMIENTO DE SERVO REFINIDO
#define BLYNK_PRINT Serial

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

char auth[] = "92ZcEX4J8U-uP5Dy56GmtyE5KphmnMYp";

// Your WiFi credentials.
char ssid[] = "INFINITUM1DC6_2.4";
char pass[] = "Mp83485845";

#include <Servo.h>

Servo servo1;
Servo servo2;

int pos1 = 0;
int pos2 = 0;

#define button1 D1
#define button2 D2

#define LED1 D3
#define LED2 D4

// Button State 1
int buttonState1 = 0;
int directionState1 = 0;

// Button State 2
int buttonState2 = 0;
int directionState2 = 0;

int pinValue1; // Virtual Button 1 // SERVO 1
int pinValue2; // Virtual Button 2 // SERVO 2

BLYNK_WRITE(V1) // V1 is the number of Virtual Pin SERVO 1
{
  pinValue1 = param.asInt();
}

BLYNK_WRITE(V2) // V2 is the number of Virtual Pin SERVO 2
{
  pinValue2 = param.asInt();
}

WidgetLED led1(V3); // LED 1
WidgetLED led2(V4); // LED 2

int lightON = 180;
int lightOFF = 90;

void setup() {
  // Debug Console
  Serial.begin(9600);

  // SETUP FIRST BUTTON
  pinMode(button1, INPUT);
  pinMode(LED1, OUTPUT);
  servo1.attach(D7);

  // SETUP SECOND BUTTON
  pinMode(button2, INPUT);
  pinMode(LED2, OUTPUT);
  servo2.attach(D8);

  Blynk.begin(auth, ssid, pass);
}

void loop() {

  Blynk.run();

  // SERVO 1
  buttonState1 = digitalRead(button1);
  if (directionState1 == 0) {
    if (buttonState1 == HIGH || pinValue1 == 1) {
      directionState1 = 1;
      digitalWrite(LED1, HIGH);
      servo1.attach(D7);

      for (pos1 = lightOFF; pos1 <= lightON; pos1 = pos1 + 1) {
        servo1.write(pos1);
        delay(15);
      }

      //servoMove(pos1, servo1, true);

      servo1.detach();
      digitalWrite(LED1, LOW);
    }

  } else if (directionState1 == 1) {
    if (buttonState1 == HIGH || pinValue1 == 1) {
      directionState1 = 0;
      digitalWrite(LED1, HIGH);
      servo1.attach(D7);

      for (pos1 = lightON; pos1 >= lightOFF; pos1 = pos1 - 1) {
        servo1.write(pos1);
        delay(15);
      }

      //servoMove(pos1, servo1, false);

      servo1.detach();
      digitalWrite(LED1, LOW);
    }
  }

  if (servo1.read() == lightON) { // ESTADO LED 1 EN BLYNK
    led1.on();
  } else {
    led1.off();
  }



  // SERVO 2
  buttonState2 = digitalRead(button2);
  if (directionState2 == 0) {
    if (buttonState2 == HIGH || pinValue2 == 1) {
      directionState2 = 1;
      digitalWrite(LED2, HIGH);
      servo2.attach(D8);

      for (pos2 = lightOFF; pos2 <= lightON; pos2 = pos2 + 1) {
        servo2.write(pos2);
        delay(15);
      }

      //servoMove(pos2, servo2, true);
      
      servo2.detach();
      digitalWrite(LED2, LOW);
    }

  } else if (directionState2 == 1) {
    if (buttonState2 == HIGH || pinValue2 == 1) {
      directionState2 = 0;
      digitalWrite(LED2, HIGH);
      servo2.attach(D8);

      for (pos2 = lightON; pos2 >= lightOFF; pos2 = pos2 - 1) {
        servo2.write(pos2);
        delay(15);
      }

      //servoMove(pos2, servo2, false);
      
      servo2.detach();
      digitalWrite(LED2, LOW);
    }
  }

  if (servo2.read() == lightON) { // ESTADO LED 2 EN BLYNK
    led2.on();
  } else {
    led2.off();
  }
  
} // EN OF VOID LOOP



void servoMove(int pos, Servo servo, bool OnOff) {

  if (OnOff == true) {

    for (pos = 90; pos <= 180; pos = pos + 1) {
      servo.write(pos);
      delay(15);
    } 

  } else if (OnOff == false) {
    
    for (pos = 180; pos >= 90; pos = pos - 1) {
      servo.write(pos);
      delay(15);
    }
    
  } // END ELSE
  
} // END FUNCTION
