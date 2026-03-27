/**
 * @file Debug.h
 * @brief Utility class for debugging and monitoring system memory.
 *
 * @date 22/12/2024
 * @version 1.0
 * @author Coela Can't
 */

#pragma once

#include <Arduino.h>

#ifdef ARDUINO_ARCH_ESP32

class Debug {
public:
    static float FreeMem() {
        return float(ESP.getFreeHeap()) / 1000.0f;
    }
};

#else

extern unsigned long _heap_start;
extern unsigned long _heap_end;
extern char *__brkval;

class Debug {
public:
    static float FreeMem() {
        return float((char *)&_heap_end - __brkval) / 1000.0f;
    }
};

#endif
