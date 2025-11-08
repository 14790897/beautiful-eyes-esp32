#ifndef STAR_EYE_H
#define STAR_EYE_H

#include <Arduino.h>
#include "Config.h"

// 星瞳眼数据类 (Anime Star Pupil Eye)
class StarEye {
public:
    // 闪烁点结构体
    struct Sparkle {
        float x, y;             // 闪烁点位置
        float brightness;       // 亮度 0-1
        float fadeSpeed;        // 闪烁速度
        float phase;            // 相位
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

    // 星瞳眼特有效果
    float starRotation;         // 星形瞳孔旋转角度
    Sparkle sparkles[8];        // 闪烁点数组
    float glowPhase;            // 发光相位
    float heartBeatPhase;       // 心跳效果相位

public:
    StarEye();

    // 更新方法
    void updateMovement();
    void updateBlink();
    void updateStarRotation();
    void updateSparkles();
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
    float getStarRotation() const { return starRotation; }
    const Sparkle* getSparkles() const { return sparkles; }
    float getGlowPhase() const { return glowPhase; }
    float getHeartBeatPhase() const { return heartBeatPhase; }
};

#endif // STAR_EYE_H
