#include "eyes/cyber/CyberEyeRenderer.h"

CyberEyeRenderer::CyberEyeRenderer() : sprite(nullptr) {}

CyberEyeRenderer::~CyberEyeRenderer() {
}

void CyberEyeRenderer::begin(LGFX_Sprite* sharedSprite) {
    sprite = sharedSprite;
}

void CyberEyeRenderer::drawGrid() {
    // 绘制背景网格
    for (int x = 0; x < HardwareConfig::SCREEN_WIDTH; x += 20) {
        sprite->drawLine(x, 0, x, HardwareConfig::SCREEN_HEIGHT, CyberColorConfig::GRID_COLOR);
    }
    for (int y = 0; y < HardwareConfig::SCREEN_HEIGHT; y += 20) {
        sprite->drawLine(0, y, HardwareConfig::SCREEN_WIDTH, y, CyberColorConfig::GRID_COLOR);
    }
}

void CyberEyeRenderer::drawMechanicalIris(const CyberEye& eye) {
    float centerX = eye.getPupilX();
    float centerY = eye.getPupilY();
    float irisSize = eye.getIrisSize();

    // 外圈 - 深青色
    sprite->drawCircle(centerX, centerY, irisSize, CyberColorConfig::IRIS_OUTER);
    sprite->drawCircle(centerX, centerY, irisSize - 1, CyberColorConfig::IRIS_OUTER);

    // 主虹膜 - 青色
    sprite->drawCircle(centerX, centerY, irisSize - 3, CyberColorConfig::IRIS_COLOR);
    sprite->drawCircle(centerX, centerY, irisSize - 4, CyberColorConfig::IRIS_COLOR);

    // 内圈 - 亮青色
    sprite->drawCircle(centerX, centerY, irisSize * 0.6f, CyberColorConfig::IRIS_INNER);

    // 机械纹理 - 径向线条
    for (int i = 0; i < 16; i++) {
        float angle = i * 22.5f * DEG_TO_RAD;
        int innerR = eye.getPupilSize() + 5;
        int outerR = irisSize - 5;

        float x1 = centerX + cos(angle) * innerR;
        float y1 = centerY + sin(angle) * innerR;
        float x2 = centerX + cos(angle) * outerR;
        float y2 = centerY + sin(angle) * outerR;

        sprite->drawLine(x1, y1, x2, y2, CyberColorConfig::IRIS_COLOR);
    }

    // 分段圆环
    for (int i = 0; i < 8; i++) {
        float startAngle = i * 45 * DEG_TO_RAD;
        float endAngle = startAngle + 30 * DEG_TO_RAD;
        int radius = irisSize * 0.8f;

        for (float angle = startAngle; angle < endAngle; angle += 0.1f) {
            int x = centerX + cos(angle) * radius;
            int y = centerY + sin(angle) * radius;
            sprite->drawPixel(x, y, CyberColorConfig::IRIS_RING);
        }
    }
}

void CyberEyeRenderer::drawTechRings(const CyberEye& eye) {
    float centerX = eye.getEyeX();
    float centerY = eye.getEyeY();

    // 外层技术环
    for (int r = 80; r < 100; r += 5) {
        // 绘制间断的圆环
        for (int angle = 0; angle < 360; angle += 10) {
            if ((angle / 10) % 2 == 0) {
                float rad = angle * DEG_TO_RAD;
                int x1 = centerX + cos(rad) * r;
                int y1 = centerY + sin(rad) * r;
                int x2 = centerX + cos(rad) * (r + 1);
                int y2 = centerY + sin(rad) * (r + 1);
                sprite->drawLine(x1, y1, x2, y2, CyberColorConfig::HUD_COLOR);
            }
        }
    }
}

void CyberEyeRenderer::drawPupilCamera(const CyberEye& eye) {
    float centerX = eye.getPupilX();
    float centerY = eye.getPupilY();
    float pupilSize = eye.getPupilSize();

    // 黑色瞳孔(摄像头)
    sprite->fillCircle(centerX, centerY, pupilSize, CyberColorConfig::PUPIL_COLOR);

    // 摄像头镜头反光
    sprite->fillCircle(centerX - pupilSize * 0.3f,
                      centerY - pupilSize * 0.3f,
                      pupilSize * 0.2f, CyberColorConfig::HIGHLIGHT_COLOR);

    // 镜头圈
    sprite->drawCircle(centerX, centerY, pupilSize + 2, CyberColorConfig::IRIS_INNER);
}

void CyberEyeRenderer::drawScanLine(const CyberEye& eye) {
    int y = eye.getScanLineY();

    // 主扫描线
    for (int i = 0; i < CyberEyeConfig::SCAN_LINE_HEIGHT; i++) {
        sprite->drawLine(0, y + i, HardwareConfig::SCREEN_WIDTH, y + i,
                        CyberColorConfig::SCAN_LINE_COLOR);
    }

    // 扫描线发光效果
    sprite->drawLine(0, y - 1, HardwareConfig::SCREEN_WIDTH, y - 1,
                    CyberColorConfig::GLOW_COLOR);
    sprite->drawLine(0, y + CyberEyeConfig::SCAN_LINE_HEIGHT,
                    HardwareConfig::SCREEN_WIDTH,
                    y + CyberEyeConfig::SCAN_LINE_HEIGHT,
                    CyberColorConfig::GLOW_COLOR);
}

void CyberEyeRenderer::drawHUD(const CyberEye& eye) {
    // 左上角 HUD 信息
    sprite->setTextColor(CyberColorConfig::HUD_COLOR);
    sprite->setTextSize(1);

    // 状态指示
    sprite->setCursor(5, 5);
    sprite->print("SYS: ONLINE");

    // 数值显示
    sprite->setCursor(5, 15);
    sprite->print("PWR: ");
    sprite->print(eye.getHUDValue());
    sprite->print("%");

    // 右上角时间戳
    sprite->setCursor(160, 5);
    sprite->print(millis() / 1000);
    sprite->print("s");

    // 左下角坐标
    sprite->setCursor(5, 225);
    sprite->print("X:");
    sprite->print((int)eye.getPupilX());
    sprite->print(" Y:");
    sprite->print((int)eye.getPupilY());
}

void CyberEyeRenderer::drawCrosshair(const CyberEye& eye) {
    float centerX = eye.getPupilX();
    float centerY = eye.getPupilY();
    int size = CyberEyeConfig::CROSSHAIR_SIZE;

    // 红色准星
    // 上
    sprite->drawLine(centerX, centerY - size - 5, centerX, centerY - size,
                    CyberColorConfig::CROSSHAIR_COLOR);
    // 下
    sprite->drawLine(centerX, centerY + size, centerX, centerY + size + 5,
                    CyberColorConfig::CROSSHAIR_COLOR);
    // 左
    sprite->drawLine(centerX - size - 5, centerY, centerX - size, centerY,
                    CyberColorConfig::CROSSHAIR_COLOR);
    // 右
    sprite->drawLine(centerX + size, centerY, centerX + size + 5, centerY,
                    CyberColorConfig::CROSSHAIR_COLOR);

    // 中心点
    sprite->fillCircle(centerX, centerY, 2, CyberColorConfig::CROSSHAIR_COLOR);
}

void CyberEyeRenderer::drawDataStream(const CyberEye& eye) {
    const uint8_t* data = eye.getDataStream();

    // 右侧数据流
    sprite->setTextColor(CyberColorConfig::TEXT_COLOR);
    sprite->setTextSize(1);

    for (int i = 0; i < 10; i++) {
        sprite->setCursor(200, 30 + i * 20);

        // 显示十六进制数据
        if (data[i] < 16) sprite->print("0");
        sprite->print(data[i], HEX);
    }
}

void CyberEyeRenderer::drawGlowEffect(const CyberEye& eye) {
    float phase = eye.getGlowPhase();
    float intensity = (sin(phase) + 1.0f) * 0.5f;  // 0-1

    if (intensity > 0.3f) {
        float centerX = eye.getEyeX();
        float centerY = eye.getEyeY();
        float irisSize = eye.getIrisSize();

        // 发光圈
        int glowRadius = irisSize + 5 + (int)(intensity * 10);
        sprite->drawCircle(centerX, centerY, glowRadius, CyberColorConfig::GLOW_COLOR);
    }
}

void CyberEyeRenderer::drawCircuitPattern(const CyberEye& eye) {
    // 在眼白区域绘制电路板图案
    float centerX = eye.getEyeX();
    float centerY = eye.getEyeY();

    // 简单的电路线条
    sprite->drawLine(centerX - 70, centerY - 40, centerX - 50, centerY - 40,
                    CyberColorConfig::GRID_COLOR);
    sprite->drawLine(centerX - 50, centerY - 40, centerX - 50, centerY - 60,
                    CyberColorConfig::GRID_COLOR);

    sprite->drawLine(centerX + 50, centerY + 40, centerX + 70, centerY + 40,
                    CyberColorConfig::GRID_COLOR);
    sprite->drawLine(centerX + 50, centerY + 40, centerX + 50, centerY + 60,
                    CyberColorConfig::GRID_COLOR);

    // 电路节点
    sprite->fillCircle(centerX - 70, centerY - 40, 2, CyberColorConfig::HUD_COLOR);
    sprite->fillCircle(centerX - 50, centerY - 60, 2, CyberColorConfig::HUD_COLOR);
    sprite->fillCircle(centerX + 70, centerY + 40, 2, CyberColorConfig::HUD_COLOR);
    sprite->fillCircle(centerX + 50, centerY + 60, 2, CyberColorConfig::HUD_COLOR);
}

void CyberEyeRenderer::render(const CyberEye& eye) {
    // 清空背景为黑色
    sprite->fillSprite(CyberColorConfig::BG_COLOR);

    // 绘制背景网格
    drawGrid();

    // 计算眨眼时的可见区域
    float visibleHeight = 100 * (1.0 - eye.getBlinkProgress());
    float upperY = eye.getEyeY() - visibleHeight;
    float lowerY = eye.getEyeY() + visibleHeight;

    if (visibleHeight > 5) {
        // 绘制眼白(深蓝灰色椭圆)
        sprite->fillEllipse(eye.getEyeX(), eye.getEyeY(), 90, visibleHeight,
                           CyberColorConfig::SCLERA_COLOR);

        // 绘制电路图案
        drawCircuitPattern(eye);

        // 绘制技术环
        drawTechRings(eye);

        // 绘制机械虹膜
        drawMechanicalIris(eye);

        // 绘制瞳孔摄像头
        drawPupilCamera(eye);

        // 绘制发光效果
        drawGlowEffect(eye);

        // 绘制准星
        drawCrosshair(eye);

        // 绘制眼睑(黑色覆盖)
        sprite->fillRect(0, 0, HardwareConfig::SCREEN_WIDTH, upperY,
                        CyberColorConfig::BG_COLOR);
        sprite->fillRect(0, lowerY, HardwareConfig::SCREEN_WIDTH,
                        HardwareConfig::SCREEN_HEIGHT - lowerY,
                        CyberColorConfig::BG_COLOR);

        // 绘制眼睑分割线
        sprite->drawLine(20, upperY, 220, upperY, CyberColorConfig::IRIS_COLOR);
        sprite->drawLine(20, lowerY, 220, lowerY, CyberColorConfig::IRIS_COLOR);
    } else {
        // 完全闭眼状态
        sprite->fillSprite(CyberColorConfig::BG_COLOR);
        sprite->drawLine(20, 120, 220, 120, CyberColorConfig::IRIS_COLOR);
    }

    // 绘制扫描线(始终显示)
    drawScanLine(eye);

    // 绘制 HUD 信息
    drawHUD(eye);

    // 绘制数据流
    drawDataStream(eye);

    // 推送到屏幕
    sprite->pushSprite(0, 0);
}
