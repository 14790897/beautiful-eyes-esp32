#include "eyes/demon/DemonEye.h"

DemonEye::DemonEye() {
    eyeX = DemonEyeConfig::EYE_CENTER_X;
    eyeY = DemonEyeConfig::EYE_CENTER_Y;
    pupilX = DemonEyeConfig::EYE_CENTER_X;
    pupilY = DemonEyeConfig::EYE_CENTER_Y;
    targetPupilX = DemonEyeConfig::EYE_CENTER_X;
    targetPupilY = DemonEyeConfig::EYE_CENTER_Y;
    irisSize = DemonEyeConfig::IRIS_SIZE;
    pupilWidth = DemonEyeConfig::PUPIL_WIDTH;
    pupilHeight = DemonEyeConfig::PUPIL_HEIGHT;
    blinkProgress = 0;
    targetBlinkProgress = 0;
    lastBlinkTime = millis();
    lastMoveTime = 0;
    glowPhase = 0;
    glowIntensity = 1.0f;
}

void DemonEye::updateMovement() {
    // 更快速的平滑移动
    pupilX += (targetPupilX - pupilX) * DemonEyeConfig::PUPIL_SMOOTH;
    pupilY += (targetPupilY - pupilY) * DemonEyeConfig::PUPIL_SMOOTH;

    // 限制瞳孔移动范围
    float dx = pupilX - eyeX;
    float dy = pupilY - eyeY;
    float dist = sqrt(dx * dx + dy * dy);

    if (dist > DemonEyeConfig::MAX_PUPIL_MOVE) {
        pupilX = eyeX + (dx / dist) * DemonEyeConfig::MAX_PUPIL_MOVE;
        pupilY = eyeY + (dy / dist) * DemonEyeConfig::MAX_PUPIL_MOVE;
    }
}

void DemonEye::updateBlink() {
    uint32_t currentTime = millis();

    // 随机触发眨眼
    if (currentTime - lastBlinkTime > random(DemonEyeConfig::BLINK_MIN_INTERVAL,
                                              DemonEyeConfig::BLINK_MAX_INTERVAL)
        && blinkProgress == 0) {
        targetBlinkProgress = 1.0;
    }

    // 更慢的眨眼动画
    if (blinkProgress < targetBlinkProgress) {
        blinkProgress += DemonEyeConfig::BLINK_SPEED;
        if (blinkProgress >= 1.0) {
            blinkProgress = 1.0;
            targetBlinkProgress = 0;
        }
    } else if (blinkProgress > targetBlinkProgress) {
        blinkProgress -= DemonEyeConfig::BLINK_SPEED;
        if (blinkProgress <= 0) {
            blinkProgress = 0;
            lastBlinkTime = currentTime;
        }
    }
}

void DemonEye::updateGlow() {
    // 脉动发光效果
    glowPhase += DemonEyeConfig::GLOW_PULSE_SPEED;
    if (glowPhase > 2 * PI) {
        glowPhase -= 2 * PI;
    }

    // 0.7 到 1.0 之间脉动
    glowIntensity = 0.7f + 0.3f * (sin(glowPhase) * 0.5f + 0.5f);
}

void DemonEye::randomMove() {
    uint32_t currentTime = millis();

    if (currentTime - lastMoveTime > random(DemonEyeConfig::MOVE_MIN_INTERVAL,
                                             DemonEyeConfig::MOVE_MAX_INTERVAL)) {
        // 设置新的注视点 - 更大的移动范围
        targetPupilX = eyeX + random(-DemonEyeConfig::MOVE_RANGE_X, DemonEyeConfig::MOVE_RANGE_X);
        targetPupilY = eyeY + random(-DemonEyeConfig::MOVE_RANGE_Y, DemonEyeConfig::MOVE_RANGE_Y);
        lastMoveTime = currentTime;
    }
}
