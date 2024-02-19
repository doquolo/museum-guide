#include <Arduino.h>

// khai bao chan cau H
const int mot1 = 15;
const int mot2 = 2;
const int mot3 = 0;
const int mot4 = 4;

// khai bao chan do line
const int left = 34;
const int right = 35;

// bien luu gia tri do line
int Left = 0;
int Right = 0;

// ham khai bao chan
void initMotor()
{
    // khai bao chan cau H
    pinMode(mot1, OUTPUT);
    pinMode(mot2, OUTPUT);
    pinMode(mot3, OUTPUT);
    pinMode(mot4, OUTPUT);

    // khai bao chan do line
    pinMode(left, INPUT);
    pinMode(right, INPUT);

    // keo chan cam bien do line len cao
    digitalWrite(left, HIGH);
    digitalWrite(right, HIGH);
}

// ham ho tro do line
void STOP(void)
{
    analogWrite(mot1, 0);
    analogWrite(mot2, 0);
    analogWrite(mot3, 0);
    analogWrite(mot4, 0);

    if (callback())
    {
        analogWrite(mot1, 100);
        analogWrite(mot2, 0);
        analogWrite(mot3, 100);
        analogWrite(mot4, 0);
        delay(250);
        analogWrite(mot1, 0);
        analogWrite(mot2, 0);
        analogWrite(mot3, 0);
        analogWrite(mot4, 0);
    }
}

void LEFT(void)
{
    analogWrite(mot3, 0);
    analogWrite(mot4, 30);

    while (Left == 0)
    {
        Left = !digitalRead(left);
        Right = !digitalRead(right);
        if (Right == 0)
        {
            int lprev = Left;
            int rprev = Right;
            STOP();
            while (((lprev == Left) && (rprev == Right)) == 1)
            {
                Left = !digitalRead(left);
                Right = !digitalRead(right);
            }
        }
        analogWrite(mot1, 100);
        analogWrite(mot2, 0);
    }
    analogWrite(mot3, 100);
    analogWrite(mot4, 0);
}

void RIGHT(void)
{
    analogWrite(mot1, 0);
    analogWrite(mot2, 30);

    while (Right == 0)
    {
        Left = !digitalRead(left);
        Right = !digitalRead(right);
        if (Left == 0)
        {
            int lprev = Left;
            int rprev = Right;
            STOP();
            while (((lprev == Left) && (rprev == Right)) == 1)
            {
                Left = !digitalRead(left);
                Right = !digitalRead(right);
            }
        }
        analogWrite(mot3, 100);
        analogWrite(mot4, 0);
    }
    analogWrite(mot1, 100);
    analogWrite(mot2, 0);
}
