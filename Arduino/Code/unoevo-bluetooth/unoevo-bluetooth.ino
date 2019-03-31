#include <Servo.h>
#include <SoftwareSerial.h>

const int switchPin = 4;

SoftwareSerial mavoieserie(2, 3); // (RX, TX) (pin Rx BT, pin Tx BT)

int Tension=0;
int Pad;

Servo Servo_G;
Servo Servo_D;

int Pos_D, Pos_G;

void setup()
{
  pinMode( 5 , OUTPUT);
  pinMode( 6 , OUTPUT);
  pinMode(switchPin, INPUT);
  Serial.begin(115200);
  mavoieserie.begin(115200);
  Servo_G.attach(8, 0, 1000);
  Servo_D.attach(9, 0, 1000);
  Pos_G=Servo_G.read();
  Serial.println(Pos_G);
  Pos_D=Servo_D.read();
  Serial.println(Pos_D);
  Servo_G.write(86);
  Servo_D.write(86);
  delay (1000);
  Serial.println(Pad);

  digitalWrite(5 , LOW);
  digitalWrite(6 , LOW);
  
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
      else
      
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
        digitalWrite(5, HIGH);
      }
      if (Pad=='F') //Rond
      {
        digitalWrite(5, LOW);
      }
      if (Pad=='R')
      {
        digitalWrite(6,HIGH);
        delay(300);
        digitalWrite(6,LOW);
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
