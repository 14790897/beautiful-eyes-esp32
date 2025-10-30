#include "eyes/cyber/CyberEye.h"

CyberEye::CyberEye() {
    // 初始化位置
    eyeX = CyberEyeConfig::EYE_CENTER_X;
    eyeY = CyberEyeConfig::EYE_CENTER_Y;
    pupilX = eyeX;
    pupilY = eyeY;
    targetPupilX = eyeX;
    targetPupilY = eyeY;

    // 初始化大小
    irisSize = CyberEyeConfig::IRIS_SIZE;
    pupilSize = CyberEyeConfig::PUPIL_SIZE;

    // 初始化眨眼状态
    blinkProgress = 0.0f;
    targetBlinkProgress = 0.0f;
    lastBlinkTime = millis();
    blinkDuration = random(CyberEyeConfig::BLINK_MIN_INTERVAL,
                          CyberEyeConfig::BLINK_MAX_INTERVAL);

    // 初始化运动状态
    lastMoveTime = millis();

    // 初始化扫描线
    scanLineY = 0;
    scanDirection = 1;

    // 初始化 HUD
    lastHUDUpdate = millis();
    hudValue = random(0, 100);
    glowPhase = 0.0f;

    // 初始化数据流
    lastDataUpdate = millis();
    for (int i = 0; i < 10; i++) {
        dataStream[i] = random(0, 256);
    }
}

void CyberEye::updateMovement() {
    // 平滑移动瞳孔到目标位置
    pupilX += (targetPupilX - pupilX) * CyberEyeConfig::PUPIL_SMOOTH;
    pupilY += (targetPupilY - pupilY) * CyberEyeConfig::PUPIL_SMOOTH;
}

void CyberEye::updateBlink() {
    uint32_t currentTime = millis();

    // 检查是否该眨眼了
    if (currentTime - lastBlinkTime > blinkDuration && targetBlinkProgress == 0.0f) {
        targetBlinkProgress = 1.0f;
    }

    // 平滑过渡到目标眨眼状态 - 机械快速眨眼
    if (blinkProgress < targetBlinkProgress) {
        blinkProgress += CyberEyeConfig::BLINK_SPEED;
        if (blinkProgress >= targetBlinkProgress) {
            blinkProgress = targetBlinkProgress;
            if (targetBlinkProgress >= 1.0f) {
                targetBlinkProgress = 0.0f;
                lastBlinkTime = currentTime;
                blinkDuration = random(CyberEyeConfig::BLINK_MIN_INTERVAL,
                                      CyberEyeConfig::BLINK_MAX_INTERVAL);
            }
        }
    } else if (blinkProgress > targetBlinkProgress) {
        blinkProgress -= CyberEyeConfig::BLINK_SPEED;
        if (blinkProgress <= targetBlinkProgress) {
            blinkProgress = targetBlinkProgress;
        }
    }
}

void CyberEye::updateScanLine() {
    // 更新扫描线位置
    scanLineY += scanDirection * CyberEyeConfig::SCAN_LINE_SPEED;

    // 反转方向
    if (scanLineY >= HardwareConfig::SCREEN_HEIGHT) {
        scanLineY = HardwareConfig::SCREEN_HEIGHT;
        scanDirection = -1;
    } else if (scanLineY <= 0) {
        scanLineY = 0;
        scanDirection = 1;
    }
}

void CyberEye::updateHUD() {
    uint32_t currentTime = millis();

    // 定期更新 HUD 数值
    if (currentTime - lastHUDUpdate > CyberEyeConfig::HUD_UPDATE_INTERVAL) {
        // 模拟数据波动
        hudValue += random(-5, 6);
        if (hudValue < 0) hudValue = 0;
        if (hudValue > 100) hudValue = 100;

        lastHUDUpdate = currentTime;
    }
}

void CyberEye::updateGlow() {
    // 更新发光相位
    glowPhase += 0.1f;
    if (glowPhase > TWO_PI) {
        glowPhase -= TWO_PI;
    }
}

void CyberEye::updateDataStream() {
    uint32_t currentTime = millis();

    // 定期更新数据流
    if (currentTime - lastDataUpdate > 50) {  // 每 50ms 更新一次
        // 滚动数据流
        for (int i = 9; i > 0; i--) {
            dataStream[i] = dataStream[i - 1];
        }
        dataStream[0] = random(0, 256);

        lastDataUpdate = currentTime;
    }
}

void CyberEye::randomMove() {
    uint32_t currentTime = millis();

    // 随机改变眼球移动方向
    if (currentTime - lastMoveTime > random(CyberEyeConfig::MOVE_MIN_INTERVAL,
                                            CyberEyeConfig::MOVE_MAX_INTERVAL)) {
        int offsetX = random(-CyberEyeConfig::MOVE_RANGE_X, CyberEyeConfig::MOVE_RANGE_X);
        int offsetY = random(-CyberEyeConfig::MOVE_RANGE_Y, CyberEyeConfig::MOVE_RANGE_Y);

        targetPupilX = eyeX + offsetX;
        targetPupilY = eyeY + offsetY;

        lastMoveTime = currentTime;
    }
}
