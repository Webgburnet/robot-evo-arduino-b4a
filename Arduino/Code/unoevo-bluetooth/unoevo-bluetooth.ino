#include <Servo.h>
#include <SoftwareSerial.h>

#define RX_pin 2
#define TX_pin 3
#define switchPin 4
#define LedPin 5
#define BuzzerPin 6
#define Servo_GPin 8
#define Servo_DPin 9


SoftwareSerial mavoieserie(RX_pin, TX_pin); // (RX, TX) (pin Rx BT, pin Tx BT)

int Tension=0;
int Pad;

Servo Servo_G;
Servo Servo_D;

int Pos_D, Pos_G;

void setup()
{
  
  pinMode( LedPin , OUTPUT);
  pinMode( BuzzerPin , OUTPUT);
  pinMode(switchPin, INPUT);
  Serial.begin(115200);
  mavoieserie.begin(115200);
  Serial.println("Debut setup");
  Servo_G.attach(Servo_GPin, 0, 1000);
  Servo_D.attach(Servo_DPin, 0, 1000);
  Pos_G=Servo_G.read();
  Serial.println(Pos_G);
  Pos_D=Servo_D.read();
  Serial.println(Pos_D);
  Servo_G.write(86);
  Servo_D.write(86);
  delay (1000);
  Serial.println(Pad);

  digitalWrite(LedPin , LOW);
  digitalWrite(BuzzerPin , LOW);
  Serial.println("Fin setup");
}

void loop()
{
  Tension = digitalRead(switchPin);
  if (Tension==HIGH)
  {
    //Serial.println("Sous tension");
    if (mavoieserie.available()>0) {
          //Serial.println("Telephone");
          Pad=mavoieserie.read();
          Serial.println(Pad);
      if (Pad == 'Z' )
      {
        //Avancer();
        Serial.print("Avancer");
        Serial.println();
        Servo_G.write(1000);
        Servo_D.write(500);
      }
      
      if (Pad=='Q')
      {
        //Gauche();
        Serial.print("Reculer");
        Serial.println();
        Servo_G.write(500);
        Servo_D.write(500);
      }
      if (Pad =='S')
      {
        //Reculer();
        Serial.print("Reculer");
        Serial.println();
        Servo_G.write(500);
        Servo_D.write(1000);
      }
      if (Pad=='D')
      {
        //Droite();
        Serial.print("Droite");
        Serial.println();
        Servo_G.write(1000);
        Servo_D.write(1000);
      }
       if (Pad == 'B' ) //Start
      {
        //Stop();
        Serial.print("STOP");
        Serial.println();
        //Stop();
        Servo_G.write(86);
        Servo_D.write(86);
      }
      if (Pad=='L') //Croix
      {
        digitalWrite(LedPin, HIGH);
      }
      if (Pad=='F') //Rond
      {
        digitalWrite(LedPin, LOW);
      }
      if (Pad=='R')
      {
        digitalWrite(BuzzerPin,HIGH);
        delay(300);
        digitalWrite(BuzzerPin,LOW);
      }
    }
  }

  else
  {
    //Serial.println("Hors tension");
    //Stop();
    Servo_G.write(86);
    Servo_D.write(86);
  }
}
