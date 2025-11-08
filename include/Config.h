#ifndef CONFIG_H
#define CONFIG_H

#include <Arduino.h>

// 硬件引脚配置
namespace HardwareConfig {
    // SPI 配置 (共享)
    constexpr int PIN_SCLK = 2;
    constexpr int PIN_MOSI = 3;
    constexpr int PIN_MISO = -1;

    // 屏幕一引脚
    constexpr int PIN_DC = 10;
    constexpr int PIN_CS = 6;
    constexpr int PIN_RST = 7;

    // 屏幕二引脚
    constexpr int PIN_DC2 = 1;
    constexpr int PIN_CS2 = 0;
    constexpr int PIN_RST2 = 4;

    // 按钮配置
    constexpr int PIN_BOOT_BUTTON = 9;  // ESP32-C3 Boot 按钮引脚

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

// 魅魔眼睛配置
namespace DemonEyeConfig {
    constexpr float EYE_CENTER_X = 120.0f;
    constexpr float EYE_CENTER_Y = 120.0f;
    constexpr float IRIS_SIZE = 55.0f;          // 略大的虹膜
    constexpr float PUPIL_WIDTH = 8.0f;         // 竖瞳宽度
    constexpr float PUPIL_HEIGHT = 35.0f;       // 竖瞳高度
    constexpr float MAX_PUPIL_MOVE = 30.0f;     // 更大的移动范围
    constexpr float PUPIL_SMOOTH = 0.15f;       // 更快速的反应

    // 眨眼参数 - 更慢、更性感的眨眼
    constexpr int BLINK_MIN_INTERVAL = 3000;
    constexpr int BLINK_MAX_INTERVAL = 7000;
    constexpr float BLINK_SPEED = 0.1f;

    // 眼球运动参数 - 更快速、更主动
    constexpr int MOVE_MIN_INTERVAL = 500;
    constexpr int MOVE_MAX_INTERVAL = 2000;
    constexpr int MOVE_RANGE_X = 30;
    constexpr int MOVE_RANGE_Y = 25;

    // 发光效果参数
    constexpr int GLOW_INTENSITY = 15;          // 发光强度
    constexpr float GLOW_PULSE_SPEED = 0.05f;   // 脉动速度

    // 渲染参数
    constexpr int FRAME_DELAY = 50;  // 约20fps
}

// 魅魔眼睛颜色配置
namespace DemonColorConfig {
    constexpr uint16_t SCLERA_COLOR = 0x18E3;    // 深灰色巩膜（不是纯黑）
    constexpr uint16_t IRIS_COLOR = 0xF800;      // 深红色虹膜
    constexpr uint16_t IRIS_OUTER = 0xA000;      // 暗红色外圈
    constexpr uint16_t IRIS_INNER = 0xFC00;      // 亮红色内圈
    constexpr uint16_t IRIS_DETAIL = 0xFD20;     // 橙红色纹理
    constexpr uint16_t PUPIL_COLOR = 0x0000;     // 黑色瞳孔
    constexpr uint16_t GLOW_COLOR = 0xF81F;      // 品红色发光
    constexpr uint16_t EYELID_COLOR = 0x8810;    // 深灰眼睑
    constexpr uint16_t EYELID_SHADOW = 0x4208;   // 暗色阴影
    constexpr uint16_t HIGHLIGHT_HEART = 0xF81F; // 心形高光（品红）
    constexpr uint16_t EYELASH_COLOR = 0x0000;   // 黑色睫毛
}

// 美丽女生眼睛配置
namespace BeautifulEyeConfig {
    constexpr float EYE_CENTER_X = 120.0f;
    constexpr float EYE_CENTER_Y = 120.0f;
    constexpr float IRIS_SIZE = 58.0f;          // 大而有神的虹膜
    constexpr float PUPIL_SIZE = 22.0f;         // 适中的瞳孔
    constexpr float MAX_PUPIL_MOVE = 28.0f;     // 灵动的眼神
    constexpr float PUPIL_SMOOTH = 0.12f;       // 柔和的移动

    // 眨眼参数 - 温柔优雅的眨眼
    constexpr int BLINK_MIN_INTERVAL = 2500;
    constexpr int BLINK_MAX_INTERVAL = 6000;
    constexpr float BLINK_SPEED = 0.12f;

    // 眼球运动参数 - 优雅而自然
    constexpr int MOVE_MIN_INTERVAL = 800;
    constexpr int MOVE_MAX_INTERVAL = 2500;
    constexpr int MOVE_RANGE_X = 28;
    constexpr int MOVE_RANGE_Y = 23;

    // 睫毛参数
    constexpr int UPPER_LASH_COUNT = 18;        // 上睫毛数量
    constexpr int LOWER_LASH_COUNT = 12;        // 下睫毛数量
    constexpr int LASH_MIN_LENGTH = 12;         // 最小睫毛长度
    constexpr int LASH_MAX_LENGTH = 22;         // 最大睫毛长度

    // 渲染参数
    constexpr int FRAME_DELAY = 50;  // 约20fps
}

// 美丽女生眼睛颜色配置
namespace BeautifulColorConfig {
    constexpr uint16_t BG_COLOR = 0xFFFF;        // 白色背景
    constexpr uint16_t SCLERA_COLOR = 0xFFFF;    // 纯净的眼白
    constexpr uint16_t IRIS_COLOR = 0x435C;      // 温柔的棕色虹膜
    constexpr uint16_t IRIS_OUTER = 0x2945;      // 深棕色外圈
    constexpr uint16_t IRIS_MIDDLE = 0x6B8E;     // 中间渐变色
    constexpr uint16_t IRIS_INNER = 0x8D11;      // 金棕色内圈
    constexpr uint16_t IRIS_DETAIL = 0x5ACB;     // 细腻的纹理
    constexpr uint16_t PUPIL_COLOR = 0x0000;     // 黑色瞳孔
    constexpr uint16_t EYELID_COLOR = 0xFDF8;    // 白皙的皮肤
    constexpr uint16_t EYESHADOW_COLOR = 0xF7BE; // 淡粉色眼影
    constexpr uint16_t EYELINER_COLOR = 0x2124;  // 深棕色眼线
    constexpr uint16_t HIGHLIGHT_MAIN = 0xFFFF;  // 主高光(白色)
    constexpr uint16_t HIGHLIGHT_SEC = 0xEF7D;   // 次高光(淡蓝色)
    constexpr uint16_t EYELASH_COLOR = 0x0841;   // 深棕色睫毛
    constexpr uint16_t SPARKLE_COLOR = 0xFFFF;   // 闪亮点(白色)
}

// 赛博朋克机械眼睛配置
namespace CyberEyeConfig {
    constexpr float EYE_CENTER_X = 120.0f;
    constexpr float EYE_CENTER_Y = 120.0f;
    constexpr float IRIS_SIZE = 60.0f;          // 大型机械虹膜
    constexpr float PUPIL_SIZE = 15.0f;         // 小瞳孔(摄像头感)
    constexpr float MAX_PUPIL_MOVE = 30.0f;     // 精确移动
    constexpr float PUPIL_SMOOTH = 0.2f;        // 快速响应

    // 眨眼参数 - 机械快速眨眼
    constexpr int BLINK_MIN_INTERVAL = 3000;
    constexpr int BLINK_MAX_INTERVAL = 8000;
    constexpr float BLINK_SPEED = 0.25f;        // 快速眨眼

    // 眼球运动参数 - 精确移动
    constexpr int MOVE_MIN_INTERVAL = 600;
    constexpr int MOVE_MAX_INTERVAL = 2000;
    constexpr int MOVE_RANGE_X = 30;
    constexpr int MOVE_RANGE_Y = 25;

    // 扫描线参数
    constexpr int SCAN_LINE_SPEED = 3;          // 扫描线移动速度
    constexpr int SCAN_LINE_HEIGHT = 2;         // 扫描线高度

    // HUD 参数
    constexpr int HUD_UPDATE_INTERVAL = 100;    // HUD 更新间隔(ms)
    constexpr int CROSSHAIR_SIZE = 20;          // 准星大小

    // 渲染参数
    constexpr int FRAME_DELAY = 50;  // 约20fps
}

// 赛博朋克机械眼睛颜色配置
namespace CyberColorConfig {
    constexpr uint16_t BG_COLOR = 0x0000;        // 黑色背景
    constexpr uint16_t SCLERA_COLOR = 0x18C3;    // 深蓝灰色巩膜
    constexpr uint16_t IRIS_COLOR = 0x07FF;      // 青色虹膜(Cyan)
    constexpr uint16_t IRIS_OUTER = 0x05DF;      // 深青色外圈
    constexpr uint16_t IRIS_INNER = 0x0FFF;      // 亮青色内圈
    constexpr uint16_t IRIS_RING = 0x07E0;       // 绿色圆环
    constexpr uint16_t PUPIL_COLOR = 0x0000;     // 黑色瞳孔
    constexpr uint16_t SCAN_LINE_COLOR = 0x07FF; // 青色扫描线
    constexpr uint16_t GRID_COLOR = 0x0410;      // 暗青色网格
    constexpr uint16_t HUD_COLOR = 0x07E0;       // 绿色HUD
    constexpr uint16_t HIGHLIGHT_COLOR = 0xFFFF; // 白色高光
    constexpr uint16_t GLOW_COLOR = 0x07FF;      // 青色发光
    constexpr uint16_t TEXT_COLOR = 0x07E0;      // 绿色文字
    constexpr uint16_t CROSSHAIR_COLOR = 0xF800; // 红色准星
}

// 星空宇宙眼睛配置
namespace CosmicEyeConfig {
    constexpr float EYE_CENTER_X = 120.0f;
    constexpr float EYE_CENTER_Y = 120.0f;
    constexpr float IRIS_SIZE = 62.0f;          // 大型星云虹膜
    constexpr float PUPIL_SIZE = 18.0f;         // 星系瞳孔
    constexpr float MAX_PUPIL_MOVE = 25.0f;     // 柔和移动
    constexpr float PUPIL_SMOOTH = 0.08f;       // 非常平滑

    // 眨眼参数 - 神秘缓慢的眨眼
    constexpr int BLINK_MIN_INTERVAL = 3500;
    constexpr int BLINK_MAX_INTERVAL = 7000;
    constexpr float BLINK_SPEED = 0.08f;        // 慢速眨眼

    // 眼球运动参数 - 缓慢优雅
    constexpr int MOVE_MIN_INTERVAL = 1000;
    constexpr int MOVE_MAX_INTERVAL = 3500;
    constexpr int MOVE_RANGE_X = 25;
    constexpr int MOVE_RANGE_Y = 20;

    // 渲染参数
    constexpr int FRAME_DELAY = 50;  // 约20fps
}

// 星空宇宙眼睛颜色配置
namespace CosmicColorConfig {
    constexpr uint16_t BG_COLOR = 0x0008;        // 深宇宙背景(极深蓝)
    constexpr uint16_t SCLERA_COLOR = 0x1084;    // 深紫灰巩膜
    constexpr uint16_t IRIS_EDGE = 0x801F;       // 紫色虹膜边缘
    constexpr uint16_t PUPIL_COLOR = 0x0000;     // 黑色瞳孔
    constexpr uint16_t STAR_COLOR = 0xFFFF;      // 白色星星
    constexpr uint16_t GLOW_COLOR = 0x841F;      // 紫蓝色发光
    constexpr uint16_t EYELID_COLOR = 0x2010;    // 深紫色眼睑
    constexpr uint16_t EYELID_EDGE = 0x4815;     // 紫色眼睑边缘
}

// 显轮眼配置 (Sharingan)
namespace WheelEyeConfig {
    constexpr float EYE_CENTER_X = 120.0f;
    constexpr float EYE_CENTER_Y = 120.0f;
    constexpr float IRIS_SIZE = 65.0f;          // 大型虹膜
    constexpr float PUPIL_SIZE = 18.0f;         // 适中瞳孔
    constexpr float MAX_PUPIL_MOVE = 28.0f;     // 锐利的移动
    constexpr float PUPIL_SMOOTH = 0.15f;       // 快速反应

    // 眨眼参数 - 凌厉快速的眨眼
    constexpr int BLINK_MIN_INTERVAL = 2500;
    constexpr int BLINK_MAX_INTERVAL = 6000;
    constexpr float BLINK_SPEED = 0.2f;         // 快速眨眼

    // 眼球运动参数 - 敏锐警觉
    constexpr int MOVE_MIN_INTERVAL = 700;
    constexpr int MOVE_MAX_INTERVAL = 2200;
    constexpr int MOVE_RANGE_X = 28;
    constexpr int MOVE_RANGE_Y = 24;

    // 勾玉参数
    constexpr int TOMOE_COUNT = 3;              // 勾玉数量(三勾玉)
    constexpr float TOMOE_DISTANCE = 30.0f;     // 勾玉距离中心的距离
    constexpr float TOMOE_SIZE = 12.0f;         // 勾玉大小
    constexpr float ROTATION_SPEED = 0.02f;     // 旋转速度

    // 渲染参数
    constexpr int FRAME_DELAY = 50;  // 约20fps
}

// 显轮眼颜色配置
namespace WheelColorConfig {
    constexpr uint16_t BG_COLOR = 0xFFFF;        // 白色背景
    constexpr uint16_t SCLERA_COLOR = 0xFFFF;    // 纯白巩膜
    constexpr uint16_t IRIS_COLOR = 0xF800;      // 鲜红色虹膜
    constexpr uint16_t IRIS_OUTER = 0xC000;      // 深红外圈
    constexpr uint16_t IRIS_INNER = 0xF980;      // 橙红内圈
    constexpr uint16_t PUPIL_COLOR = 0x0000;     // 黑色瞳孔
    constexpr uint16_t TOMOE_COLOR = 0x0000;     // 黑色勾玉
    constexpr uint16_t WHEEL_LINE_COLOR = 0x0000;// 黑色轮廓线
    constexpr uint16_t EYELID_COLOR = 0xFBE4;    // 皮肤色眼睑
    constexpr uint16_t HIGHLIGHT_COLOR = 0xFFFF; // 白色高光
    constexpr uint16_t GLOW_COLOR = 0xF800;      // 红色发光
}

// 星瞳眼配置 (Anime Star Pupil Eye)
namespace StarEyeConfig {
    constexpr float EYE_CENTER_X = 120.0f;
    constexpr float EYE_CENTER_Y = 120.0f;
    constexpr float IRIS_SIZE = 68.0f;          // 大型可爱虹膜
    constexpr float PUPIL_SIZE = 22.0f;         // 星形瞳孔大小
    constexpr float MAX_PUPIL_MOVE = 26.0f;     // 灵动的移动
    constexpr float PUPIL_SMOOTH = 0.12f;       // 柔和移动

    // 眨眼参数 - 可爱的眨眼
    constexpr int BLINK_MIN_INTERVAL = 2800;
    constexpr int BLINK_MAX_INTERVAL = 6500;
    constexpr float BLINK_SPEED = 0.14f;

    // 眼球运动参数 - 活泼灵动
    constexpr int MOVE_MIN_INTERVAL = 800;
    constexpr int MOVE_MAX_INTERVAL = 2400;
    constexpr int MOVE_RANGE_X = 26;
    constexpr int MOVE_RANGE_Y = 22;

    // 星星参数
    constexpr int STAR_POINTS = 4;              // 四角星
    constexpr float STAR_INNER_RATIO = 0.45f;   // 内外半径比例
    constexpr float SPARKLE_SPEED = 0.06f;      // 闪烁速度
    constexpr int SPARKLE_COUNT = 8;            // 闪烁点数量

    // 渲染参数
    constexpr int FRAME_DELAY = 50;  // 约20fps
}

// 星瞳眼颜色配置
namespace StarColorConfig {
    constexpr uint16_t BG_COLOR = 0xFFFF;        // 白色背景
    constexpr uint16_t SCLERA_COLOR = 0xFFFF;    // 纯白巩膜
    constexpr uint16_t IRIS_OUTER = 0xF81F;      // 粉紫色外圈 (magenta)
    constexpr uint16_t IRIS_MIDDLE = 0xFBDF;     // 亮粉色中圈
    constexpr uint16_t IRIS_INNER = 0xFE9F;      // 粉白色内圈
    constexpr uint16_t PUPIL_COLOR = 0xF81F;     // 粉紫色星形瞳孔
    constexpr uint16_t PUPIL_CORE = 0xFFFF;      // 白色瞳孔核心
    constexpr uint16_t HIGHLIGHT_MAIN = 0xFFFF;  // 白色主高光
    constexpr uint16_t HIGHLIGHT_SEC = 0xFEDF;   // 淡粉色次高光
    constexpr uint16_t SPARKLE_COLOR = 0xFFFF;   // 白色闪烁
    constexpr uint16_t EYELID_COLOR = 0xFDF8;    // 白皙皮肤
    constexpr uint16_t EYELASH_COLOR = 0x4208;   // 深棕色睫毛
    constexpr uint16_t GLOW_COLOR = 0xFBDF;      // 粉色发光
}

#endif // CONFIG_H
