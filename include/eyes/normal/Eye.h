#ifndef EYE_H
#define EYE_H

#include <Arduino.h>
#include "Config.h"

// 眼睛数据类
class Eye {
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

public:
    Eye();

    // 更新方法
    void updateMovement();
    void updateBlink();
    void randomMove();

    // 获取器
    float getEyeX() const { return eyeX; }
    float getEyeY() const { return eyeY; }
    float getPupilX() const { return pupilX; }
    float getPupilY() const { return pupilY; }
    float getIrisSize() const { return irisSize; }
    float getPupilSize() const { return pupilSize; }
    float getBlinkProgress() const { return blinkProgress; }
};

#endif // EYE_H
