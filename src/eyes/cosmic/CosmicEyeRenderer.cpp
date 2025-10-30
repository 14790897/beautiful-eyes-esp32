#include "eyes/cosmic/CosmicEyeRenderer.h"

CosmicEyeRenderer::CosmicEyeRenderer() : sprite(nullptr) {}

CosmicEyeRenderer::~CosmicEyeRenderer() {
}

void CosmicEyeRenderer::begin(LGFX_Sprite* sharedSprite) {
    sprite = sharedSprite;
}

void CosmicEyeRenderer::drawNebulaIris(const CosmicEye& eye) {
    float centerX = eye.getPupilX();
    float centerY = eye.getPupilY();
    float irisSize = eye.getIrisSize();
    float rotation = eye.getNebulaRotation();
    float pulse = sin(eye.getNebulaPulse()) * 0.15f + 0.85f;  // 0.7 - 1.0 脉动

    // 绘制多层星云效果，使用紫蓝渐变
    for (int layer = 0; layer < 3; layer++) {
        float layerSize = irisSize * (0.8f - layer * 0.15f) * pulse;
        int segments = 32;

        for (int i = 0; i < segments; i++) {
            float angle1 = (i * TWO_PI / segments) + rotation + layer * 0.5f;
            float angle2 = ((i + 1) * TWO_PI / segments) + rotation + layer * 0.5f;

            // 计算颜色 - 紫到蓝的渐变
            float colorPhase = (float)i / segments;
            uint16_t color;
            if (layer == 0) {
                // 外层 - 深紫色到蓝色
                color = sprite->color565(
                    80 + colorPhase * 40,   // R: 80-120
                    60 + colorPhase * 80,   // G: 60-140
                    150 + colorPhase * 50   // B: 150-200
                );
            } else if (layer == 1) {
                // 中层 - 蓝紫色
                color = sprite->color565(
                    120 + colorPhase * 50,  // R: 120-170
                    100 + colorPhase * 100, // G: 100-200
                    180 + colorPhase * 50   // B: 180-230
                );
            } else {
                // 内层 - 亮蓝色
                color = sprite->color565(
                    140 + colorPhase * 60,  // R: 140-200
                    140 + colorPhase * 80,  // G: 140-220
                    200 + colorPhase * 55   // B: 200-255
                );
            }

            // 绘制星云段
            float x1 = centerX + cos(angle1) * layerSize;
            float y1 = centerY + sin(angle1) * layerSize;
            float x2 = centerX + cos(angle2) * layerSize;
            float y2 = centerY + sin(angle2) * layerSize;

            sprite->drawLine(x1, y1, x2, y2, color);
        }

        // 添加圆环强调边缘
        sprite->drawCircle(centerX, centerY, layerSize,
            sprite->color565(100 + layer * 40, 120 + layer * 50, 200 + layer * 30));
    }

    // 最外圈发光边缘
    sprite->drawCircle(centerX, centerY, irisSize * pulse, CosmicColorConfig::GLOW_COLOR);
    sprite->drawCircle(centerX, centerY, irisSize * pulse - 1, CosmicColorConfig::IRIS_EDGE);
}

void CosmicEyeRenderer::drawGalaxyPupil(const CosmicEye& eye) {
    float centerX = eye.getPupilX();
    float centerY = eye.getPupilY();
    float pupilSize = eye.getPupilSize();
    float rotation = eye.getGalaxyRotation();

    // 绘制黑色瞳孔背景
    sprite->fillCircle(centerX, centerY, pupilSize, 0x0000);

    // 绘制螺旋星系
    int arms = 3;  // 3条旋臂
    for (int arm = 0; arm < arms; arm++) {
        float baseAngle = arm * TWO_PI / arms + rotation;

        // 每条旋臂绘制多个点
        for (float r = 5; r < pupilSize; r += 2) {
            float spiralTightness = 0.3f;
            float angle = baseAngle + r * spiralTightness;

            float x = centerX + cos(angle) * r;
            float y = centerY + sin(angle) * r;

            // 星系臂的颜色 - 从中心向外渐变
            float brightness = 1.0f - (r / pupilSize * 0.5f);
            uint16_t color = sprite->color565(
                150 * brightness,
                180 * brightness,
                255 * brightness
            );

            sprite->fillCircle(x, y, 1, color);

            // 添加一些额外的亮点
            if ((int)r % 5 == 0) {
                sprite->drawPixel(x, y, CosmicColorConfig::STAR_COLOR);
            }
        }
    }

    // 中心亮核
    sprite->fillCircle(centerX, centerY, 3, CosmicColorConfig::STAR_COLOR);
    sprite->fillCircle(centerX, centerY, 2, 0xFFFF);  // 白色核心
}

void CosmicEyeRenderer::drawStars(const CosmicEye& eye) {
    float centerX = eye.getPupilX();
    float centerY = eye.getPupilY();
    const CosmicEye::Star* stars = eye.getStars();

    // 绘制闪烁的星星
    for (int i = 0; i < 8; i++) {
        float x = centerX + stars[i].x;
        float y = centerY + stars[i].y;
        float brightness = stars[i].brightness;

        // 星星颜色随亮度变化
        uint16_t color = sprite->color565(
            200 * brightness,
            220 * brightness,
            255 * brightness
        );

        // 绘制十字形星星
        sprite->fillCircle(x, y, 2, color);
        sprite->drawPixel(x - 2, y, color);
        sprite->drawPixel(x + 2, y, color);
        sprite->drawPixel(x, y - 2, color);
        sprite->drawPixel(x, y + 2, color);

        // 亮度高时添加光晕
        if (brightness > 0.8f) {
            sprite->drawPixel(x - 1, y, CosmicColorConfig::STAR_COLOR);
            sprite->drawPixel(x + 1, y, CosmicColorConfig::STAR_COLOR);
            sprite->drawPixel(x, y - 1, CosmicColorConfig::STAR_COLOR);
            sprite->drawPixel(x, y + 1, CosmicColorConfig::STAR_COLOR);
        }
    }
}

void CosmicEyeRenderer::drawMeteor(const CosmicEye& eye) {
    const CosmicEye::Meteor& meteor = eye.getMeteor();

    if (!meteor.active) return;

    float centerX = eye.getPupilX();
    float centerY = eye.getPupilY();
    float x = centerX + meteor.x;
    float y = centerY + meteor.y;

    // 流星颜色 - 白色到蓝色渐变
    uint16_t headColor = sprite->color565(
        255 * meteor.life,
        255 * meteor.life,
        255
    );

    // 绘制流星头部
    sprite->fillCircle(x, y, 2, headColor);

    // 绘制流星尾迹
    for (int i = 1; i <= 5; i++) {
        float trailX = x - meteor.dx * i * 0.5f;
        float trailY = y - meteor.dy * i * 0.5f;
        float trailAlpha = meteor.life * (1.0f - i * 0.15f);

        if (trailAlpha > 0) {
            uint16_t trailColor = sprite->color565(
                150 * trailAlpha,
                180 * trailAlpha,
                255 * trailAlpha
            );
            sprite->drawPixel(trailX, trailY, trailColor);
        }
    }
}

void CosmicEyeRenderer::drawCosmicGlow(const CosmicEye& eye) {
    float centerX = eye.getPupilX();
    float centerY = eye.getPupilY();
    float irisSize = eye.getIrisSize();
    float pulse = sin(eye.getNebulaPulse()) * 0.5f + 0.5f;

    // 外部光晕 - 多层半透明圆
    for (int i = 0; i < 3; i++) {
        float glowRadius = irisSize + 5 + i * 3;
        uint8_t alpha = (3 - i) * 30 * pulse;

        uint16_t glowColor = sprite->color565(
            alpha,
            alpha * 1.2f,
            alpha * 1.5f
        );

        sprite->drawCircle(centerX, centerY, glowRadius, glowColor);
    }
}

void CosmicEyeRenderer::drawEyelids(const CosmicEye& eye) {
    float blinkProgress = eye.getBlinkProgress();

    if (blinkProgress > 0.01f) {
        float eyeY = eye.getEyeY();
        float eyeWidth = HardwareConfig::SCREEN_WIDTH;
        float eyeHeight = HardwareConfig::SCREEN_HEIGHT;

        // 计算眼睑位置
        float upperLidY = eyeY - (eyeHeight * 0.5f) + (eyeHeight * blinkProgress * 0.5f);
        float lowerLidY = eyeY + (eyeHeight * 0.5f) - (eyeHeight * blinkProgress * 0.5f);

        // 绘制上眼睑（深紫色）
        sprite->fillRect(0, 0, eyeWidth, upperLidY + 1, CosmicColorConfig::EYELID_COLOR);

        // 绘制下眼睑
        sprite->fillRect(0, lowerLidY, eyeWidth, eyeHeight - lowerLidY, CosmicColorConfig::EYELID_COLOR);

        // 眼睑边缘高光
        sprite->drawFastHLine(0, upperLidY, eyeWidth, CosmicColorConfig::EYELID_EDGE);
        sprite->drawFastHLine(0, lowerLidY, eyeWidth, CosmicColorConfig::EYELID_EDGE);
    }
}

void CosmicEyeRenderer::render(const CosmicEye& eye) {
    if (!sprite) return;

    // 清空背景为深色宇宙背景
    sprite->fillSprite(CosmicColorConfig::BG_COLOR);

    // 绘制各个元素
    drawCosmicGlow(eye);      // 外部光晕
    drawNebulaIris(eye);      // 星云虹膜
    drawStars(eye);           // 闪烁星星
    drawMeteor(eye);          // 流星
    drawGalaxyPupil(eye);     // 星系瞳孔
    drawEyelids(eye);         // 眼睑（眨眼）

    // 推送到屏幕
    sprite->pushSprite(0, 0);
}
