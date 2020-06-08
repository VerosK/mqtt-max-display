#include "dot-display.hpp"

void DotDisplay::drawSmallText(const char *text)
{
    this->display.clearBuffer();
    this->display.setDrawColor(1);
    this->display.setFont(u8g2_font_4x6_mr);    
    this->display.setDrawColor(1);
    this->display.drawStr(0, 7, text);
    this->display.sendBuffer();
}

void DotDisplay::drawText(const char *text)
{
    this->display.clearBuffer();
    this->display.setDrawColor(1);
    this->display.setFont(u8g2_font_5x8_mr);
    this->display.setDrawColor(1);
    this->display.drawStr(0, 7, text);
    this->display.sendBuffer();
}

void DotDisplay::loop()
{
    static unsigned int next_change = 0;
    static int color = 0;
    if (millis() > next_change)
    {
        this->display.setDrawColor(color);
        this->display.drawPixel(31, 0);
        this->display.sendBuffer();
        if (color)
        {
            next_change = millis() + 100;
        }
        else
        {
            next_change = millis() + 9900;
        }
        color = (color + 1) % 2;
    }
}

void DotDisplay::uploadProgress()
{
    static int phase = 0;
    phase = (phase + 1) % 32;

    this->display.setDrawColor(2); // XOR
    this->display.drawPixel(phase, 0);
    this->display.sendBuffer();
}