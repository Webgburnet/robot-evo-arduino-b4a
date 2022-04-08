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
int Clav;

Servo Servo_G;
Servo Servo_D;

const int MIN=500; 
const int MAX=1000; 

int Pos_D, Pos_G;

void setup()
{
  Serial.println("Debut setup");
  pinMode( LedPin , OUTPUT);
  pinMode( BuzzerPin , OUTPUT);
  pinMode(switchPin, INPUT);
  pinMode (Servo_DPin,OUTPUT);
  pinMode (Servo_GPin,OUTPUT);
  Serial.begin(115200);
  mavoieserie.begin(115200);
  Pos_G=Servo_G.read();
  Serial.println(Pos_G);
  Pos_D=Servo_D.read();
  Serial.println(Pos_D);
  delay (1000);
  Serial.print("Pad=");
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
          Serial.print("Pad=");
          Serial.println(Pad);
      if (Pad == 'Z' )
      {
        //Avancer();
        Serial.print("Avancer");
        Serial.println();
        Servo_G.attach(Servo_GPin);
        Servo_G.write(MAX);
        Servo_D.attach(Servo_DPin);
        Servo_D.write(MIN);
      }
      if (Pad=='Q')
      {
        //Gauche();
        Serial.print("Droite");
        Serial.println();
        Servo_G.attach(Servo_GPin);
        Servo_G.write(MAX);
        Servo_D.attach(Servo_DPin);
        Servo_D.write(MAX);
      }
      if (Pad =='S')
      {
        //Reculer();
        Serial.print("Reculer");
        Serial.println();
        Servo_G.attach(Servo_GPin);
        Servo_G.write(MIN);
        Servo_D.attach(Servo_DPin);
        Servo_D.write(MAX);
      }
      if (Pad=='D')
      {
        //Droite();
        Serial.print("Gauche");
        Serial.println();
        Servo_G.attach(Servo_GPin);
        Servo_G.write(MIN);
        Servo_D.attach(Servo_DPin);
        Servo_D.write(MIN);
      }
       if (Pad == 'B' ) //Start
      {
        //Stop();
        Serial.print("STOP");
        Serial.println();
        //Stop();
        Servo_G.detach();
        Servo_D.detach();
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
