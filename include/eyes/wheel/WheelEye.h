#ifndef WHEEL_EYE_H
#define WHEEL_EYE_H

#include <Arduino.h>
#include "Config.h"

// 显轮眼数据类 (Sharingan)
class WheelEye {
public:
    // 勾玉结构体
    struct Tomoe {
        float x, y;             // 勾玉位置
        float angle;            // 勾玉自身旋转角度
    };

private:
    // 位置和大小
    float eyeX, eyeY;           // 眼球中心位置
    float pupilX, pupilY;       // 瞳孔当前位置
    float targetPupilX, targetPupilY;  // 瞳孔目标位置
    float irisSize;             // 虹膜大小
    float pupilSize;            // 瞳孔大小

    // 眨眼状态
    float blinkProgress;        // 眨眼进度 0-1
    float targetBlinkProgress;
    uint32_t lastBlinkTime;
    uint32_t blinkDuration;

    // 运动状态
    uint32_t lastMoveTime;

    // 显轮眼特有效果
    float wheelRotation;        // 勾玉轮盘旋转角度
    Tomoe tomoes[3];            // 三个勾玉
    float glowIntensity;        // 发光强度 0-1
    float glowPhase;            // 发光相位

public:
    WheelEye();

    // 更新方法
    void updateMovement();
    void updateBlink();
    void updateWheelRotation();
    void updateGlow();
    void randomMove();

    // 获取器
    float getEyeX() const { return eyeX; }
    float getEyeY() const { return eyeY; }
    float getPupilX() const { return pupilX; }
    float getPupilY() const { return pupilY; }
    float getIrisSize() const { return irisSize; }
    float getPupilSize() const { return pupilSize; }
    float getBlinkProgress() const { return blinkProgress; }
    float getWheelRotation() const { return wheelRotation; }
    const Tomoe* getTomoes() const { return tomoes; }
    float getGlowIntensity() const { return glowIntensity; }
};

#endif // WHEEL_EYE_H
