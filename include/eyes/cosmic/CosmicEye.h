#ifndef COSMIC_EYE_H
#define COSMIC_EYE_H

#include <Arduino.h>
#include "Config.h"

// 星空宇宙眼睛数据类
class CosmicEye {
public:
    // 公开结构体定义，让渲染器可以访问
    struct Star {
        int x, y;               // 星星位置
        float brightness;       // 亮度 0-1
        float fadeSpeed;        // 闪烁速度
    };

    struct Meteor {
        float x, y;             // 流星位置
        float dx, dy;           // 流星速度
        bool active;            // 是否活动
        float life;             // 生命值 0-1
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

    // 星云旋转
    float nebulaRotation;       // 星云旋转角度
    float nebulaSpeed;          // 星云旋转速度

    // 星系旋转
    float galaxyRotation;       // 星系旋转角度

    // 星星闪烁
    Star stars[8];              // 8颗星星

    // 流星效果
    Meteor meteor;
    uint32_t lastMeteorTime;

    // 星云脉动
    float nebulaPulse;          // 星云脉动相位

public:
    CosmicEye();

    // 更新方法
    void updateMovement();
    void updateBlink();
    void updateNebula();
    void updateGalaxy();
    void updateStars();
    void updateMeteor();
    void updatePulse();
    void randomMove();

    // 获取器
    float getEyeX() const { return eyeX; }
    float getEyeY() const { return eyeY; }
    float getPupilX() const { return pupilX; }
    float getPupilY() const { return pupilY; }
    float getIrisSize() const { return irisSize; }
    float getPupilSize() const { return pupilSize; }
    float getBlinkProgress() const { return blinkProgress; }
    float getNebulaRotation() const { return nebulaRotation; }
    float getGalaxyRotation() const { return galaxyRotation; }
    const Star* getStars() const { return stars; }
    const Meteor& getMeteor() const { return meteor; }
    float getNebulaPulse() const { return nebulaPulse; }
};

#endif // COSMIC_EYE_H
