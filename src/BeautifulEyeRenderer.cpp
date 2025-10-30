#include "BeautifulEyeRenderer.h"

BeautifulEyeRenderer::BeautifulEyeRenderer() : sprite(nullptr) {}

BeautifulEyeRenderer::~BeautifulEyeRenderer() {
}

void BeautifulEyeRenderer::begin(LGFX_Sprite* sharedSprite) {
    sprite = sharedSprite;
}

void BeautifulEyeRenderer::drawEyeShape(const BeautifulEye& eye, float visibleHeight) {
    // 绘制纯净的眼白(椭圆形,比普通眼睛更大)
    sprite->fillEllipse(eye.getEyeX(), eye.getEyeY(), 95, visibleHeight,
                       BeautifulColorConfig::SCLERA_COLOR);
}

void BeautifulEyeRenderer::drawEyeShadow(const BeautifulEye& eye, float upperY) {
    // 绘制淡淡的眼影效果(在上眼睑下方)
    for (int i = 0; i < 15; i++) {
        int alpha = 15 - i;  // 渐变透明度
        float y = upperY + i * 0.8f;

        // 使用半透明效果绘制眼影
        sprite->drawLine(30, y, 210, y, BeautifulColorConfig::EYESHADOW_COLOR);
    }
}

void BeautifulEyeRenderer::drawIrisGradient(const BeautifulEye& eye) {
    // 多层次渐变虹膜,从外到内
    float centerX = eye.getPupilX();
    float centerY = eye.getPupilY();
    float irisSize = eye.getIrisSize();

    // 外圈 - 深棕色
    sprite->fillCircle(centerX, centerY, irisSize, BeautifulColorConfig::IRIS_OUTER);

    // 中圈 - 温柔的棕色
    sprite->fillCircle(centerX, centerY, irisSize * 0.85f, BeautifulColorConfig::IRIS_COLOR);

    // 中间渐变
    sprite->fillCircle(centerX, centerY, irisSize * 0.6f, BeautifulColorConfig::IRIS_MIDDLE);

    // 内圈 - 金棕色
    sprite->fillCircle(centerX, centerY, irisSize * 0.35f, BeautifulColorConfig::IRIS_INNER);
}

void BeautifulEyeRenderer::drawIrisDetail(const BeautifulEye& eye) {
    // 精细的虹膜纹理(径向线条,更多更细腻)
    float centerX = eye.getPupilX();
    float centerY = eye.getPupilY();
    float pupilSize = eye.getPupilSize();
    float irisSize = eye.getIrisSize();

    // 绘制24条径向线,营造精致感
    for (int i = 0; i < 24; i++) {
        float angle = i * 15 * DEG_TO_RAD;
        int innerR = pupilSize + 3;
        int outerR = irisSize - 5;

        float x1 = centerX + cos(angle) * innerR;
        float y1 = centerY + sin(angle) * innerR;
        float x2 = centerX + cos(angle) * outerR;
        float y2 = centerY + sin(angle) * outerR;

        sprite->drawLine(x1, y1, x2, y2, BeautifulColorConfig::IRIS_DETAIL);
    }

    // 绘制虹膜外圈加强
    sprite->drawCircle(centerX, centerY, irisSize - 1, BeautifulColorConfig::IRIS_OUTER);
    sprite->drawCircle(centerX, centerY, irisSize - 2, BeautifulColorConfig::IRIS_OUTER);
}

void BeautifulEyeRenderer::drawPupil(const BeautifulEye& eye) {
    // 绘制瞳孔
    sprite->fillCircle(eye.getPupilX(), eye.getPupilY(), eye.getPupilSize(),
                      BeautifulColorConfig::PUPIL_COLOR);
}

void BeautifulEyeRenderer::drawReflections(const BeautifulEye& eye) {
    float pupilX = eye.getPupilX();
    float pupilY = eye.getPupilY();
    float pupilSize = eye.getPupilSize();

    // 主高光 - 更大更明显(左上)
    float mainHighlightX = pupilX - pupilSize * 0.4f;
    float mainHighlightY = pupilY - pupilSize * 0.4f;
    sprite->fillCircle(mainHighlightX, mainHighlightY, pupilSize * 0.35f,
                      BeautifulColorConfig::HIGHLIGHT_MAIN);

    // 次高光 - 淡蓝色,营造水润感(右侧)
    float secHighlightX = pupilX + pupilSize * 0.5f;
    float secHighlightY = pupilY + pupilSize * 0.3f;
    sprite->fillCircle(secHighlightX, secHighlightY, pupilSize * 0.2f,
                      BeautifulColorConfig::HIGHLIGHT_SEC);

    // 第三个小高光(下方)
    float thirdHighlightX = pupilX - pupilSize * 0.2f;
    float thirdHighlightY = pupilY + pupilSize * 0.6f;
    sprite->fillCircle(thirdHighlightX, thirdHighlightY, pupilSize * 0.12f,
                      BeautifulColorConfig::HIGHLIGHT_MAIN);
}

void BeautifulEyeRenderer::drawSparkles(const BeautifulEye& eye) {
    // 在虹膜上绘制闪亮的小星星效果
    float phase = eye.getSparklePhase();
    float centerX = eye.getPupilX();
    float centerY = eye.getPupilY();
    float irisSize = eye.getIrisSize();

    // 绘制3个闪亮点,随着相位变化改变亮度
    for (int i = 0; i < 3; i++) {
        float angle = (phase + i * TWO_PI / 3.0f);
        float brightness = (sin(angle) + 1.0f) * 0.5f;  // 0-1

        if (brightness > 0.6f) {  // 只在亮度足够时绘制
            float dist = irisSize * 0.7f;
            float sparkleX = centerX + cos(angle * 1.3f) * dist;
            float sparkleY = centerY + sin(angle * 1.3f) * dist;

            // 绘制小星星
            sprite->fillCircle(sparkleX, sparkleY, 2, BeautifulColorConfig::SPARKLE_COLOR);
        }
    }
}

void BeautifulEyeRenderer::drawEyeliner(float upperY, float lowerY) {
    // 绘制细致的眼线
    // 上眼线 - 深棕色,从眼头到眼尾逐渐加粗
    for (int x = 35; x < 205; x++) {
        float progress = (x - 35) / 170.0f;
        int thickness = 1 + (int)(progress * 2);  // 1-3像素厚度

        for (int t = 0; t < thickness; t++) {
            sprite->drawPixel(x, upperY + t, BeautifulColorConfig::EYELINER_COLOR);
        }
    }

    // 下眼线 - 更细,只在外侧1/3
    for (int x = 150; x < 205; x++) {
        sprite->drawPixel(x, lowerY - 1, BeautifulColorConfig::EYELINER_COLOR);
    }
}

void BeautifulEyeRenderer::drawEyelashes(float upperY, float lowerY) {
    // 绘制浓密的上睫毛
    for (int i = 0; i < BeautifulEyeConfig::UPPER_LASH_COUNT; i++) {
        float progress = i / (float)(BeautifulEyeConfig::UPPER_LASH_COUNT - 1);
        int x = 30 + i * 180 / (BeautifulEyeConfig::UPPER_LASH_COUNT - 1);

        // 中间的睫毛更长
        float lengthFactor = 1.0f - abs(progress - 0.5f) * 2.0f;
        int len = BeautifulEyeConfig::LASH_MIN_LENGTH +
                  (int)(lengthFactor * (BeautifulEyeConfig::LASH_MAX_LENGTH -
                                       BeautifulEyeConfig::LASH_MIN_LENGTH));

        // 睫毛有轻微弧度
        int curve = (int)(progress * 6 - 3);

        // 绘制睫毛(多条线增加浓密感)
        sprite->drawLine(x, upperY, x + curve, upperY - len,
                        BeautifulColorConfig::EYELASH_COLOR);
        sprite->drawLine(x + 1, upperY, x + curve + 1, upperY - len,
                        BeautifulColorConfig::EYELASH_COLOR);
    }

    // 绘制下睫毛(更短更稀疏)
    for (int i = 0; i < BeautifulEyeConfig::LOWER_LASH_COUNT; i++) {
        float progress = i / (float)(BeautifulEyeConfig::LOWER_LASH_COUNT - 1);
        int x = 50 + i * 140 / (BeautifulEyeConfig::LOWER_LASH_COUNT - 1);

        int len = BeautifulEyeConfig::LASH_MIN_LENGTH * 0.6f + random(0, 4);
        int curve = (int)(progress * 4 - 2);

        sprite->drawLine(x, lowerY, x + curve, lowerY + len,
                        BeautifulColorConfig::EYELASH_COLOR);
    }
}

void BeautifulEyeRenderer::render(const BeautifulEye& eye) {
    // 清空背景
    sprite->fillSprite(BeautifulColorConfig::BG_COLOR);

    // 计算眨眼时的眼睛可见区域
    float blinkProgress = eye.getBlinkProgress();
    float visibleHeight = 100.0f * (1.0f - blinkProgress);
    float upperY = eye.getEyeY() - visibleHeight;
    float lowerY = eye.getEyeY() + visibleHeight;

    if (visibleHeight > 8) {
        // 绘制眼白
        drawEyeShape(eye, visibleHeight);

        // 绘制虹膜渐变
        drawIrisGradient(eye);

        // 绘制虹膜细节
        drawIrisDetail(eye);

        // 绘制瞳孔
        drawPupil(eye);

        // 绘制高光
        drawReflections(eye);

        // 绘制闪亮效果
        drawSparkles(eye);

        // 绘制眼睑(覆盖上下部分)
        sprite->fillRect(0, 0, HardwareConfig::SCREEN_WIDTH, upperY,
                        BeautifulColorConfig::EYELID_COLOR);
        sprite->fillRect(0, lowerY, HardwareConfig::SCREEN_WIDTH,
                        HardwareConfig::SCREEN_HEIGHT - lowerY,
                        BeautifulColorConfig::EYELID_COLOR);

        // 绘制眼影
        drawEyeShadow(eye, upperY);

        // 绘制眼线
        drawEyeliner(upperY, lowerY);

        // 绘制睫毛
        drawEyelashes(upperY, lowerY);
    } else {
        // 完全闭眼状态
        sprite->fillSprite(BeautifulColorConfig::EYELID_COLOR);

        // 绘制眼睑缝隙
        sprite->fillRect(20, 118, 200, 4, BeautifulColorConfig::EYELINER_COLOR);

        // 绘制闭眼时的睫毛
        for (int i = 0; i < 15; i++) {
            int x = 30 + i * 180 / 15;
            int len = random(8, 12);
            sprite->drawLine(x, 120, x + random(-2, 2), 120 - len,
                           BeautifulColorConfig::EYELASH_COLOR);
        }
    }

    // 推送到屏幕
    sprite->pushSprite(0, 0);
}
