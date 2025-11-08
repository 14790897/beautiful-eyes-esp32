#ifndef STAR_EYE_RENDERER_H
#define STAR_EYE_RENDERER_H

#include <LovyanGFX.hpp>
#include "eyes/star/StarEye.h"
#include "Config.h"

// 星瞳眼渲染器类 (Anime Star Pupil Eye)
class StarEyeRenderer {
private:
    LGFX_Sprite* sprite;

    // 渲染细节方法
    void drawGradientIris(const StarEye& eye);
    void drawStarPupil(const StarEye& eye);
    void drawSparkles(const StarEye& eye);
    void drawHighlights(const StarEye& eye);
    void drawGlowEffect(const StarEye& eye);
    void drawEyelids(const StarEye& eye);
    void drawEyelashes(const StarEye& eye);

public:
    StarEyeRenderer();
    ~StarEyeRenderer();

    void begin(LGFX_Sprite* sharedSprite);
    void render(const StarEye& eye);
};

#endif // STAR_EYE_RENDERER_H
