#include "eyes/beautiful/BeautifulEye.h"

BeautifulEye::BeautifulEye() {
    // 初始化位置
    eyeX = BeautifulEyeConfig::EYE_CENTER_X;
    eyeY = BeautifulEyeConfig::EYE_CENTER_Y;
    pupilX = eyeX;
    pupilY = eyeY;
    targetPupilX = eyeX;
    targetPupilY = eyeY;

    // 初始化大小
    irisSize = BeautifulEyeConfig::IRIS_SIZE;
    pupilSize = BeautifulEyeConfig::PUPIL_SIZE;

    // 初始化眨眼状态
    blinkProgress = 0.0f;
    targetBlinkProgress = 0.0f;
    lastBlinkTime = millis();
    blinkDuration = random(BeautifulEyeConfig::BLINK_MIN_INTERVAL,
                          BeautifulEyeConfig::BLINK_MAX_INTERVAL);

    // 初始化运动状态
    lastMoveTime = millis();

    // 初始化闪亮效果
    sparklePhase = 0.0f;
}

void BeautifulEye::updateMovement() {
    // 平滑移动瞳孔到目标位置
    pupilX += (targetPupilX - pupilX) * BeautifulEyeConfig::PUPIL_SMOOTH;
    pupilY += (targetPupilY - pupilY) * BeautifulEyeConfig::PUPIL_SMOOTH;
}

void BeautifulEye::updateBlink() {
    uint32_t currentTime = millis();

    // 检查是否该眨眼了
    if (currentTime - lastBlinkTime > blinkDuration && targetBlinkProgress == 0.0f) {
        targetBlinkProgress = 1.0f;
    }

    // 平滑过渡到目标眨眼状态
    if (blinkProgress < targetBlinkProgress) {
        blinkProgress += BeautifulEyeConfig::BLINK_SPEED;
        if (blinkProgress >= targetBlinkProgress) {
            blinkProgress = targetBlinkProgress;
            if (targetBlinkProgress >= 1.0f) {
                targetBlinkProgress = 0.0f;
                // 立即更新lastBlinkTime,防止重复触发眨眼
                lastBlinkTime = currentTime;
                blinkDuration = random(BeautifulEyeConfig::BLINK_MIN_INTERVAL,
                                      BeautifulEyeConfig::BLINK_MAX_INTERVAL);
            }
        }
    } else if (blinkProgress > targetBlinkProgress) {
        blinkProgress -= BeautifulEyeConfig::BLINK_SPEED;
        if (blinkProgress <= targetBlinkProgress) {
            blinkProgress = targetBlinkProgress;
        }
    }
}

void BeautifulEye::updateSparkle() {
    // 更新闪亮相位
    sparklePhase += 0.08f;
    if (sparklePhase > TWO_PI) {
        sparklePhase -= TWO_PI;
    }
}

void BeautifulEye::randomMove() {
    uint32_t currentTime = millis();

    // 随机改变眼球移动方向
    if (currentTime - lastMoveTime > random(BeautifulEyeConfig::MOVE_MIN_INTERVAL,
                                            BeautifulEyeConfig::MOVE_MAX_INTERVAL)) {
        int offsetX = random(-BeautifulEyeConfig::MOVE_RANGE_X, BeautifulEyeConfig::MOVE_RANGE_X);
        int offsetY = random(-BeautifulEyeConfig::MOVE_RANGE_Y, BeautifulEyeConfig::MOVE_RANGE_Y);

        targetPupilX = eyeX + offsetX;
        targetPupilY = eyeY + offsetY;

        lastMoveTime = currentTime;
    }
}
