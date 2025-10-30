#include <Arduino.h>
#include <OneButton.h>
#include "Display.h"
#include "Eye.h"
#include "EyeRenderer.h"
#include "DemonEye.h"
#include "DemonEyeRenderer.h"
#include "Config.h"

// 眼睛类型枚举
enum EyeType {
  NORMAL_EYE = 0,
  DEMON_EYE = 1
};

// 全局对象
Display display;
OneButton bootButton(HardwareConfig::PIN_BOOT_BUTTON, true, true);

// 当前眼睛类型
EyeType currentEyeType = NORMAL_EYE;

// 普通眼睛对象
Eye normalEye;
EyeRenderer normalRenderer;

// 魅魔眼睛对象
DemonEye demonEye;
DemonEyeRenderer demonRenderer;

// 按钮点击回调函数
void onButtonClick() {
  Serial.println("=== Button Clicked! ===");

  // 切换眼睛类型
  if (currentEyeType == NORMAL_EYE) {
    currentEyeType = DEMON_EYE;
    Serial.println("Switched to Demon Eye!");

    // 清空屏幕为黑色（魅魔眼睛背景）
    display.fillScreen(0x0000);

    // 立即渲染一次魅魔眼睛
    demonRenderer.render(demonEye);
  } else {
    currentEyeType = NORMAL_EYE;
    Serial.println("Switched to Normal Eye!");

    // 清空屏幕为白色（普通眼睛背景）
    display.fillScreen(ColorConfig::BG_COLOR);

    // 立即渲染一次普通眼睛
    normalRenderer.render(normalEye);
  }
}

void setup() {
  Serial.begin(115200);
  delay(500);

  Serial.println("\n=== Beautiful Eye Animation Started! ===");

  // 初始化显示屏
  display.begin();

  // 初始化渲染器
  normalRenderer.begin(&display);
  demonRenderer.begin(&display);

  // 配置按钮
  bootButton.attachClick(onButtonClick);
  bootButton.setDebounceMs(50);
  bootButton.setClickMs(400);

  Serial.println("Press BOOT button (GPIO9) to switch eye type.");
  Serial.println("Starting with Normal Eye.");
}

void loop() {
  // 检查按钮状态
  bootButton.tick();

  // 根据当前眼睛类型更新和渲染
  if (currentEyeType == NORMAL_EYE) {
    // 更新普通眼球状态
    normalEye.randomMove();
    normalEye.updateMovement();
    normalEye.updateBlink();

    // 渲染普通眼睛
    normalRenderer.render(normalEye);

    delay(EyeConfig::FRAME_DELAY);
  } else {
    // 更新魅魔眼球状态
    demonEye.randomMove();
    demonEye.updateMovement();
    demonEye.updateBlink();
    demonEye.updateGlow();

    // 渲染魅魔眼睛
    demonRenderer.render(demonEye);

    delay(DemonEyeConfig::FRAME_DELAY);
  }
}