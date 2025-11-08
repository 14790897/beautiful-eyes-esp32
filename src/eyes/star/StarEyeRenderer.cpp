#include "eyes/star/StarEyeRenderer.h"

StarEyeRenderer::StarEyeRenderer() : sprite(nullptr) {}

StarEyeRenderer::~StarEyeRenderer() {
}

void StarEyeRenderer::begin(LGFX_Sprite* sharedSprite) {
    sprite = sharedSprite;
}

void StarEyeRenderer::drawGradientIris(const StarEye& eye) {
    float centerX = eye.getPupilX();
    float centerY = eye.getPupilY();
    float irisSize = eye.getIrisSize();

    // 绘制粉紫色渐变虹膜 - 从外到内
    // 外圈 - 粉紫色
    sprite->fillCircle(centerX, centerY, irisSize, StarColorConfig::IRIS_OUTER);

    // 中圈 - 亮粉色
    sprite->fillCircle(centerX, centerY, irisSize * 0.75f, StarColorConfig::IRIS_MIDDLE);

    // 内圈 - 粉白色
    sprite->fillCircle(centerX, centerY, irisSize * 0.5f, StarColorConfig::IRIS_INNER);

    // 添加细腻的径向渐变效果
    int rays = 16;  // 16条径向渐变线
    for (int i = 0; i < rays; i++) {
        float angle = (i * TWO_PI / rays);

        // 绘制从中心向外的渐变射线
        for (float r = irisSize * 0.3f; r < irisSize; r += 3) {
            float x = centerX + cos(angle) * r;
            float y = centerY + sin(angle) * r;

            // 计算颜色 - 越靠外越深
            float ratio = r / irisSize;
            uint8_t alpha = (1.0f - ratio) * 100;

            if (alpha > 10) {
                uint16_t rayColor = sprite->color565(
                    255,
                    200 - alpha,
                    255 - alpha * 0.5f
                );
                sprite->drawPixel(x, y, rayColor);
            }
        }
    }

    // 绘制虹膜外圈轮廓(淡粉色)
    sprite->drawCircle(centerX, centerY, irisSize, StarColorConfig::IRIS_OUTER);
}

void StarEyeRenderer::drawStarPupil(const StarEye& eye) {
    float centerX = eye.getPupilX();
    float centerY = eye.getPupilY();
    float pupilSize = eye.getPupilSize();
    float rotation = eye.getStarRotation();
    int points = StarEyeConfig::STAR_POINTS;
    float innerRatio = StarEyeConfig::STAR_INNER_RATIO;

    // 计算四角星的顶点
    float outerRadius = pupilSize;
    float innerRadius = pupilSize * innerRatio;

    // 绘制星形 - 使用填充三角形
    for (int i = 0; i < points * 2; i++) {
        float angle1 = (i * PI / points) + rotation;
        float angle2 = ((i + 1) * PI / points) + rotation;

        float r1 = (i % 2 == 0) ? outerRadius : innerRadius;
        float r2 = ((i + 1) % 2 == 0) ? outerRadius : innerRadius;

        float x1 = centerX + cos(angle1) * r1;
        float y1 = centerY + sin(angle1) * r1;
        float x2 = centerX + cos(angle2) * r2;
        float y2 = centerY + sin(angle2) * r2;

        // 绘制从中心到边缘的三角形
        sprite->fillTriangle(centerX, centerY, x1, y1, x2, y2,
                            StarColorConfig::PUPIL_COLOR);
    }

    // 绘制星形轮廓
    for (int i = 0; i < points * 2; i++) {
        float angle1 = (i * PI / points) + rotation;
        float angle2 = ((i + 1) * PI / points) + rotation;

        float r1 = (i % 2 == 0) ? outerRadius : innerRadius;
        float r2 = ((i + 1) % 2 == 0) ? outerRadius : innerRadius;

        float x1 = centerX + cos(angle1) * r1;
        float y1 = centerY + sin(angle1) * r1;
        float x2 = centerX + cos(angle2) * r2;
        float y2 = centerY + sin(angle2) * r2;

        sprite->drawLine(x1, y1, x2, y2, StarColorConfig::PUPIL_COLOR);
    }

    // 绘制白色中心核心
    sprite->fillCircle(centerX, centerY, pupilSize * 0.25f, StarColorConfig::PUPIL_CORE);
}

void StarEyeRenderer::drawSparkles(const StarEye& eye) {
    float centerX = eye.getPupilX();
    float centerY = eye.getPupilY();
    const StarEye::Sparkle* sparkles = eye.getSparkles();

    // 绘制闪烁点
    for (int i = 0; i < StarEyeConfig::SPARKLE_COUNT; i++) {
        float x = centerX + sparkles[i].x;
        float y = centerY + sparkles[i].y;
        float brightness = sparkles[i].brightness;

        // 闪烁点颜色
        uint16_t color = sprite->color565(
            255 * brightness,
            255 * brightness,
            255
        );

        // 绘制十字形闪烁
        sprite->fillCircle(x, y, 2, color);

        if (brightness > 0.7f) {
            // 亮度高时添加十字光芒
            sprite->drawPixel(x - 2, y, StarColorConfig::SPARKLE_COLOR);
            sprite->drawPixel(x + 2, y, StarColorConfig::SPARKLE_COLOR);
            sprite->drawPixel(x, y - 2, StarColorConfig::SPARKLE_COLOR);
            sprite->drawPixel(x, y + 2, StarColorConfig::SPARKLE_COLOR);
        }

        if (brightness > 0.85f) {
            // 非常亮时添加对角线光芒
            sprite->drawPixel(x - 1, y - 1, StarColorConfig::SPARKLE_COLOR);
            sprite->drawPixel(x + 1, y + 1, StarColorConfig::SPARKLE_COLOR);
            sprite->drawPixel(x - 1, y + 1, StarColorConfig::SPARKLE_COLOR);
            sprite->drawPixel(x + 1, y - 1, StarColorConfig::SPARKLE_COLOR);
        }
    }
}

void StarEyeRenderer::drawHighlights(const StarEye& eye) {
    float pupilX = eye.getPupilX();
    float pupilY = eye.getPupilY();
    float irisSize = eye.getIrisSize();

    // 主高光 - 左上方较大的高光
    float mainHighlightX = pupilX - irisSize * 0.35f;
    float mainHighlightY = pupilY - irisSize * 0.4f;

    // 绘制主高光(椭圆形)
    sprite->fillEllipse(mainHighlightX, mainHighlightY, 10, 14,
                       StarColorConfig::HIGHLIGHT_MAIN);
    sprite->fillEllipse(mainHighlightX, mainHighlightY, 6, 9,
                       0xFFFF);  // 白色核心

    // 次高光 - 右下方小高光
    float secHighlightX = pupilX + irisSize * 0.25f;
    float secHighlightY = pupilY + irisSize * 0.3f;
    sprite->fillCircle(secHighlightX, secHighlightY, 4,
                      StarColorConfig::HIGHLIGHT_SEC);
    sprite->fillCircle(secHighlightX, secHighlightY, 2,
                      0xFFFF);

    // 第三高光 - 更小的点缀
    float thirdHighlightX = pupilX - irisSize * 0.15f;
    float thirdHighlightY = pupilY - irisSize * 0.2f;
    sprite->fillCircle(thirdHighlightX, thirdHighlightY, 2, 0xFFFF);
}

void StarEyeRenderer::drawGlowEffect(const StarEye& eye) {
    float centerX = eye.getPupilX();
    float centerY = eye.getPupilY();
    float irisSize = eye.getIrisSize();
    float glowPhase = eye.getGlowPhase();

    // 脉动发光效果
    float glowIntensity = 0.5f + 0.5f * sin(glowPhase);

    // 粉色发光光晕 - 多层半透明圆
    for (int i = 0; i < 3; i++) {
        float glowRadius = irisSize + 2 + i * 2;
        uint8_t alpha = (3 - i) * 25 * glowIntensity;

        uint16_t glowColor = sprite->color565(
            255,
            180 + alpha * 0.3f,
            255
        );

        sprite->drawCircle(centerX, centerY, glowRadius, glowColor);
    }
}

void StarEyeRenderer::drawEyelashes(const StarEye& eye) {
    float eyeX = eye.getEyeX();
    float eyeY = eye.getEyeY();
    float blinkProgress = eye.getBlinkProgress();

    if (blinkProgress < 0.8f) {  // 只在眼睛张开时绘制
        // 上睫毛 - 优雅的弧形
        int lashCount = 12;
        for (int i = 0; i < lashCount; i++) {
            float ratio = (float)i / (lashCount - 1);
            float angle = PI + ratio * PI;  // 从左到右

            float baseX = eyeX + cos(angle) * 90;
            float baseY = eyeY + sin(angle) * 100;

            // 睫毛长度
            int length = 10 + random(-2, 3);
            float lashAngle = angle - HALF_PI;  // 向外

            float endX = baseX + cos(lashAngle) * length;
            float endY = baseY + sin(lashAngle) * length;

            sprite->drawLine(baseX, baseY, endX, endY,
                           StarColorConfig::EYELASH_COLOR);
        }
    }
}

void StarEyeRenderer::drawEyelids(const StarEye& eye) {
    float blinkProgress = eye.getBlinkProgress();

    if (blinkProgress > 0.01f) {
        float eyeY = eye.getEyeY();
        float eyeWidth = HardwareConfig::SCREEN_WIDTH;
        float eyeHeight = HardwareConfig::SCREEN_HEIGHT;

        // 计算眼睑位置
        float upperLidY = eyeY - (eyeHeight * 0.5f) + (eyeHeight * blinkProgress * 0.5f);
        float lowerLidY = eyeY + (eyeHeight * 0.5f) - (eyeHeight * blinkProgress * 0.5f);

        // 绘制上眼睑
        sprite->fillRect(0, 0, eyeWidth, upperLidY + 1,
                        StarColorConfig::EYELID_COLOR);

        // 绘制下眼睑
        sprite->fillRect(0, lowerLidY, eyeWidth, eyeHeight - lowerLidY,
                        StarColorConfig::EYELID_COLOR);
    }
}

void StarEyeRenderer::render(const StarEye& eye) {
    if (!sprite) return;

    // 清空背景为白色
    sprite->fillSprite(StarColorConfig::BG_COLOR);

    // 绘制眼白
    float eyeX = eye.getEyeX();
    float eyeY = eye.getEyeY();
    float visibleHeight = 100 * (1.0 - eye.getBlinkProgress());
    sprite->fillEllipse(eyeX, eyeY, 90, visibleHeight,
                       StarColorConfig::SCLERA_COLOR);

    // 绘制各个元素(从后往前)
    drawGlowEffect(eye);      // 发光效果
    drawGradientIris(eye);    // 粉紫色渐变虹膜
    drawSparkles(eye);        // 闪烁点
    drawStarPupil(eye);       // 星形瞳孔
    drawHighlights(eye);      // 高光
    drawEyelashes(eye);       // 睫毛
    drawEyelids(eye);         // 眼睑(眨眼)

    // 推送到屏幕
    sprite->pushSprite(0, 0);
}
