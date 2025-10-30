#include "Eye.h"

Eye::Eye() {
    eyeX = EyeConfig::EYE_CENTER_X;
    eyeY = EyeConfig::EYE_CENTER_Y;
    pupilX = EyeConfig::EYE_CENTER_X;
    pupilY = EyeConfig::EYE_CENTER_Y;
    targetPupilX = EyeConfig::EYE_CENTER_X;
    targetPupilY = EyeConfig::EYE_CENTER_Y;
    irisSize = EyeConfig::IRIS_SIZE;
    pupilSize = EyeConfig::PUPIL_SIZE;
    blinkProgress = 0;
    targetBlinkProgress = 0;
    lastBlinkTime = millis();
    blinkDuration = 150;
    lastMoveTime = 0;
}

void Eye::updateMovement() {
    // 平滑移动瞳孔到目标位置
    pupilX += (targetPupilX - pupilX) * EyeConfig::PUPIL_SMOOTH;
    pupilY += (targetPupilY - pupilY) * EyeConfig::PUPIL_SMOOTH;

    // 限制瞳孔移动范围
    float dx = pupilX - eyeX;
    float dy = pupilY - eyeY;
    float dist = sqrt(dx * dx + dy * dy);

    if (dist > EyeConfig::MAX_PUPIL_MOVE) {
        pupilX = eyeX + (dx / dist) * EyeConfig::MAX_PUPIL_MOVE;
        pupilY = eyeY + (dy / dist) * EyeConfig::MAX_PUPIL_MOVE;
    }
}

void Eye::updateBlink() {
    uint32_t currentTime = millis();

    // 随机触发眨眼
    if (currentTime - lastBlinkTime > random(EyeConfig::BLINK_MIN_INTERVAL,
                                              EyeConfig::BLINK_MAX_INTERVAL)
        && blinkProgress == 0) {
        targetBlinkProgress = 1.0;
    }

    // 眨眼动画
    if (blinkProgress < targetBlinkProgress) {
        blinkProgress += EyeConfig::BLINK_SPEED;
        if (blinkProgress >= 1.0) {
            blinkProgress = 1.0;
            targetBlinkProgress = 0;
        }
    } else if (blinkProgress > targetBlinkProgress) {
        blinkProgress -= EyeConfig::BLINK_SPEED;
        if (blinkProgress <= 0) {
            blinkProgress = 0;
            lastBlinkTime = currentTime;
        }
    }
}

void Eye::randomMove() {
    uint32_t currentTime = millis();

    if (currentTime - lastMoveTime > random(EyeConfig::MOVE_MIN_INTERVAL,
                                             EyeConfig::MOVE_MAX_INTERVAL)) {
        // 设置新的注视点
        targetPupilX = eyeX + random(-EyeConfig::MOVE_RANGE_X, EyeConfig::MOVE_RANGE_X);
        targetPupilY = eyeY + random(-EyeConfig::MOVE_RANGE_Y, EyeConfig::MOVE_RANGE_Y);
        lastMoveTime = currentTime;
    }
}
