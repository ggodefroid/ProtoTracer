/**
 * @file MatrixPortalS3HUB75.h
 * @brief Configuration for ESP32-HUB75-MatrixPanel-DMA on the Adafruit Matrix Portal S3.
 *
 * Pin mapping derived from the official Adafruit CircuitPython board definition.
 * Drives two 64x32 HUB75 panels daisy-chained (total logical 128x32).
 *
 * @date 26/03/2026
 */

#pragma once

#ifndef MATRIXPORTALS3HUB75_H
#define MATRIXPORTALS3HUB75_H

#include <ESP32-HUB75-MatrixPanel-I2S-DMA.h>

#define PANEL_RES_X 64
#define PANEL_RES_Y 32
#define PANEL_CHAIN  2

#define MP_S3_R1  42
#define MP_S3_G1  41
#define MP_S3_B1  40
#define MP_S3_R2  38
#define MP_S3_G2  39
#define MP_S3_B2  37
#define MP_S3_A   45
#define MP_S3_B   36
#define MP_S3_C   48
#define MP_S3_D   35
#define MP_S3_E   21
#define MP_S3_CLK  2
#define MP_S3_LAT 47
#define MP_S3_OE  14

#endif
