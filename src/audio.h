#include "DFRobotDFPlayerMini.h"
#include <Arduino.h>

// khai bao dfplayer
HardwareSerial mySoftwareSerial(1);
DFRobotDFPlayerMini myDFPlayer;
void printDetail(uint8_t type, int value);
// khai bao so luong am thanh con lai
const int list_length = 3;
int list_progress = 1;

bool initAudio()
{
    mySoftwareSerial.begin(9600, SERIAL_8N1, 27, 26); // speed, type, RX, TX
                                                      //  player
    Serial.println();
    Serial.println(F("DFRobot DFPlayer Mini Demo"));
    Serial.println(F("Initializing DFPlayer ... (May take 3~5 seconds)"));

    if (!myDFPlayer.begin(mySoftwareSerial))
    { // Use softwareSerial to communicate with mp3.

        Serial.println(myDFPlayer.readType(), HEX);
        Serial.println(F("Unable to begin:"));
        Serial.println(F("1.Please recheck the connection!"));
        Serial.println(F("2.Please insert the SD card!"));
        return false;
    }
    Serial.println(F("DFPlayer Mini online."));
    // Set serial communictaion time out 500ms
    myDFPlayer.setTimeOut(500);
    // set volume
    myDFPlayer.volume(30); // Set volume value (0~30).
    // set eq
    myDFPlayer.EQ(DFPLAYER_EQ_NORMAL);
    // set sdcard as device
    myDFPlayer.outputDevice(DFPLAYER_DEVICE_SD);
    return true;
}

void waitForPA()
{
    while (true)
    {
        while (myDFPlayer.available())
        {
            if (myDFPlayer.readType() == DFPlayerPlayFinished)
            {
                return;
            }
        }
    }
}

bool callback()
{
    if (list_progress > list_length)
        return false;
    myDFPlayer.playMp3Folder(list_progress);
    myDFPlayer.start();
    waitForPA();
    list_progress++;
    return true;
}
