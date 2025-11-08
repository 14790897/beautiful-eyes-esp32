#include "eyes/star/StarEye.h"

StarEye::StarEye() {
    // 初始化位置
    eyeX = StarEyeConfig::EYE_CENTER_X;
    eyeY = StarEyeConfig::EYE_CENTER_Y;
    pupilX = eyeX;
    pupilY = eyeY;
    targetPupilX = eyeX;
    targetPupilY = eyeY;

    // 初始化大小
    irisSize = StarEyeConfig::IRIS_SIZE;
    pupilSize = StarEyeConfig::PUPIL_SIZE;

    // 初始化眨眼状态
    blinkProgress = 0.0f;
    targetBlinkProgress = 0.0f;
    lastBlinkTime = millis();
    blinkDuration = random(StarEyeConfig::BLINK_MIN_INTERVAL,
                          StarEyeConfig::BLINK_MAX_INTERVAL);

    // 初始化运动状态
    lastMoveTime = millis();

    // 初始化星瞳眼效果
    starRotation = 0.0f;
    glowPhase = 0.0f;
    heartBeatPhase = 0.0f;

    // 初始化闪烁点
    for (int i = 0; i < StarEyeConfig::SPARKLE_COUNT; i++) {
        // 在虹膜范围内随机分布闪烁点
        float angle = random(0, 360) * DEG_TO_RAD;
        float distance = random(irisSize * 0.4f, irisSize * 0.85f);
        sparkles[i].x = cos(angle) * distance;
        sparkles[i].y = sin(angle) * distance;
        sparkles[i].brightness = random(50, 100) / 100.0f;
        sparkles[i].fadeSpeed = random(3, 10) / 100.0f;
        sparkles[i].phase = random(0, 314) / 100.0f;  // 0 to PI
    }
}

void StarEye::updateMovement() {
    // 平滑移动瞳孔到目标位置
    pupilX += (targetPupilX - pupilX) * StarEyeConfig::PUPIL_SMOOTH;
    pupilY += (targetPupilY - pupilY) * StarEyeConfig::PUPIL_SMOOTH;
}

void StarEye::updateBlink() {
    uint32_t currentTime = millis();

    // 检查是否该眨眼了
    if (currentTime - lastBlinkTime > blinkDuration && targetBlinkProgress == 0.0f) {
        targetBlinkProgress = 1.0f;
    }

    // 平滑过渡到目标眨眼状态
    if (blinkProgress < targetBlinkProgress) {
        blinkProgress += StarEyeConfig::BLINK_SPEED;
        if (blinkProgress >= targetBlinkProgress) {
            blinkProgress = targetBlinkProgress;
            if (targetBlinkProgress >= 1.0f) {
                targetBlinkProgress = 0.0f;
                lastBlinkTime = currentTime;
                blinkDuration = random(StarEyeConfig::BLINK_MIN_INTERVAL,
                                      StarEyeConfig::BLINK_MAX_INTERVAL);
            }
        }
    } else if (blinkProgress > targetBlinkProgress) {
        blinkProgress -= StarEyeConfig::BLINK_SPEED;
        if (blinkProgress <= targetBlinkProgress) {
            blinkProgress = targetBlinkProgress;
        }
    }
}

void StarEye::updateStarRotation() {
    // 缓慢旋转星形瞳孔
    starRotation += 0.01f;
    if (starRotation > TWO_PI) {
        starRotation -= TWO_PI;
    }
}

void StarEye::updateSparkles() {
    // 更新每个闪烁点
    for (int i = 0; i < StarEyeConfig::SPARKLE_COUNT; i++) {
        // 更新相位
        sparkles[i].phase += StarEyeConfig::SPARKLE_SPEED;
        if (sparkles[i].phase > TWO_PI) {
            sparkles[i].phase -= TWO_PI;
        }

        // 使用正弦波产生闪烁效果
        sparkles[i].brightness = 0.3f + 0.7f * (sin(sparkles[i].phase) * 0.5f + 0.5f);
    }
}

void StarEye::updateGlow() {
    // 更新发光相位
    glowPhase += 0.08f;
    if (glowPhase > TWO_PI) {
        glowPhase -= TWO_PI;
    }

    // 更新心跳效果相位(稍慢)
    heartBeatPhase += 0.05f;
    if (heartBeatPhase > TWO_PI) {
        heartBeatPhase -= TWO_PI;
    }
}

void StarEye::randomMove() {
    uint32_t currentTime = millis();

    // 随机改变眼球移动方向
    if (currentTime - lastMoveTime > random(StarEyeConfig::MOVE_MIN_INTERVAL,
                                            StarEyeConfig::MOVE_MAX_INTERVAL)) {
        int offsetX = random(-StarEyeConfig::MOVE_RANGE_X, StarEyeConfig::MOVE_RANGE_X);
        int offsetY = random(-StarEyeConfig::MOVE_RANGE_Y, StarEyeConfig::MOVE_RANGE_Y);

        targetPupilX = eyeX + offsetX;
        targetPupilY = eyeY + offsetY;

        lastMoveTime = currentTime;
    }
}
