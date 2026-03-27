/**
 * @file ProtogenMatrixPortalS3Project.h
 * @brief Protogen face project for Adafruit Matrix Portal S3 with two 64x32 HUB75 panels.
 *
 * Dual-panel layout: each panel displays one eye (mirrored). Uses the Matrix Portal S3
 * buttons (UP=GPIO6, DOWN=GPIO7) for menu control and GPIO12 (A0) for analog microphone.
 *
 * @date 26/03/2026
 */

#pragma once

#include "../Templates/ProtogenProjectTemplate.h"
#include "../../Assets/Models/FBX/NukudeFlat.h"
#include "../../Assets/Models/OBJ/Background.h"

#include "../../Camera/CameraManager/Implementations/MatrixPortalS3Cameras.h"
#include "../../Controller/MatrixPortalS3Controller.h"

class ProtogenMatrixPortalS3Project : public ProtogenProject {
private:
    MatrixPortalS3CameraManager cameras;
    MatrixPortalS3Controller controller = MatrixPortalS3Controller(&cameras, 50, 0);
    NukudeFace pM;

    const __FlashStringHelper* faceArray[10] = {F("DEFAULT"), F("ANGRY"), F("DOUBT"), F("FROWN"), F("LOOKUP"), F("SAD"), F("AUDIO1"), F("AUDIO2"), F("AUDIO3")};

    void LinkControlParameters() override {
        AddParameter(NukudeFace::Anger, pM.GetMorphWeightReference(NukudeFace::Anger), 15);
        AddParameter(NukudeFace::Sadness, pM.GetMorphWeightReference(NukudeFace::Sadness), 15, IEasyEaseAnimator::InterpolationMethod::Cosine);
        AddParameter(NukudeFace::Surprised, pM.GetMorphWeightReference(NukudeFace::Surprised), 15);
        AddParameter(NukudeFace::Doubt, pM.GetMorphWeightReference(NukudeFace::Doubt), 15);
        AddParameter(NukudeFace::Frown, pM.GetMorphWeightReference(NukudeFace::Frown), 15);
        AddParameter(NukudeFace::LookUp, pM.GetMorphWeightReference(NukudeFace::LookUp), 15);
        AddParameter(NukudeFace::LookDown, pM.GetMorphWeightReference(NukudeFace::LookDown), 15);

        AddParameter(NukudeFace::HideBlush, pM.GetMorphWeightReference(NukudeFace::HideBlush), 15, IEasyEaseAnimator::InterpolationMethod::Cosine, true);

        AddViseme(Viseme::MouthShape::EE, pM.GetMorphWeightReference(NukudeFace::vrc_v_ee));
        AddViseme(Viseme::MouthShape::AH, pM.GetMorphWeightReference(NukudeFace::vrc_v_aa));
        AddViseme(Viseme::MouthShape::UH, pM.GetMorphWeightReference(NukudeFace::vrc_v_dd));
        AddViseme(Viseme::MouthShape::AR, pM.GetMorphWeightReference(NukudeFace::vrc_v_rr));
        AddViseme(Viseme::MouthShape::ER, pM.GetMorphWeightReference(NukudeFace::vrc_v_ch));
        AddViseme(Viseme::MouthShape::OO, pM.GetMorphWeightReference(NukudeFace::vrc_v_oh));
        AddViseme(Viseme::MouthShape::SS, pM.GetMorphWeightReference(NukudeFace::vrc_v_ss));

        AddBlinkParameter(pM.GetMorphWeightReference(NukudeFace::Blink));
    }

    void Default() {}

    void Angry() {
        AddParameterFrame(NukudeFace::Anger, 1.0f);
        AddMaterialFrame(Color::CRED);
    }

    void Sad() {
        AddParameterFrame(NukudeFace::Sadness, 1.0f);
        AddParameterFrame(NukudeFace::Frown, 1.0f);
        AddMaterialFrame(Color::CBLUE);
    }

    void Surprised() {
        AddParameterFrame(NukudeFace::Surprised, 1.0f);
        AddParameterFrame(NukudeFace::HideBlush, 0.0f);
        AddMaterialFrame(Color::CRAINBOW);
    }

    void Doubt() {
        AddParameterFrame(NukudeFace::Doubt, 1.0f);
    }

    void Frown() {
        AddParameterFrame(NukudeFace::Frown, 1.0f);
    }

    void LookUp() {
        AddParameterFrame(NukudeFace::LookUp, 1.0f);
    }

    void LookDown() {
        AddParameterFrame(NukudeFace::LookDown, 1.0f);
    }

    void SpectrumAnalyzerCallback() override {
        AddMaterialFrame(Color::CHORIZONTALRAINBOW, 0.8f);
    }

    void AudioReactiveGradientCallback() override {
        AddMaterialFrame(Color::CHORIZONTALRAINBOW, 0.8f);
    }

    void OscilloscopeCallback() override {
        AddMaterialFrame(Color::CHORIZONTALRAINBOW, 0.8f);
    }

public:
    ProtogenMatrixPortalS3Project() : ProtogenProject(&cameras, &controller, 2, Vector2D(), Vector2D(192.0f, 94.0f), 12, 7, 9) {
        scene.AddObject(pM.GetObject());

        pM.GetObject()->SetMaterial(GetFaceMaterial());

        hud.SetFaceArray(faceArray);

        LinkControlParameters();

        SetWiggleSpeed(5.0f);
        SetMenuWiggleSpeed(0.0f, 0.0f, 0.0f);
        SetMenuOffset(Vector2D(17.5f, -3.0f));
        SetMenuSize(Vector2D(192, 56));
    }

    void Update(float ratio) override {
        pM.Reset();

        uint8_t mode = Menu::GetFaceState();

        controller.SetBrightness(Menu::GetBrightness());

        SelectFace(mode);

        UpdateFace(ratio);

        pM.Update();

        AlignObjectFace(pM.GetObject(), -7.5f);

        pM.GetObject()->GetTransform()->SetPosition(GetWiggleOffset());
        pM.GetObject()->UpdateTransform();
    }

    void SelectFace(uint8_t code) {
        if (IsBooped() && code != 6) {
            Surprised();
            return;
        }

        switch (code) {
            case 0: Default();  break;
            case 1: Angry();    break;
            case 2: Doubt();    break;
            case 3: Frown();    break;
            case 4: LookUp();   break;
            case 5: Sad();      break;
            case 6: AudioReactiveGradientFace();    break;
            case 7: OscilloscopeFace();             break;
            default: SpectrumAnalyzerFace();        break;
        }
    }
};
