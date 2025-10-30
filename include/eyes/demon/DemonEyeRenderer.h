#ifndef DEMON_EYE_RENDERER_H
#define DEMON_EYE_RENDERER_H

#include <LovyanGFX.hpp>
#include "eyes/demon/DemonEye.h"
#include "Config.h"

// 魅魔眼睛渲染器类
class DemonEyeRenderer {
private:
    LGFX_Sprite* sprite;

    // 渲染细节方法
    void drawGlowEffect(const DemonEye& eye);
    void drawIrisDetail(const DemonEye& eye);
    void drawVerticalPupil(const DemonEye& eye);
    void drawHeartHighlight(const DemonEye& eye);
    void drawSexyEyelashes(float upperY, float lowerY);

public:
    DemonEyeRenderer();
    ~DemonEyeRenderer();

    void begin(LGFX_Sprite* sharedSprite);
    void render(const DemonEye& eye);
};

#endif // DEMON_EYE_RENDERER_H
