#ifndef CONFIG_H
#define CONFIG_H

#include <Arduino.h>

// 硬件引脚配置
namespace HardwareConfig {
    // SPI 配置
    constexpr int PIN_SCLK = 2;
    constexpr int PIN_MOSI = 3;
    constexpr int PIN_MISO = -1;
    constexpr int PIN_DC = 10;
    constexpr int PIN_CS = 6;
    constexpr int PIN_RST = 7;

    // SPI 频率
    constexpr int FREQ_WRITE = 80000000;
    constexpr int FREQ_READ = 16000000;

    // 屏幕参数
    constexpr int SCREEN_WIDTH = 240;
    constexpr int SCREEN_HEIGHT = 240;
    constexpr int BRIGHTNESS = 255;
}

// 颜色配置
namespace ColorConfig {
    constexpr uint16_t BG_COLOR = 0xFFFF;        // 白色背景
    constexpr uint16_t SCLERA_COLOR = 0xFFFF;    // 巩膜(眼白)
    constexpr uint16_t IRIS_COLOR = 0x4208;      // 棕色虹膜
    constexpr uint16_t IRIS_OUTER = 0x2945;      // 虹膜外圈
    constexpr uint16_t IRIS_DETAIL = 0x5ACB;     // 虹膜纹理
    constexpr uint16_t PUPIL_COLOR = 0x0000;     // 黑色瞳孔
    constexpr uint16_t EYELID_COLOR = 0xFBE4;    // 皮肤色眼睑
    constexpr uint16_t EYELID_SHADOW = 0x8410;   // 眼睑阴影
    constexpr uint16_t VEIN_COLOR = 0xF7BE;      // 微红色血管
    constexpr uint16_t HIGHLIGHT_MAIN = 0xFFFF;  // 主高光
    constexpr uint16_t HIGHLIGHT_SEC = 0xD69A;   // 次高光
    constexpr uint16_t EYELASH_COLOR = 0x0000;   // 睫毛颜色
}

// 眼睛参数配置
namespace EyeConfig {
    constexpr float EYE_CENTER_X = 120.0f;
    constexpr float EYE_CENTER_Y = 120.0f;
    constexpr float IRIS_SIZE = 50.0f;
    constexpr float PUPIL_SIZE = 20.0f;
    constexpr float MAX_PUPIL_MOVE = 25.0f;
    constexpr float PUPIL_SMOOTH = 0.1f;

    // 眨眼参数
    constexpr int BLINK_MIN_INTERVAL = 2000;
    constexpr int BLINK_MAX_INTERVAL = 5000;
    constexpr float BLINK_SPEED = 0.15f;

    // 眼球运动参数
    constexpr int MOVE_MIN_INTERVAL = 1000;
    constexpr int MOVE_MAX_INTERVAL = 3000;
    constexpr int MOVE_RANGE_X = 25;
    constexpr int MOVE_RANGE_Y = 20;

    // 渲染参数
    constexpr int FRAME_DELAY = 50;  // 约20fps
}

#endif // CONFIG_H
