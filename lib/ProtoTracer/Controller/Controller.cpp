#include "Controller.h"

Controller::Controller(CameraManager* cameras, uint8_t maxBrightness, uint8_t maxAccentBrightness) {
    this->cameras = cameras;
    this->maxBrightness = maxBrightness;
    this->maxAccentBrightness = maxAccentBrightness;
}

void Controller::UpdateBrightness() {
    if (!startTime) {
        startTime = true;
        previousTime = micros();
    }

    if (!isOn && (uint32_t)micros() < softStart + previousTime) {
        uint32_t now = (uint32_t)micros();
        uint32_t end = softStart + previousTime;
        brightness = Mathematics::Map(now, previousTime, end, uint32_t(0), uint32_t(maxBrightness));
        accentBrightness = Mathematics::Map(now, previousTime, end, uint32_t(0), uint32_t(maxAccentBrightness));
    } else if (!isOn) {
        brightness = maxBrightness;
        accentBrightness = maxAccentBrightness;
        isOn = true;
    }
}

uint8_t Controller::GetBrightness() {
    return brightness;
}

uint8_t Controller::GetAccentBrightness() {
    return accentBrightness;
}

