#include "MatrixPortalS3Controller.h"

MatrixPortalS3Controller::MatrixPortalS3Controller(CameraManager* cameras, uint8_t maxBrightness, uint8_t maxAccentBrightness)
    : Controller(cameras, maxBrightness, maxAccentBrightness) {}

void MatrixPortalS3Controller::Initialize() {
    HUB75_I2S_CFG::i2s_pins _pins = {
        MP_S3_R1, MP_S3_G1, MP_S3_B1,
        MP_S3_R2, MP_S3_G2, MP_S3_B2,
        MP_S3_A,  MP_S3_B,  MP_S3_C,
        MP_S3_D,  MP_S3_E,
        MP_S3_LAT, MP_S3_OE, MP_S3_CLK
    };

    HUB75_I2S_CFG mxconfig(
        PANEL_RES_X,
        PANEL_RES_Y,
        PANEL_CHAIN,
        _pins
    );

    mxconfig.clkphase = false;

    dma_display = new MatrixPanel_I2S_DMA(mxconfig);

    if (!dma_display->begin()) {
        Serial.println("HUB75 DMA allocation failed");
    }

    dma_display->setBrightness8(128);
    dma_display->clearScreen();

    // Boot test pattern: confirms panel power/cabling/pinout quickly.
    for (uint16_t y = 0; y < PANEL_RES_Y; y++) {
        for (uint16_t x = 0; x < PANEL_RES_X * PANEL_CHAIN; x++) {
            if (x < (PANEL_RES_X * PANEL_CHAIN) / 3) {
                dma_display->drawPixelRGB888(x, y, 255, 0, 0);
            } else if (x < ((PANEL_RES_X * PANEL_CHAIN) * 2) / 3) {
                dma_display->drawPixelRGB888(x, y, 0, 255, 0);
            } else {
                dma_display->drawPixelRGB888(x, y, 0, 0, 255);
            }
        }
    }
    delay(1200);
    dma_display->clearScreen();
}

void MatrixPortalS3Controller::Display() {
    UpdateBrightness();

    dma_display->setBrightness8(brightness);

    uint8_t camCount = cameras->GetCameraCount();

    if (camCount >= 2) {
        IPixelGroup* camLeft  = cameras->GetCameras()[0]->GetPixelGroup();
        IPixelGroup* camRight = cameras->GetCameras()[1]->GetPixelGroup();

        for (uint16_t y = 0; y < PANEL_RES_Y; y++) {
            for (uint16_t x = 0; x < PANEL_RES_X; x++) {
                uint16_t pixelNum = y * PANEL_RES_X + x;

                RGBColor* cL = camLeft->GetColor(pixelNum);
                uint16_t mirroredX = PANEL_RES_X - 1 - x;
                dma_display->drawPixelRGB888(mirroredX, y, cL->R, cL->G, cL->B);

                RGBColor* cR = camRight->GetColor(pixelNum);
                dma_display->drawPixelRGB888(x + PANEL_RES_X, y, cR->R, cR->G, cR->B);
            }
        }
    } else if (camCount == 1) {
        IPixelGroup* camPixels = cameras->GetCameras()[0]->GetPixelGroup();

        for (uint16_t y = 0; y < PANEL_RES_Y; y++) {
            for (uint16_t x = 0; x < PANEL_RES_X; x++) {
                uint16_t pixelNum = y * PANEL_RES_X + x;

                RGBColor* c = camPixels->GetColor(pixelNum);
                dma_display->drawPixelRGB888(x, y, c->R, c->G, c->B);
                dma_display->drawPixelRGB888((PANEL_RES_X * 2 - 1) - x, y, c->R, c->G, c->B);
            }
        }
    }
}

void MatrixPortalS3Controller::SetBrightness(uint8_t maxBrightness) {
    this->maxBrightness = maxBrightness * 25 + 5;

    if (isOn) {
        this->brightness = maxBrightness * 25 + 5;
    }
}

void MatrixPortalS3Controller::SetAccentBrightness(uint8_t maxAccentBrightness) {
    this->maxAccentBrightness = maxAccentBrightness;

    if (isOn) {
        this->accentBrightness = maxAccentBrightness;
    }
}
