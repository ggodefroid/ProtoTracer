/**
 * @file MatrixPortalS3Cameras.h
 * @brief Dual-camera layout for Adafruit Matrix Portal S3 with two 64x32 HUB75 panels.
 *
 * Each camera maps to one 64x32 panel (one per eye). The two cameras share the same
 * rectangular pixel layout (64 cols x 32 rows = 2048 pixels at 3px spacing).
 *
 * @date 26/03/2026
 */

#pragma once

#include "../CameraManager.h"
#include "../../Camera.h"
#include "../../Pixels/PixelGroup.h"
#include "../../Pixels/PixelGroups/P3HUB75.h"
#include "../../../Utils/Math/Transform.h"

class MatrixPortalS3CameraManager : public CameraManager {
private:
    CameraLayout cameraLayout = CameraLayout(CameraLayout::ZForward, CameraLayout::YUp);

    Transform camTransformLeft  = Transform(Vector3D(), Vector3D(0, 0.0f, -500.0f), Vector3D(1, 1, 1));
    Transform camTransformRight = Transform(Vector3D(), Vector3D(0, 0.0f, -500.0f), Vector3D(1, 1, 1));

    PixelGroup<2048> camPixelsLeft  = PixelGroup<2048>(Vector2D(192.0f, 96.0f), Vector2D(0.0f, 0.0f), 64);
    PixelGroup<2048> camPixelsRight = PixelGroup<2048>(Vector2D(192.0f, 96.0f), Vector2D(0.0f, 0.0f), 64);

    Camera<2048> camLeft  = Camera<2048>(&camTransformLeft,  &cameraLayout, &camPixelsLeft);
    Camera<2048> camRight = Camera<2048>(&camTransformRight, &cameraLayout, &camPixelsRight);

public:
    MatrixPortalS3CameraManager() : CameraManager(new CameraBase*[2]{ &camLeft, &camRight }, 2) {}
};
