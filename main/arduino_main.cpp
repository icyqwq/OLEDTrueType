#include "sdkconfig.h"
#include <Arduino.h>
#include "SH1122.h"
#include "ISprite.h"
#include "binaryttf.h" // Simplified character set, only ASCII, kana and some symbols

#define USE_FLASH

SH1122 sh1122;
ISprite sprite(&sh1122);

void OLEDTestTask(void *args)
{
    sprite.fillSprite(0);

#ifdef USE_SPIFFS
    sprite.loadFont("/GenSenRounded-R.ttf", SPIFFS);  // Load font files from SPIFFS
#endif
#ifdef USE_SD
    sprite.loadFont("/GenSenRounded-R.ttf", SD);  // Load font files from SD Card
#endif
#ifdef USE_FLASH
    sprite.loadFont(binaryttf, sizeof(binaryttf));  // Load font files from binary data
#endif

    sprite.createRender(26, 32);
    sprite.setTextSize(26);
    sprite.setTextColor(15, 0);
    sprite.setTextDatum(TL_DATUM);
    sprite.drawString("Hello world!", 0, 0);
    sprite.drawString("こんにちは", 0, 32);
    sprite.pushSprite();

    vTaskDelete(NULL);
}

// Arduino setup function. Runs in CPU 1
void setup() {
    Serial.begin(115200);

    sh1122.init(0);
    // note: Only the drawing functions in the sprite class can be used
    sprite.setColorDepth(4);
    sprite.createSprite(256, 64);
    sprite.fillSprite(0);
    
    xTaskCreatePinnedToCore(&OLEDTestTask, "OLEDTestTask", 64 * 1024, NULL, 10, NULL, 0);
}

// Arduino loop function. Runs in CPU 1
void loop() 
{
    delay(150);
}
