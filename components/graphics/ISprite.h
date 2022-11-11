#pragma once

#include "Sprite.h"
#include "IeSPI.h"

// Legacy class for overriding driver code
class ISprite : public TFT_eSprite
{
private:
    IeSPI *_itft;
public:
    ISprite(IeSPI *tft);
    ~ISprite();

    void pushSprite(int32_t x, int32_t y);
    void pushSprite();
};

inline ISprite::ISprite(IeSPI *tft):TFT_eSprite(tft)
{
    _itft = tft;
}

inline ISprite::~ISprite()
{
}

inline void ISprite::pushSprite()
{
    _itft->updateDisplay(_dwidth * _dheight, _img8);
}

inline void ISprite::pushSprite(int32_t x, int32_t y)
{
    _itft->updateDisplay(x, y, _dwidth, _dheight, _img8);
}
