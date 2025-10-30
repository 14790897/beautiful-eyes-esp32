#include "DemonEyeRenderer.h"

DemonEyeRenderer::DemonEyeRenderer() : sprite(nullptr) {}

DemonEyeRenderer::~DemonEyeRenderer() {
    if (sprite) {
        delete sprite;
    }
}

void DemonEyeRenderer::begin(lgfx::LGFX_Device* display) {
    sprite = new LGFX_Sprite(display);
    sprite->createSprite(HardwareConfig::SCREEN_WIDTH, HardwareConfig::SCREEN_HEIGHT);
    sprite->setColorDepth(16);
}

// 绘制发光效果
void DemonEyeRenderer::drawGlowEffect(const DemonEye& eye) {
    float intensity = eye.getGlowIntensity();

    // 多层发光效果
    for (int i = 0; i < DemonEyeConfig::GLOW_INTENSITY; i++) {
        float radius = eye.getIrisSize() + i * 3;
        uint8_t alpha = 255 * intensity * (1.0f - (float)i / DemonEyeConfig::GLOW_INTENSITY);

        // 简化的透明度模拟：通过颜色混合
        uint16_t glowColor = DemonColorConfig::GLOW_COLOR;
        sprite->drawCircle(eye.getPupilX(), eye.getPupilY(), radius, glowColor);
    }
}

// 绘制虹膜细节 - 火焰般的纹理
void DemonEyeRenderer::drawIrisDetail(const DemonEye& eye) {
    // 虹膜外圈
    sprite->drawCircle(eye.getPupilX(), eye.getPupilY(), eye.getIrisSize(), DemonColorConfig::IRIS_OUTER);
    sprite->drawCircle(eye.getPupilX(), eye.getPupilY(), eye.getIrisSize() - 1, DemonColorConfig::IRIS_OUTER);

    // 内圈亮光
    sprite->drawCircle(eye.getPupilX(), eye.getPupilY(), eye.getIrisSize() * 0.7, DemonColorConfig::IRIS_INNER);

    // 火焰状径向线条
    for (int i = 0; i < 16; i++) {
        float angle = i * 22.5 * DEG_TO_RAD;
        int innerR = eye.getPupilHeight() / 2 + 3;
        int outerR = eye.getIrisSize() - 2;

        float x1 = eye.getPupilX() + cos(angle) * innerR;
        float y1 = eye.getPupilY() + sin(angle) * innerR;
        float x2 = eye.getPupilX() + cos(angle) * outerR;
        float y2 = eye.getPupilY() + sin(angle) * outerR;

        sprite->drawLine(x1, y1, x2, y2, DemonColorConfig::IRIS_DETAIL);
    }

    // 不规则纹理线条（火焰效果）
    for (int i = 0; i < 8; i++) {
        float angle = i * 45 * DEG_TO_RAD + random(-15, 15) * DEG_TO_RAD;
        int midR = eye.getIrisSize() * 0.5;
        int outerR = eye.getIrisSize() - 3;

        float x1 = eye.getPupilX() + cos(angle) * midR;
        float y1 = eye.getPupilY() + sin(angle) * midR;
        float x2 = eye.getPupilX() + cos(angle + random(-20, 20) * DEG_TO_RAD) * outerR;
        float y2 = eye.getPupilY() + sin(angle + random(-20, 20) * DEG_TO_RAD) * outerR;

        sprite->drawLine(x1, y1, x2, y2, DemonColorConfig::IRIS_INNER);
    }
}

// 绘制竖瞳
void DemonEyeRenderer::drawVerticalPupil(const DemonEye& eye) {
    float halfWidth = eye.getPupilWidth() / 2;
    float halfHeight = eye.getPupilHeight() / 2;

    // 绘制椭圆形竖瞳（近似用填充矩形 + 圆角）
    // 中心矩形
    sprite->fillRect(eye.getPupilX() - halfWidth,
                     eye.getPupilY() - halfHeight,
                     eye.getPupilWidth(),
                     eye.getPupilHeight(),
                     DemonColorConfig::PUPIL_COLOR);

    // 上下圆角
    for (int i = 0; i < halfWidth; i++) {
        int h = sqrt(halfWidth * halfWidth - i * i);
        // 上圆角
        sprite->drawLine(eye.getPupilX() - i, eye.getPupilY() - halfHeight,
                        eye.getPupilY() - i, eye.getPupilY() - halfHeight + h,
                        DemonColorConfig::PUPIL_COLOR);
        sprite->drawLine(eye.getPupilX() + i, eye.getPupilY() - halfHeight,
                        eye.getPupilX() + i, eye.getPupilY() - halfHeight + h,
                        DemonColorConfig::PUPIL_COLOR);
        // 下圆角
        sprite->drawLine(eye.getPupilX() - i, eye.getPupilY() + halfHeight,
                        eye.getPupilX() - i, eye.getPupilY() + halfHeight - h,
                        DemonColorConfig::PUPIL_COLOR);
        sprite->drawLine(eye.getPupilX() + i, eye.getPupilY() + halfHeight,
                        eye.getPupilX() + i, eye.getPupilY() + halfHeight - h,
                        DemonColorConfig::PUPIL_COLOR);
    }
}

// 绘制心形高光
void DemonEyeRenderer::drawHeartHighlight(const DemonEye& eye) {
    float scale = eye.getPupilHeight() * 0.15f;
    float offsetX = -eye.getPupilWidth() * 0.5f;
    float offsetY = -eye.getPupilHeight() * 0.3f;

    float centerX = eye.getPupilX() + offsetX;
    float centerY = eye.getPupilY() + offsetY;

    // 简化的心形：两个小圆 + 三角形
    sprite->fillCircle(centerX - scale * 0.6, centerY, scale * 0.8, DemonColorConfig::HIGHLIGHT_HEART);
    sprite->fillCircle(centerX + scale * 0.6, centerY, scale * 0.8, DemonColorConfig::HIGHLIGHT_HEART);
    sprite->fillTriangle(centerX - scale * 1.2, centerY,
                        centerX + scale * 1.2, centerY,
                        centerX, centerY + scale * 1.5,
                        DemonColorConfig::HIGHLIGHT_HEART);
}

// 绘制性感睫毛
void DemonEyeRenderer::drawSexyEyelashes(float upperY, float lowerY) {
    // 更长、更浓密的睫毛
    for (int i = 0; i < 20; i++) {
        int x = 20 + i * 200 / 20;
        int len = random(12, 20);
        int curve = random(-5, 5);

        // 上睫毛 - 更夸张的弧度
        sprite->drawLine(x, upperY, x + curve, upperY - len, DemonColorConfig::EYELASH_COLOR);
        sprite->drawLine(x + 1, upperY, x + curve + 1, upperY - len, DemonColorConfig::EYELASH_COLOR);

        // 下睫毛
        sprite->drawLine(x, lowerY, x - curve, lowerY + len - 8, DemonColorConfig::EYELASH_COLOR);
    }
}

void DemonEyeRenderer::render(const DemonEye& eye) {
    // 清空背景为黑色（魅魔眼睛的背景）
    sprite->fillSprite(0x0000);

    // 计算眨眼时的眼睛可见区域
    float visibleHeight = 100 * (1.0 - eye.getBlinkProgress());
    float upperY = eye.getEyeY() - visibleHeight;
    float lowerY = eye.getEyeY() + visibleHeight;

    // 调试：确保眼睛可见
    if (visibleHeight > 5) {
        // 绘制巩膜（黑色眼白）
        sprite->fillEllipse(eye.getEyeX(), eye.getEyeY(), 90, visibleHeight, DemonColorConfig::SCLERA_COLOR);

        // 绘制发光效果
        drawGlowEffect(eye);

        // 绘制虹膜（红色圆形应该很明显）
        sprite->fillCircle(eye.getPupilX(), eye.getPupilY(), eye.getIrisSize(), DemonColorConfig::IRIS_COLOR);

        // 绘制虹膜细节
        drawIrisDetail(eye);

        // 绘制竖瞳
        drawVerticalPupil(eye);

        // 绘制心形高光
        drawHeartHighlight(eye);

        // 绘制眼睑（上下遮挡）
        if (upperY > 0) {
            sprite->fillRect(0, 0, HardwareConfig::SCREEN_WIDTH, upperY, DemonColorConfig::EYELID_COLOR);
        }
        if (lowerY < HardwareConfig::SCREEN_HEIGHT) {
            sprite->fillRect(0, lowerY, HardwareConfig::SCREEN_WIDTH,
                            HardwareConfig::SCREEN_HEIGHT - lowerY, DemonColorConfig::EYELID_COLOR);
        }

        // 绘制性感睫毛
        drawSexyEyelashes(upperY, lowerY);
    } else {
        // 完全闭眼状态
        sprite->fillSprite(DemonColorConfig::EYELID_COLOR);
        sprite->fillRect(20, 118, 200, 4, DemonColorConfig::EYELID_SHADOW);
    }

    // 推送到屏幕
    sprite->pushSprite(0, 0);
}
