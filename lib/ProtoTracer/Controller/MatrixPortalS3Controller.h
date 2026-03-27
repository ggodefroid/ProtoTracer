/**
 * @file MatrixPortalS3Controller.h
 * @brief HUB75 controller for Adafruit Matrix Portal S3 with two daisy-chained 64x32 panels.
 *
 * Uses ESP32-HUB75-MatrixPanel-DMA to drive panels via DMA on the ESP32-S3.
 *
 * @date 26/03/2026
 */

#pragma once

#include <stdint.h>
#include "Controller.h"
#include "MatrixPortalS3HUB75.h"
#include "../Camera/CameraManager/CameraManager.h"
#include "../Camera/Pixels/PixelGroup.h"

class MatrixPortalS3Controller : public Controller {
private:
    MatrixPanel_I2S_DMA* dma_display = nullptr;

public:
    MatrixPortalS3Controller(CameraManager* cameras, uint8_t maxBrightness, uint8_t maxAccentBrightness);

    void Initialize() override;
    void Display() override;
    void SetBrightness(uint8_t maxBrightness) override;
    void SetAccentBrightness(uint8_t maxAccentBrightness) override;
};
