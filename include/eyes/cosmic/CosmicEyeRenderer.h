#ifndef COSMIC_EYE_RENDERER_H
#define COSMIC_EYE_RENDERER_H

#include <LovyanGFX.hpp>
#include "eyes/cosmic/CosmicEye.h"
#include "Config.h"

// 星空宇宙眼睛渲染器类
class CosmicEyeRenderer {
private:
    LGFX_Sprite* sprite;

    // 渲染细节方法
    void drawNebulaIris(const CosmicEye& eye);
    void drawGalaxyPupil(const CosmicEye& eye);
    void drawStars(const CosmicEye& eye);
    void drawMeteor(const CosmicEye& eye);
    void drawCosmicGlow(const CosmicEye& eye);
    void drawEyelids(const CosmicEye& eye);

public:
    CosmicEyeRenderer();
    ~CosmicEyeRenderer();

    void begin(LGFX_Sprite* sharedSprite);
    void render(const CosmicEye& eye);
};

#endif // COSMIC_EYE_RENDERER_H
