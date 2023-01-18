#include "sdkconfig.h"
#include <Arduino.h>
#include "driver/rmt.h"
#include <IRremoteESP8266.h>
#include <IRsend.h>

IRsend irsend(18);

void sendCMD(uint16_t cmd)
{
    #define PULSE_0   390
    #define PULSE_1   1170

    uint16_t rawData[28];

    for (int i = 0; i < 14; i++)
    {
        if (cmd & 0x0001)
        {
            rawData[i*2] = PULSE_1;
            rawData[i*2 + 1] = PULSE_0;
        }
        else
        {
            rawData[i*2] = PULSE_0;
            rawData[i*2 + 1] = PULSE_1;
        }
        cmd >>= 1;
    }
    irsend.sendRaw(rawData, 28, 38);  // Send a raw data capture at 38kHz.
}

void setup() 
{
    Serial.begin(115200);

    delay(50);
    Serial.printf("Hello!\n");

    irsend.begin();
}

void loop() 
{
    sendCMD(0x0820);
    delay(50);
}
