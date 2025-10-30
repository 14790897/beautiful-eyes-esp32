#ifndef BEAUTIFUL_EYE_RENDERER_H
#define BEAUTIFUL_EYE_RENDERER_H

#include <LovyanGFX.hpp>
#include "BeautifulEye.h"
#include "Config.h"

// 美丽女生眼睛渲染器类
class BeautifulEyeRenderer {
private:
    LGFX_Sprite* sprite;

    // 渲染细节方法
    void drawEyeShape(const BeautifulEye& eye, float visibleHeight);
    void drawEyeShadow(const BeautifulEye& eye, float upperY);
    void drawIrisGradient(const BeautifulEye& eye);
    void drawIrisDetail(const BeautifulEye& eye);
    void drawPupil(const BeautifulEye& eye);
    void drawReflections(const BeautifulEye& eye);
    void drawSparkles(const BeautifulEye& eye);
    void drawEyeliner(float upperY, float lowerY);
    void drawEyelashes(float upperY, float lowerY);

public:
    BeautifulEyeRenderer();
    ~BeautifulEyeRenderer();

    void begin(LGFX_Sprite* sharedSprite);
    void render(const BeautifulEye& eye);
};

#endif // BEAUTIFUL_EYE_RENDERER_H
