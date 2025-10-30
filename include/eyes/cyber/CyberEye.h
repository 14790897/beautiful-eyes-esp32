#ifndef CYBER_EYE_H
#define CYBER_EYE_H

#include <Arduino.h>
#include "Config.h"

// 赛博朋克机械眼睛数据类
class CyberEye {
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

    // 扫描线效果
    int scanLineY;              // 扫描线当前Y位置
    int scanDirection;          // 扫描方向 (1=向下, -1=向上)

    // HUD 状态
    uint32_t lastHUDUpdate;
    int hudValue;               // HUD 显示的数值
    float glowPhase;            // 发光相位

    // 数据流动画
    uint32_t lastDataUpdate;
    uint8_t dataStream[10];     // 数据流字节

public:
    CyberEye();

    // 更新方法
    void updateMovement();
    void updateBlink();
    void updateScanLine();
    void updateHUD();
    void updateGlow();
    void updateDataStream();
    void randomMove();

    // 获取器
    float getEyeX() const { return eyeX; }
    float getEyeY() const { return eyeY; }
    float getPupilX() const { return pupilX; }
    float getPupilY() const { return pupilY; }
    float getIrisSize() const { return irisSize; }
    float getPupilSize() const { return pupilSize; }
    float getBlinkProgress() const { return blinkProgress; }
    int getScanLineY() const { return scanLineY; }
    int getHUDValue() const { return hudValue; }
    float getGlowPhase() const { return glowPhase; }
    const uint8_t* getDataStream() const { return dataStream; }
};

#endif // CYBER_EYE_H
