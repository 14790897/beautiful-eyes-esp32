#include "eyes/wheel/WheelEye.h"

WheelEye::WheelEye() {
    // 初始化位置
    eyeX = WheelEyeConfig::EYE_CENTER_X;
    eyeY = WheelEyeConfig::EYE_CENTER_Y;
    pupilX = eyeX;
    pupilY = eyeY;
    targetPupilX = eyeX;
    targetPupilY = eyeY;

    // 初始化大小
    irisSize = WheelEyeConfig::IRIS_SIZE;
    pupilSize = WheelEyeConfig::PUPIL_SIZE;

    // 初始化眨眼状态
    blinkProgress = 0.0f;
    targetBlinkProgress = 0.0f;
    lastBlinkTime = millis();
    blinkDuration = random(WheelEyeConfig::BLINK_MIN_INTERVAL,
                          WheelEyeConfig::BLINK_MAX_INTERVAL);

    // 初始化运动状态
    lastMoveTime = millis();

    // 初始化显轮眼效果
    wheelRotation = 0.0f;
    glowIntensity = 0.8f;
    glowPhase = 0.0f;

    // 初始化三个勾玉的位置
    for (int i = 0; i < WheelEyeConfig::TOMOE_COUNT; i++) {
        float angle = (i * TWO_PI / WheelEyeConfig::TOMOE_COUNT) + wheelRotation;
        tomoes[i].x = cos(angle) * WheelEyeConfig::TOMOE_DISTANCE;
        tomoes[i].y = sin(angle) * WheelEyeConfig::TOMOE_DISTANCE;
        tomoes[i].angle = angle;
    }
}

void WheelEye::updateMovement() {
    // 平滑移动瞳孔到目标位置
    pupilX += (targetPupilX - pupilX) * WheelEyeConfig::PUPIL_SMOOTH;
    pupilY += (targetPupilY - pupilY) * WheelEyeConfig::PUPIL_SMOOTH;
}

void WheelEye::updateBlink() {
    uint32_t currentTime = millis();

    // 检查是否该眨眼了
    if (currentTime - lastBlinkTime > blinkDuration && targetBlinkProgress == 0.0f) {
        targetBlinkProgress = 1.0f;
    }

    // 平滑过渡到目标眨眼状态
    if (blinkProgress < targetBlinkProgress) {
        blinkProgress += WheelEyeConfig::BLINK_SPEED;
        if (blinkProgress >= targetBlinkProgress) {
            blinkProgress = targetBlinkProgress;
            if (targetBlinkProgress >= 1.0f) {
                targetBlinkProgress = 0.0f;
                lastBlinkTime = currentTime;
                blinkDuration = random(WheelEyeConfig::BLINK_MIN_INTERVAL,
                                      WheelEyeConfig::BLINK_MAX_INTERVAL);
            }
        }
    } else if (blinkProgress > targetBlinkProgress) {
        blinkProgress -= WheelEyeConfig::BLINK_SPEED;
        if (blinkProgress <= targetBlinkProgress) {
            blinkProgress = targetBlinkProgress;
        }
    }
}

void WheelEye::updateWheelRotation() {
    // 缓慢旋转勾玉轮盘
    wheelRotation += WheelEyeConfig::ROTATION_SPEED;
    if (wheelRotation > TWO_PI) {
        wheelRotation -= TWO_PI;
    }

    // 更新每个勾玉的位置
    for (int i = 0; i < WheelEyeConfig::TOMOE_COUNT; i++) {
        float angle = (i * TWO_PI / WheelEyeConfig::TOMOE_COUNT) + wheelRotation;
        tomoes[i].x = cos(angle) * WheelEyeConfig::TOMOE_DISTANCE;
        tomoes[i].y = sin(angle) * WheelEyeConfig::TOMOE_DISTANCE;
        tomoes[i].angle = angle;
    }
}

void WheelEye::updateGlow() {
    // 更新发光效果相位
    glowPhase += 0.05f;
    if (glowPhase > TWO_PI) {
        glowPhase -= TWO_PI;
    }

    // 脉动发光强度
    glowIntensity = 0.5f + 0.3f * sin(glowPhase);
}

void WheelEye::randomMove() {
    uint32_t currentTime = millis();

    // 随机改变眼球移动方向
    if (currentTime - lastMoveTime > random(WheelEyeConfig::MOVE_MIN_INTERVAL,
                                            WheelEyeConfig::MOVE_MAX_INTERVAL)) {
        int offsetX = random(-WheelEyeConfig::MOVE_RANGE_X, WheelEyeConfig::MOVE_RANGE_X);
        int offsetY = random(-WheelEyeConfig::MOVE_RANGE_Y, WheelEyeConfig::MOVE_RANGE_Y);

        targetPupilX = eyeX + offsetX;
        targetPupilY = eyeY + offsetY;

        lastMoveTime = currentTime;
    }
}
