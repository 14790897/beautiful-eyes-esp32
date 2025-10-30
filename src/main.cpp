#include <Arduino.h>
#include "Display.h"
#include "Eye.h"
#include "EyeRenderer.h"
#include "Config.h"

// 全局对象
Display display;
Eye eye;
EyeRenderer renderer;

void setup() {
  Serial.begin(115200);

  // 初始化显示屏
  display.begin();

  // 初始化渲染器
  renderer.begin(&display);

  Serial.println("Beautiful Eye Animation Started!");
  Serial.println("Modular architecture with separate components!");
}

void loop() {
  // 更新眼球状态
  eye.randomMove();
  eye.updateMovement();
  eye.updateBlink();

  // 渲染眼睛
  renderer.render(eye);

  delay(EyeConfig::FRAME_DELAY);
}