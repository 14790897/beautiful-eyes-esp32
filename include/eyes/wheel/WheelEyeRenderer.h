#ifndef WHEEL_EYE_RENDERER_H
#define WHEEL_EYE_RENDERER_H

#include <LovyanGFX.hpp>
#include "eyes/wheel/WheelEye.h"
#include "Config.h"

// 显轮眼渲染器类 (Sharingan)
class WheelEyeRenderer {
private:
    LGFX_Sprite* sprite;

    // 渲染细节方法
    void drawRedIris(const WheelEye& eye);
    void drawTomoes(const WheelEye& eye);
    void drawPupil(const WheelEye& eye);
    void drawWheelPattern(const WheelEye& eye);
    void drawGlowEffect(const WheelEye& eye);
    void drawEyelids(const WheelEye& eye);
    void drawHighlights(const WheelEye& eye);

public:
    WheelEyeRenderer();
    ~WheelEyeRenderer();

    void begin(LGFX_Sprite* sharedSprite);
    void render(const WheelEye& eye);
};

#endif // WHEEL_EYE_RENDERER_H
