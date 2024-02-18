#include <Arduino.h>
#include "audio.h"
#include "motor.h"

const int user_sensor = 32;

void setup()
{ 
  // khoi dong serial
  Serial.begin(115200);
  // khai bao chan motor + do line
  Serial.println("Khai bao chan motor...");
  initMotor();
  // khai bao module mp3
  Serial.println("Khai bao module mp3");
  if (!initAudio()) {
    Serial.println("Khong the ket noi den module mp3");
    while (1);
  }
  Serial.println("Module mp3 truc tuyen!");
  // khai bao cam bien vat can
  pinMode(user_sensor, INPUT);
  digitalWrite(user_sensor, HIGH);
}

void loop()
{
  while (1) {
    if (!digitalRead(user_sensor)) {
      Serial.println("Bat dau tien trinh");
      break;
    }
  }
  analogWrite(mot1, 100);
  analogWrite(mot2, 0);
  analogWrite(mot3, 100);
  analogWrite(mot4, 0);

  while (1)
  {
    Left = !digitalRead(left);
    Right = !digitalRead(right);

    if ((Left == 0 && Right == 1) == 1)
      LEFT();
    else if ((Right == 0 && Left == 1) == 1)
      RIGHT();
  }
}