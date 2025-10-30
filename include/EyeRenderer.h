#ifndef EYE_RENDERER_H
#define EYE_RENDERER_H

#include <LovyanGFX.hpp>
#include "Eye.h"
#include "Config.h"

// 眼睛渲染器类
class EyeRenderer {
private:
    LGFX_Sprite* sprite;

    // 渲染细节方法
    void drawVeins(const Eye& eye);
    void drawIrisDetail(const Eye& eye);
    void drawReflections(const Eye& eye);
    void drawEyelashes(float upperY, float lowerY);

public:
    EyeRenderer();
    ~EyeRenderer();

    void begin(LGFX_Sprite* sharedSprite);
    void render(const Eye& eye);
};

#endif // EYE_RENDERER_H
