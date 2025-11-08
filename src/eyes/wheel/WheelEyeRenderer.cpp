#include "eyes/wheel/WheelEyeRenderer.h"

WheelEyeRenderer::WheelEyeRenderer() : sprite(nullptr) {}

WheelEyeRenderer::~WheelEyeRenderer() {
}

void WheelEyeRenderer::begin(LGFX_Sprite* sharedSprite) {
    sprite = sharedSprite;
}

void WheelEyeRenderer::drawRedIris(const WheelEye& eye) {
    float centerX = eye.getPupilX();
    float centerY = eye.getPupilY();
    float irisSize = eye.getIrisSize();

    // 绘制红色虹膜 - 多层渐变
    // 外圈 - 深红色
    sprite->fillCircle(centerX, centerY, irisSize, WheelColorConfig::IRIS_OUTER);

    // 中圈 - 鲜红色
    sprite->fillCircle(centerX, centerY, irisSize * 0.85f, WheelColorConfig::IRIS_COLOR);

    // 内圈 - 橙红色
    sprite->fillCircle(centerX, centerY, irisSize * 0.65f, WheelColorConfig::IRIS_INNER);

    // 绘制虹膜外圈轮廓
    sprite->drawCircle(centerX, centerY, irisSize, WheelColorConfig::WHEEL_LINE_COLOR);
    sprite->drawCircle(centerX, centerY, irisSize - 1, WheelColorConfig::WHEEL_LINE_COLOR);
}

void WheelEyeRenderer::drawWheelPattern(const WheelEye& eye) {
    float centerX = eye.getPupilX();
    float centerY = eye.getPupilY();
    float irisSize = eye.getIrisSize();

    // 绘制从中心向外发散的辐射线（显轮眼特征）
    int lineCount = 12;  // 12条辐射线
    for (int i = 0; i < lineCount; i++) {
        float angle = (i * TWO_PI / lineCount) + eye.getWheelRotation() * 0.3f;

        // 起点在瞳孔边缘
        float startR = eye.getPupilSize() + 5;
        float endR = irisSize * 0.9f;

        float x1 = centerX + cos(angle) * startR;
        float y1 = centerY + sin(angle) * startR;
        float x2 = centerX + cos(angle) * endR;
        float y2 = centerY + sin(angle) * endR;

        // 绘制黑色辐射线
        sprite->drawLine(x1, y1, x2, y2, WheelColorConfig::WHEEL_LINE_COLOR);
    }

    // 绘制中间圆环
    float midRadius = (eye.getPupilSize() + irisSize) * 0.5f;
    sprite->drawCircle(centerX, centerY, midRadius, WheelColorConfig::WHEEL_LINE_COLOR);
}

void WheelEyeRenderer::drawTomoes(const WheelEye& eye) {
    float centerX = eye.getPupilX();
    float centerY = eye.getPupilY();
    const WheelEye::Tomoe* tomoes = eye.getTomoes();
    float tomoeSize = WheelEyeConfig::TOMOE_SIZE;

    // 绘制三个勾玉
    for (int i = 0; i < WheelEyeConfig::TOMOE_COUNT; i++) {
        float x = centerX + tomoes[i].x;
        float y = centerY + tomoes[i].y;
        float angle = tomoes[i].angle;

        // 勾玉主体 - 逗号形状
        // 圆形头部
        sprite->fillCircle(x, y, tomoeSize * 0.6f, WheelColorConfig::TOMOE_COLOR);

        // 尾部 - 使用三角形近似
        float tailAngle = angle + PI;
        float tailLength = tomoeSize * 1.2f;

        float tailX1 = x + cos(tailAngle) * tailLength;
        float tailY1 = y + sin(tailAngle) * tailLength;

        float perpAngle1 = tailAngle + HALF_PI;
        float perpAngle2 = tailAngle - HALF_PI;

        float tailWidth = tomoeSize * 0.4f;
        float tailX2 = x + cos(perpAngle1) * tailWidth;
        float tailY2 = y + sin(perpAngle1) * tailWidth;
        float tailX3 = x + cos(perpAngle2) * tailWidth;
        float tailY3 = y + sin(perpAngle2) * tailWidth;

        // 绘制尾部三角形
        sprite->fillTriangle(tailX1, tailY1, tailX2, tailY2, tailX3, tailY3,
                            WheelColorConfig::TOMOE_COLOR);

        // 填充头部到尾部的连接
        sprite->fillCircle(x + cos(tailAngle) * tomoeSize * 0.3f,
                          y + sin(tailAngle) * tomoeSize * 0.3f,
                          tomoeSize * 0.5f,
                          WheelColorConfig::TOMOE_COLOR);
    }
}

void WheelEyeRenderer::drawPupil(const WheelEye& eye) {
    float centerX = eye.getPupilX();
    float centerY = eye.getPupilY();
    float pupilSize = eye.getPupilSize();

    // 绘制黑色瞳孔
    sprite->fillCircle(centerX, centerY, pupilSize, WheelColorConfig::PUPIL_COLOR);

    // 绘制瞳孔外圈
    sprite->drawCircle(centerX, centerY, pupilSize, WheelColorConfig::WHEEL_LINE_COLOR);
}

void WheelEyeRenderer::drawGlowEffect(const WheelEye& eye) {
    float centerX = eye.getPupilX();
    float centerY = eye.getPupilY();
    float irisSize = eye.getIrisSize();
    float glowIntensity = eye.getGlowIntensity();

    // 红色发光效果 - 多层半透明圆
    for (int i = 0; i < 3; i++) {
        float glowRadius = irisSize + 3 + i * 2;
        uint8_t alpha = (3 - i) * 30 * glowIntensity;

        uint16_t glowColor = sprite->color565(
            255,
            alpha * 0.3f,  // 少量绿色
            alpha * 0.2f   // 少量蓝色
        );

        sprite->drawCircle(centerX, centerY, glowRadius, glowColor);
    }
}

void WheelEyeRenderer::drawHighlights(const WheelEye& eye) {
    float pupilX = eye.getPupilX();
    float pupilY = eye.getPupilY();
    float pupilSize = eye.getPupilSize();

    // 主高光 - 左上方
    float highlightX = pupilX - pupilSize * 0.3f;
    float highlightY = pupilY - pupilSize * 0.3f;
    sprite->fillCircle(highlightX, highlightY, 4, WheelColorConfig::HIGHLIGHT_COLOR);
    sprite->fillCircle(highlightX, highlightY, 2, 0xFFFF);  // 白色核心

    // 次高光 - 右下方
    float secHighlightX = pupilX + pupilSize * 0.4f;
    float secHighlightY = pupilY + pupilSize * 0.4f;
    sprite->fillCircle(secHighlightX, secHighlightY, 2, WheelColorConfig::HIGHLIGHT_COLOR);
}

void WheelEyeRenderer::drawEyelids(const WheelEye& eye) {
    float blinkProgress = eye.getBlinkProgress();

    if (blinkProgress > 0.01f) {
        float eyeY = eye.getEyeY();
        float eyeWidth = HardwareConfig::SCREEN_WIDTH;
        float eyeHeight = HardwareConfig::SCREEN_HEIGHT;

        // 计算眼睑位置
        float upperLidY = eyeY - (eyeHeight * 0.5f) + (eyeHeight * blinkProgress * 0.5f);
        float lowerLidY = eyeY + (eyeHeight * 0.5f) - (eyeHeight * blinkProgress * 0.5f);

        // 绘制上眼睑
        sprite->fillRect(0, 0, eyeWidth, upperLidY + 1, WheelColorConfig::EYELID_COLOR);

        // 绘制下眼睑
        sprite->fillRect(0, lowerLidY, eyeWidth, eyeHeight - lowerLidY,
                        WheelColorConfig::EYELID_COLOR);

        // 眼睑边缘
        sprite->drawFastHLine(0, upperLidY, eyeWidth, WheelColorConfig::WHEEL_LINE_COLOR);
        sprite->drawFastHLine(0, lowerLidY, eyeWidth, WheelColorConfig::WHEEL_LINE_COLOR);
    }
}

void WheelEyeRenderer::render(const WheelEye& eye) {
    if (!sprite) return;

    // 清空背景为白色
    sprite->fillSprite(WheelColorConfig::BG_COLOR);

    // 绘制眼白
    float eyeX = eye.getEyeX();
    float eyeY = eye.getEyeY();
    float visibleHeight = 100 * (1.0 - eye.getBlinkProgress());
    sprite->fillEllipse(eyeX, eyeY, 90, visibleHeight, WheelColorConfig::SCLERA_COLOR);

    // 绘制各个元素（从后往前）
    drawGlowEffect(eye);      // 发光效果
    drawRedIris(eye);         // 红色虹膜
    drawWheelPattern(eye);    // 轮盘图案
    drawTomoes(eye);          // 三勾玉
    drawPupil(eye);           // 瞳孔
    drawHighlights(eye);      // 高光
    drawEyelids(eye);         // 眼睑（眨眼）

    // 推送到屏幕
    sprite->pushSprite(0, 0);
}
