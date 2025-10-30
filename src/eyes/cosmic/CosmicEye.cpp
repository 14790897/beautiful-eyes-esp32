#include "eyes/cosmic/CosmicEye.h"

CosmicEye::CosmicEye() {
    // 初始化位置
    eyeX = CosmicEyeConfig::EYE_CENTER_X;
    eyeY = CosmicEyeConfig::EYE_CENTER_Y;
    pupilX = eyeX;
    pupilY = eyeY;
    targetPupilX = eyeX;
    targetPupilY = eyeY;

    // 初始化大小
    irisSize = CosmicEyeConfig::IRIS_SIZE;
    pupilSize = CosmicEyeConfig::PUPIL_SIZE;

    // 初始化眨眼状态
    blinkProgress = 0.0f;
    targetBlinkProgress = 0.0f;
    lastBlinkTime = millis();
    blinkDuration = random(CosmicEyeConfig::BLINK_MIN_INTERVAL,
                          CosmicEyeConfig::BLINK_MAX_INTERVAL);

    // 初始化运动状态
    lastMoveTime = millis();

    // 初始化星云旋转
    nebulaRotation = 0.0f;
    nebulaSpeed = 0.02f;

    // 初始化星系旋转
    galaxyRotation = 0.0f;

    // 初始化星星
    for (int i = 0; i < 8; i++) {
        // 在虹膜范围内随机分布星星
        float angle = random(0, 360) * DEG_TO_RAD;
        float distance = random(irisSize * 0.3f, irisSize * 0.8f);
        stars[i].x = cos(angle) * distance;
        stars[i].y = sin(angle) * distance;
        stars[i].brightness = random(50, 100) / 100.0f;
        stars[i].fadeSpeed = random(2, 8) / 100.0f;
    }

    // 初始化流星
    meteor.active = false;
    meteor.life = 0.0f;
    lastMeteorTime = millis();

    // 初始化星云脉动
    nebulaPulse = 0.0f;
}

void CosmicEye::updateMovement() {
    // 平滑移动瞳孔到目标位置
    pupilX += (targetPupilX - pupilX) * CosmicEyeConfig::PUPIL_SMOOTH;
    pupilY += (targetPupilY - pupilY) * CosmicEyeConfig::PUPIL_SMOOTH;
}

void CosmicEye::updateBlink() {
    uint32_t currentTime = millis();

    // 检查是否该眨眼了
    if (currentTime - lastBlinkTime > blinkDuration && targetBlinkProgress == 0.0f) {
        targetBlinkProgress = 1.0f;
    }

    // 平滑过渡到目标眨眼状态
    if (blinkProgress < targetBlinkProgress) {
        blinkProgress += CosmicEyeConfig::BLINK_SPEED;
        if (blinkProgress >= targetBlinkProgress) {
            blinkProgress = targetBlinkProgress;
            if (targetBlinkProgress >= 1.0f) {
                targetBlinkProgress = 0.0f;
                lastBlinkTime = currentTime;
                blinkDuration = random(CosmicEyeConfig::BLINK_MIN_INTERVAL,
                                      CosmicEyeConfig::BLINK_MAX_INTERVAL);
            }
        }
    } else if (blinkProgress > targetBlinkProgress) {
        blinkProgress -= CosmicEyeConfig::BLINK_SPEED;
        if (blinkProgress <= targetBlinkProgress) {
            blinkProgress = targetBlinkProgress;
        }
    }
}

void CosmicEye::updateNebula() {
    // 缓慢旋转星云
    nebulaRotation += nebulaSpeed;
    if (nebulaRotation > TWO_PI) {
        nebulaRotation -= TWO_PI;
    }
}

void CosmicEye::updateGalaxy() {
    // 星系旋转（瞳孔中的螺旋星系）
    galaxyRotation += 0.05f;
    if (galaxyRotation > TWO_PI) {
        galaxyRotation -= TWO_PI;
    }
}

void CosmicEye::updateStars() {
    // 更新每颗星星的闪烁
    for (int i = 0; i < 8; i++) {
        stars[i].brightness += stars[i].fadeSpeed;

        // 反转闪烁方向
        if (stars[i].brightness >= 1.0f) {
            stars[i].brightness = 1.0f;
            stars[i].fadeSpeed = -abs(stars[i].fadeSpeed);
        } else if (stars[i].brightness <= 0.3f) {
            stars[i].brightness = 0.3f;
            stars[i].fadeSpeed = abs(stars[i].fadeSpeed);
        }
    }
}

void CosmicEye::updateMeteor() {
    uint32_t currentTime = millis();

    if (meteor.active) {
        // 移动流星
        meteor.x += meteor.dx;
        meteor.y += meteor.dy;
        meteor.life -= 0.02f;

        // 流星消失
        if (meteor.life <= 0.0f) {
            meteor.active = false;
        }
    } else {
        // 随机生成新流星
        if (currentTime - lastMeteorTime > random(3000, 8000)) {
            meteor.active = true;
            meteor.life = 1.0f;

            // 从虹膜边缘开始
            float angle = random(0, 360) * DEG_TO_RAD;
            meteor.x = cos(angle) * irisSize;
            meteor.y = sin(angle) * irisSize;

            // 向中心方向移动
            float targetAngle = atan2(-meteor.y, -meteor.x);
            meteor.dx = cos(targetAngle) * 3.0f;
            meteor.dy = sin(targetAngle) * 3.0f;

            lastMeteorTime = currentTime;
        }
    }
}

void CosmicEye::updatePulse() {
    // 更新星云脉动相位
    nebulaPulse += 0.08f;
    if (nebulaPulse > TWO_PI) {
        nebulaPulse -= TWO_PI;
    }
}

void CosmicEye::randomMove() {
    uint32_t currentTime = millis();

    // 随机改变眼球移动方向
    if (currentTime - lastMoveTime > random(CosmicEyeConfig::MOVE_MIN_INTERVAL,
                                            CosmicEyeConfig::MOVE_MAX_INTERVAL)) {
        int offsetX = random(-CosmicEyeConfig::MOVE_RANGE_X, CosmicEyeConfig::MOVE_RANGE_X);
        int offsetY = random(-CosmicEyeConfig::MOVE_RANGE_Y, CosmicEyeConfig::MOVE_RANGE_Y);

        targetPupilX = eyeX + offsetX;
        targetPupilY = eyeY + offsetY;

        lastMoveTime = currentTime;
    }
}
