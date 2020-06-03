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

void DotDisplay::drawText(const char *text) {
    this->display.clearBuffer();
    this->display.setDrawColor(1);
    this->display.setFont(u8g2_font_5x8_mr);
    this->display.setDrawColor(1);
    this->display.drawStr(0, 7, text);
    this->display.sendBuffer();
}

void DotDisplay::loop() {
    static int last_change = millis();
    if (millis() - last_change > 1000) {
        last_change = millis();
        this->display.setDrawColor(2);
        this->display.drawPixel(31, 0);
        this->display.sendBuffer();
    }
}