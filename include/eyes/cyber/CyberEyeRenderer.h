#ifndef CYBER_EYE_RENDERER_H
#define CYBER_EYE_RENDERER_H

#include <LovyanGFX.hpp>
#include "eyes/cyber/CyberEye.h"
#include "Config.h"

// 赛博朋克机械眼睛渲染器类
class CyberEyeRenderer {
private:
    LGFX_Sprite* sprite;

    // 渲染细节方法
    void drawGrid();
    void drawMechanicalIris(const CyberEye& eye);
    void drawTechRings(const CyberEye& eye);
    void drawPupilCamera(const CyberEye& eye);
    void drawScanLine(const CyberEye& eye);
    void drawHUD(const CyberEye& eye);
    void drawCrosshair(const CyberEye& eye);
    void drawDataStream(const CyberEye& eye);
    void drawGlowEffect(const CyberEye& eye);
    void drawCircuitPattern(const CyberEye& eye);

public:
    CyberEyeRenderer();
    ~CyberEyeRenderer();

    void begin(LGFX_Sprite* sharedSprite);
    void render(const CyberEye& eye);
};

#endif // CYBER_EYE_RENDERER_H
