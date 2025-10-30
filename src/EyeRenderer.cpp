#include "EyeRenderer.h"

EyeRenderer::EyeRenderer() : sprite(nullptr) {}

EyeRenderer::~EyeRenderer() {
}

void EyeRenderer::begin(LGFX_Sprite* sharedSprite) {
    sprite = sharedSprite;
}

void EyeRenderer::drawVeins(const Eye& eye) {
    for (int i = 0; i < 5; i++) {
        int startAngle = random(360);
        int startR = eye.getIrisSize() + 10 + random(20);
        int endR = startR + random(30, 60);

        float startX = eye.getEyeX() + cos(startAngle * DEG_TO_RAD) * startR;
        float startY = eye.getEyeY() + sin(startAngle * DEG_TO_RAD) * startR;
        float endX = eye.getEyeX() + cos((startAngle + random(-30, 30)) * DEG_TO_RAD) * endR;
        float endY = eye.getEyeY() + sin((startAngle + random(-30, 30)) * DEG_TO_RAD) * endR;

        sprite->drawLine(startX, startY, endX, endY, ColorConfig::VEIN_COLOR);
    }
}

void EyeRenderer::drawIrisDetail(const Eye& eye) {
    // 虹膜外圈较深
    sprite->drawCircle(eye.getPupilX(), eye.getPupilY(), eye.getIrisSize(), ColorConfig::IRIS_OUTER);
    sprite->drawCircle(eye.getPupilX(), eye.getPupilY(), eye.getIrisSize() - 1, ColorConfig::IRIS_OUTER);

    // 虹膜纹理(径向线条)
    for (int i = 0; i < 12; i++) {
        float angle = i * 30 * DEG_TO_RAD;
        int innerR = eye.getPupilSize() + 5;
        int outerR = eye.getIrisSize() - 3;

        float x1 = eye.getPupilX() + cos(angle) * innerR;
        float y1 = eye.getPupilY() + sin(angle) * innerR;
        float x2 = eye.getPupilX() + cos(angle) * outerR;
        float y2 = eye.getPupilY() + sin(angle) * outerR;

        sprite->drawLine(x1, y1, x2, y2, ColorConfig::IRIS_DETAIL);
    }
}

void EyeRenderer::drawReflections(const Eye& eye) {
    float pupilSize = eye.getPupilSize();

    // 主高光
    sprite->fillCircle(eye.getPupilX() - pupilSize * 0.3,
                       eye.getPupilY() - pupilSize * 0.3,
                       pupilSize * 0.25, ColorConfig::HIGHLIGHT_MAIN);

    // 次高光
    sprite->fillCircle(eye.getPupilX() + pupilSize * 0.4,
                       eye.getPupilY() + pupilSize * 0.2,
                       pupilSize * 0.15, ColorConfig::HIGHLIGHT_SEC);
}

void EyeRenderer::drawEyelashes(float upperY, float lowerY) {
    for (int i = 0; i < 15; i++) {
        int x = 30 + i * 180 / 15;
        int len = random(8, 15);
        // 上睫毛
        sprite->drawLine(x, upperY, x + random(-3, 3), upperY - len, ColorConfig::EYELASH_COLOR);
        // 下睫毛
        sprite->drawLine(x, lowerY, x + random(-3, 3), lowerY + len - 3, ColorConfig::EYELASH_COLOR);
    }
}

void EyeRenderer::render(const Eye& eye) {
    // 清空背景
    sprite->fillSprite(ColorConfig::EYELID_COLOR);

    // 计算眨眼时的眼睛可见区域
    float visibleHeight = 100 * (1.0 - eye.getBlinkProgress());
    float upperY = eye.getEyeY() - visibleHeight;
    float lowerY = eye.getEyeY() + visibleHeight;

    if (visibleHeight > 5) {
        // 绘制眼白(椭圆形)
        sprite->fillEllipse(eye.getEyeX(), eye.getEyeY(), 90, visibleHeight, ColorConfig::SCLERA_COLOR);

        // 绘制血管
        if (random(100) < 30) {
            drawVeins(eye);
        }

        // 绘制虹膜
        sprite->fillCircle(eye.getPupilX(), eye.getPupilY(), eye.getIrisSize(), ColorConfig::IRIS_COLOR);

        // 绘制虹膜细节
        drawIrisDetail(eye);

        // 绘制瞳孔
        sprite->fillCircle(eye.getPupilX(), eye.getPupilY(), eye.getPupilSize(), ColorConfig::PUPIL_COLOR);

        // 绘制高光
        drawReflections(eye);

        // 绘制眼睑阴影
        sprite->fillRect(0, 0, HardwareConfig::SCREEN_WIDTH, upperY, ColorConfig::EYELID_COLOR);
        sprite->fillRect(0, lowerY, HardwareConfig::SCREEN_WIDTH,
                        HardwareConfig::SCREEN_HEIGHT - lowerY, ColorConfig::EYELID_COLOR);

        // 绘制睫毛
        drawEyelashes(upperY, lowerY);
    } else {
        // 完全闭眼状态 - 绘制眼睑线
        sprite->fillSprite(ColorConfig::EYELID_COLOR);
        sprite->fillRect(20, 118, 200, 4, ColorConfig::EYELID_SHADOW);
    }

    // 推送到屏幕
    sprite->pushSprite(0, 0);
}
