#pragma once

#include <Arduino.h>
#include <Preferences.h>

template <uint8_t menuCount>
class MenuHandler {
private:
    static Preferences preferences;
    static long previousMillisHold;
    static uint16_t holdingTime;
    static uint8_t currentMenu;
    static uint8_t currentValue[menuCount];
    static uint8_t maxValue[menuCount];
    static uint8_t pin;
    static bool holdingState;
    static bool previousState;
    static bool started;

    static uint8_t ReadPref(uint16_t index) {
        char key[8];
        snprintf(key, sizeof(key), "m%d", index);
        return preferences.getUChar(key, 255);
    }

    static void WritePref(uint16_t index, uint8_t value) {
        char key[8];
        snprintf(key, sizeof(key), "m%d", index);
        preferences.putUChar(key, value);
    }

public:
    static void Begin();
    static bool Initialize(uint8_t pin, uint16_t holdingTime);
    static void SetDefaultValue(uint16_t menu, uint8_t value);
    static void SetInitialized();
    static void SetMenuMax(uint8_t menu, uint8_t maxValue);
    static uint8_t GetMenuValue(uint8_t menu);
    static uint8_t GetCurrentMenu();
};

#include "SingleButtonMenuHandler_ESP32.tpp"
