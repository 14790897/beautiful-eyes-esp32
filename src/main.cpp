#include <Arduino.h>
#include <LovyanGFX.hpp>

// GC9A01圆形屏幕配置
class LGFX : public lgfx::LGFX_Device
{
  lgfx::Panel_GC9A01 _panel_instance;
  lgfx::Bus_SPI _bus_instance;

public:
  LGFX(void)
  {
    {
      auto cfg = _bus_instance.config();
      cfg.spi_host = SPI2_HOST;
      cfg.spi_mode = 0;
      cfg.freq_write = 80000000;
      cfg.freq_read = 16000000;
      cfg.spi_3wire = true;
      cfg.use_lock = true;
      cfg.dma_channel = SPI_DMA_CH_AUTO;
      cfg.pin_sclk = 2;  
      cfg.pin_mosi = 3;  
      cfg.pin_miso = -1;
      cfg.pin_dc = 10;    
      _bus_instance.config(cfg);
      _panel_instance.setBus(&_bus_instance);
    }

    {
      auto cfg = _panel_instance.config();
      cfg.pin_cs = 6;     // 根据你的硬件连接修改
      cfg.pin_rst = 7;   // 根据你的硬件连接修改
      cfg.pin_busy = -1;
      cfg.panel_width = 240;
      cfg.panel_height = 240;
      cfg.offset_x = 0;
      cfg.offset_y = 0;
      cfg.offset_rotation = 0;
      cfg.dummy_read_pixel = 8;
      cfg.dummy_read_bits = 1;
      cfg.readable = false;
      cfg.invert = true;
      cfg.rgb_order = false;
      cfg.dlen_16bit = false;
      cfg.bus_shared = false;
      _panel_instance.config(cfg);
    }

    setPanel(&_panel_instance);
  }
};

LGFX lcd;
LGFX_Sprite sprite(&lcd);  // 创建精灵缓冲区用于双缓冲

// 眼睛参数
struct Eye {
  float eyeX, eyeY;           // 眼球中心位置
  float pupilX, pupilY;       // 瞳孔位置
  float irisSize;             // 虹膜大小
  float pupilSize;            // 瞳孔大小
  float blinkProgress;        // 眨眼进度 0-1
  float targetBlinkProgress;
  uint32_t lastBlinkTime;
  uint32_t blinkDuration;

  // 眼睛注视目标
  float targetPupilX, targetPupilY;

  // 上下眼睑位置
  float upperLidY, lowerLidY;
};

Eye eye;

// 颜色定义
const uint16_t BG_COLOR = 0xFFFF;        // 白色背景
const uint16_t SCLERA_COLOR = 0xFFFF;    // 巩膜(眼白)
const uint16_t IRIS_COLOR = 0x4208;      // 棕色虹膜
const uint16_t PUPIL_COLOR = 0x0000;     // 黑色瞳孔
const uint16_t EYELID_COLOR = 0xFBE4;    // 皮肤色眼睑
const uint16_t VEIN_COLOR = 0xF7BE;      // 微红色血管

void initEye() {
  eye.eyeX = 120;
  eye.eyeY = 120;
  eye.pupilX = 120;
  eye.pupilY = 120;
  eye.irisSize = 50;
  eye.pupilSize = 20;
  eye.blinkProgress = 0;
  eye.targetBlinkProgress = 0;
  eye.lastBlinkTime = millis();
  eye.blinkDuration = 150;
  eye.targetPupilX = 120;
  eye.targetPupilY = 120;
  eye.upperLidY = 70;
  eye.lowerLidY = 170;
}

// 绘制眼睛的血管纹理(增加真实感)
void drawVeins() {
  for (int i = 0; i < 5; i++) {
    int startAngle = random(360);
    int startR = eye.irisSize + 10 + random(20);
    int endR = startR + random(30, 60);

    float startX = eye.eyeX + cos(startAngle * DEG_TO_RAD) * startR;
    float startY = eye.eyeY + sin(startAngle * DEG_TO_RAD) * startR;
    float endX = eye.eyeX + cos((startAngle + random(-30, 30)) * DEG_TO_RAD) * endR;
    float endY = eye.eyeY + sin((startAngle + random(-30, 30)) * DEG_TO_RAD) * endR;

    sprite.drawLine(startX, startY, endX, endY, VEIN_COLOR);
  }
}

// 绘制虹膜细节
void drawIrisDetail() {
  // 虹膜外圈较深
  sprite.drawCircle(eye.pupilX, eye.pupilY, eye.irisSize, 0x2945);
  sprite.drawCircle(eye.pupilX, eye.pupilY, eye.irisSize - 1, 0x2945);

  // 虹膜纹理(径向线条)
  for (int i = 0; i < 12; i++) {
    float angle = i * 30 * DEG_TO_RAD;
    int innerR = eye.pupilSize + 5;
    int outerR = eye.irisSize - 3;

    float x1 = eye.pupilX + cos(angle) * innerR;
    float y1 = eye.pupilY + sin(angle) * innerR;
    float x2 = eye.pupilX + cos(angle) * outerR;
    float y2 = eye.pupilY + sin(angle) * outerR;

    sprite.drawLine(x1, y1, x2, y2, 0x5ACB);
  }
}

// 绘制高光反射
void drawReflections() {
  // 主高光
  sprite.fillCircle(eye.pupilX - eye.pupilSize * 0.3,
                 eye.pupilY - eye.pupilSize * 0.3,
                 eye.pupilSize * 0.25, 0xFFFF);

  // 次高光
  sprite.fillCircle(eye.pupilX + eye.pupilSize * 0.4,
                 eye.pupilY + eye.pupilSize * 0.2,
                 eye.pupilSize * 0.15, 0xD69A);
}

// 绘制完整的眼睛
void drawEye() {
  // 在 Sprite 缓冲区中绘制，而不是直接绘制到屏幕
  sprite.fillSprite(EYELID_COLOR);

  // 计算眨眼时的眼睛可见区域
  float visibleHeight = 100 * (1.0 - eye.blinkProgress);
  float upperY = eye.eyeY - visibleHeight;
  float lowerY = eye.eyeY + visibleHeight;

  if (visibleHeight > 5) {
    // 绘制眼白(椭圆形)
    sprite.fillEllipse(eye.eyeX, eye.eyeY, 90, visibleHeight, SCLERA_COLOR);

    // 绘制血管
    if (random(100) < 30) {
      drawVeins();
    }

    // 绘制虹膜
    sprite.fillCircle(eye.pupilX, eye.pupilY, eye.irisSize, IRIS_COLOR);

    // 绘制虹膜细节
    drawIrisDetail();

    // 绘制瞳孔
    sprite.fillCircle(eye.pupilX, eye.pupilY, eye.pupilSize, PUPIL_COLOR);

    // 绘制高光
    drawReflections();

    // 绘制眼睑阴影
    sprite.fillRect(0, 0, 240, upperY, EYELID_COLOR);
    sprite.fillRect(0, lowerY, 240, 240 - lowerY, EYELID_COLOR);

    // 绘制睫毛(简化版)
    for (int i = 0; i < 15; i++) {
      int x = 30 + i * 180 / 15;
      int len = random(8, 15);
      // 上睫毛
      sprite.drawLine(x, upperY, x + random(-3, 3), upperY - len, 0x0000);
      // 下睫毛
      sprite.drawLine(x, lowerY, x + random(-3, 3), lowerY + len - 3, 0x0000);
    }
  } else {
    // 完全闭眼状态 - 绘制眼睑线
    sprite.fillSprite(EYELID_COLOR);
    sprite.fillRect(20, 118, 200, 4, 0x8410);
  }

  // 最后一次性推送到屏幕 - 利用 DMA 快速传输
  sprite.pushSprite(0, 0);
}

// 更新眼球移动
void updateEyeMovement() {
  // 平滑移动瞳孔到目标位置
  eye.pupilX += (eye.targetPupilX - eye.pupilX) * 0.1;
  eye.pupilY += (eye.targetPupilY - eye.pupilY) * 0.1;

  // 限制瞳孔移动范围
  float maxDist = 25;
  float dx = eye.pupilX - eye.eyeX;
  float dy = eye.pupilY - eye.eyeY;
  float dist = sqrt(dx * dx + dy * dy);

  if (dist > maxDist) {
    eye.pupilX = eye.eyeX + (dx / dist) * maxDist;
    eye.pupilY = eye.eyeY + (dy / dist) * maxDist;
  }
}

// 更新眨眼动画
void updateBlink() {
  uint32_t currentTime = millis();

  // 随机触发眨眼
  if (currentTime - eye.lastBlinkTime > random(2000, 5000) && eye.blinkProgress == 0) {
    eye.targetBlinkProgress = 1.0;
  }

  // 眨眼动画
  if (eye.blinkProgress < eye.targetBlinkProgress) {
    eye.blinkProgress += 0.15;
    if (eye.blinkProgress >= 1.0) {
      eye.blinkProgress = 1.0;
      eye.targetBlinkProgress = 0;
    }
  } else if (eye.blinkProgress > eye.targetBlinkProgress) {
    eye.blinkProgress -= 0.15;
    if (eye.blinkProgress <= 0) {
      eye.blinkProgress = 0;
      eye.lastBlinkTime = currentTime;
    }
  }
}

// 随机眼球运动
void randomEyeMovement() {
  static uint32_t lastMoveTime = 0;
  uint32_t currentTime = millis();

  if (currentTime - lastMoveTime > random(1000, 3000)) {
    // 设置新的注视点
    eye.targetPupilX = eye.eyeX + random(-25, 25);
    eye.targetPupilY = eye.eyeY + random(-20, 20);
    lastMoveTime = currentTime;
  }
}

void setup() {
  Serial.begin(115200);

  lcd.init();
  lcd.setRotation(0);
  lcd.setBrightness(255);
  lcd.fillScreen(BG_COLOR);

  // 创建 Sprite 缓冲区 (240x240, 16位色深)
  sprite.createSprite(240, 240);
  sprite.setColorDepth(16);  // 16位色深，适配 DMA 传输

  initEye();

  Serial.println("Beautiful Eye Animation Started!");
  Serial.println("Using Sprite buffer with DMA for smooth rendering!");
}

void loop() {
  // 更新眼球运动
  randomEyeMovement();
  updateEyeMovement();

  // 更新眨眼
  updateBlink();

  // 绘制眼睛
  drawEye();

  delay(50);  // 约20fps
}