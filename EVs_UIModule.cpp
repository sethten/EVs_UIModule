
// EVs_UIModule.cpp

/*
  Copyright (C) 2015 OpenElectrons.com

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/


#include "EVs_UIModule.h"


EVs_UIModule::EVs_UIModule(uint8_t CS, uint8_t RS, uint8_t RST):Adafruit_ILI9340(CS, RS, RST)
{
}

void EVs_UIModule::setRotation(uint8_t r)
{
    Adafruit_ILI9340::setRotation(r);
}

void EVs_UIModule::clearScreen()
{
    Adafruit_ILI9340::fillScreen(EVs_UIM_BLACK);
}

void EVs_UIModule::begin()
{
    Adafruit_ILI9340::begin();
    #if defined(ESP8266)
    setRotation(3);
    #else
    setRotation(1);
    #endif
    setTextSize(2);
    setTextColor(EVs_UIM_WHITE);
    #if !defined(ESP8266)
    pinMode(EVs_BTN_LEFT, INPUT);
    pinMode(EVs_BTN_RIGHT, INPUT);
    pinMode(EVs_BTN_UP, INPUT);
    pinMode(EVs_BTN_DOWN, INPUT);
    pinMode(EVs_BTN_CLICK, INPUT);
    #endif
}

bool EVs_UIModule::getButtonState(uint8_t btn)
{
    #if defined(ESP8266)
    #warning from EVs_UIModule: bool getButtonState(uint8_t btn) is not supported
    return false;
    #else
    return (!digitalRead(btn));
    #endif
}

void EVs_UIModule::waitForButtonPress(uint8_t btn)
{
    #if defined(ESP8266)
    #warning from EVs_UIModule: void waitForButtonPress(uint8_t btn) is not supported
    return;
    #else
    while (digitalRead(btn))
        ;
    #endif
}

void EVs_UIModule::clearLine(uint8_t lineNo)
{
    uint16_t y = (lineNo - 1) * 16;
    Adafruit_ILI9340::fillRect(0,y,320,16,EVs_UIM_BLACK);
}

void EVs_UIModule::writeLine(uint16_t x, uint8_t lineNo, const char *outText, bool clearLine, uint16_t color)
{
    if(clearLine==true){
        EVs_UIModule::clearLine(lineNo);
    }
    setTextSize(2);
    setTextColor(color);
    Adafruit_GFX::setCursor(x,((lineNo - 1) * 16));
    println(outText);
    
}
