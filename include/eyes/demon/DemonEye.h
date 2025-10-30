#ifndef DEMON_EYE_H
#define DEMON_EYE_H

#include <Arduino.h>
#include "Config.h"

// 魅魔眼睛类 - 具有竖瞳和发光效果
class DemonEye {
private:
    // 位置和大小
    float eyeX, eyeY;           // 眼球中心位置
    float pupilX, pupilY;       // 瞳孔当前位置
    float targetPupilX, targetPupilY;  // 瞳孔目标位置
    float irisSize;             // 虹膜大小
    float pupilWidth;           // 竖瞳宽度
    float pupilHeight;          // 竖瞳高度

    // 眨眼状态
    float blinkProgress;        // 眨眼进度 0-1
    float targetBlinkProgress;
    uint32_t lastBlinkTime;

    // 运动状态
    uint32_t lastMoveTime;

    // 发光效果
    float glowPhase;            // 发光相位 0-2π
    float glowIntensity;        // 当前发光强度

public:
    DemonEye();

    // 更新方法
    void updateMovement();
    void updateBlink();
    void updateGlow();
    void randomMove();

    // 获取器
    float getEyeX() const { return eyeX; }
    float getEyeY() const { return eyeY; }
    float getPupilX() const { return pupilX; }
    float getPupilY() const { return pupilY; }
    float getIrisSize() const { return irisSize; }
    float getPupilWidth() const { return pupilWidth; }
    float getPupilHeight() const { return pupilHeight; }
    float getBlinkProgress() const { return blinkProgress; }
    float getGlowIntensity() const { return glowIntensity; }
};

#endif // DEMON_EYE_H
