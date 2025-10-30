#ifndef BEAUTIFUL_EYE_H
#define BEAUTIFUL_EYE_H

#include <Arduino.h>
#include "Config.h"

// 美丽女生眼睛数据类
class BeautifulEye {
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

    // 闪亮效果
    float sparklePhase;         // 闪亮动画相位

public:
    BeautifulEye();

    // 更新方法
    void updateMovement();
    void updateBlink();
    void updateSparkle();
    void randomMove();

    // 获取器
    float getEyeX() const { return eyeX; }
    float getEyeY() const { return eyeY; }
    float getPupilX() const { return pupilX; }
    float getPupilY() const { return pupilY; }
    float getIrisSize() const { return irisSize; }
    float getPupilSize() const { return pupilSize; }
    float getBlinkProgress() const { return blinkProgress; }
    float getSparklePhase() const { return sparklePhase; }
};

#endif // BEAUTIFUL_EYE_H
