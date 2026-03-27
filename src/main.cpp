/**
 * @file main.cpp
 * @brief Entry point for various projects, managing initialization and main loop operations.
 *
 * This file determines which project to run based on the defined preprocessor directive
 * and provides functionality for initializing and executing the selected project.
 *
 * Supported projects:
 * - PROJECT_PROTOGEN_HUB75
 * - PROJECT_PROTOGEN_WS35
 * - PROJECT_PROTOGEN_BETA
 * - PROJECT_PROTOGEN_MATRIXPORTAL_S3
 * - PROJECT_VERIFY_ENGINE
 * - PROJECT_VERIFY_HARDWARE
 *
 * @date 22/12/2024
 * @version 1.0
 * @author Coela Can't
 */

#include "Examples/UserConfiguration.h"

#if defined(PROJECT_PROTOGEN_HUB75)
    #include "Examples/Protogen/ProtogenHUB75Project.h"
    ProtogenHUB75Project project; ///< Instance of the Protogen HUB75 project.

#elif defined(PROJECT_PROTOGEN_WS35)
    #include "Examples/Protogen/ProtogenWS35Project.h"
    ProtogenWS35Project project; ///< Instance of the Protogen WS35 project.

#elif defined(PROJECT_PROTOGEN_BETA)
    #include "Examples/Protogen/BetaProject.h"
    BetaProject project; ///< Instance of the Beta project.

#elif defined(PROJECT_PROTOGEN_MATRIXPORTAL_S3)
    #include "Examples/Protogen/ProtogenMatrixPortalS3Project.h"
    ProtogenMatrixPortalS3Project project;

#elif defined(PROJECT_VERIFY_ENGINE)
    #include "Examples/VerifyEngine.h"
    VerifyEngine project; ///< Instance of the Verify Engine project.

#elif defined(PROJECT_VERIFY_HARDWARE)
    #include "Examples/Protogen/ProtogenHardwareTest.h"
#else
    #error "No project defined! Please define one of PROJECT_PROTOGEN_HUB75, PROJECT_PROTOGEN_WS35, or PROJECT_VERIFY_ENGINE."
#endif

/**
 * @brief Arduino setup function, initializes the selected project.
 *
 * If PROJECT_VERIFY_HARDWARE is defined, runs continuous hardware testing.
 */
void setup() {
    Serial.begin(115200);
#ifdef ARDUINO_ARCH_ESP32
    delay(2000);
#endif
    Serial.println("\n=== ProtoTracer Boot ===");
    Serial.printf("Free heap: %u\n", ESP.getFreeHeap());

    #ifndef PROJECT_VERIFY_HARDWARE
    Serial.println("[SETUP] Calling project.Initialize()...");
    project.Initialize();
    Serial.println("[SETUP] Initialize() done");
    Serial.printf("Free heap after init: %u\n", ESP.getFreeHeap());
    delay(100);
    #else
    while (true) {
        HardwareTest::ScanDevices(); ///< Scans for connected hardware devices.
        HardwareTest::TestNeoTrellis(); ///< Tests the NeoTrellis input device.
        HardwareTest::TestBoopSensor(); ///< Tests the proximity (boop) sensor.
        HardwareTest::TestHUD(); ///< Tests the HUD (Head-Up Display) functionality.
    }
    #endif
}

/**
 * @brief Arduino main loop function, animates, renders, and updates the selected project.
 *
 * If PROJECT_VERIFY_HARDWARE is defined, this function is disabled.
 */
void loop() {
    #ifndef PROJECT_VERIFY_HARDWARE
    float ratio = (float)(millis() % 5000) / 5000.0f;

    project.Animate(ratio);
    project.Render();
    project.Display();
    project.PrintStats();
    #endif
}
