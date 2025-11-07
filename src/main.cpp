#include <Arduino.h>
#include <OneButton.h>
#include "Display.h"
#include "eyes/normal/Eye.h"
#include "eyes/normal/EyeRenderer.h"
#include "eyes/demon/DemonEye.h"
#include "eyes/demon/DemonEyeRenderer.h"
#include "eyes/beautiful/BeautifulEye.h"
#include "eyes/beautiful/BeautifulEyeRenderer.h"
#include "eyes/cyber/CyberEye.h"
#include "eyes/cyber/CyberEyeRenderer.h"
#include "eyes/cosmic/CosmicEye.h"
#include "eyes/cosmic/CosmicEyeRenderer.h"
#include "Config.h"

// 眼睛类型枚举
enum EyeType {
  NORMAL_EYE = 0,
  DEMON_EYE = 1,
  BEAUTIFUL_EYE = 2,
  CYBER_EYE = 3,
  COSMIC_EYE = 4
};

// 全局对象
Display display(HardwareConfig::PIN_DC, HardwareConfig::PIN_CS, HardwareConfig::PIN_RST);
Display display2(HardwareConfig::PIN_DC2, HardwareConfig::PIN_CS2, HardwareConfig::PIN_RST2);
OneButton bootButton(HardwareConfig::PIN_BOOT_BUTTON, true, true);

// 共享的 sprite 用于节省内存 (两个屏幕共用一个sprite)
LGFX_Sprite* sharedSprite = nullptr;

// 当前眼睛类型
EyeType currentEyeType = NORMAL_EYE;

// 普通眼睛对象
Eye normalEye;
EyeRenderer normalRenderer;

// 魅魔眼睛对象
DemonEye demonEye;
DemonEyeRenderer demonRenderer;

// 美丽女生眼睛对象
BeautifulEye beautifulEye;
BeautifulEyeRenderer beautifulRenderer;

// 赛博朋克眼睛对象
CyberEye cyberEye;
CyberEyeRenderer cyberRenderer;

// 星空宇宙眼睛对象
CosmicEye cosmicEye;
CosmicEyeRenderer cosmicRenderer;

// 按钮点击回调函数
void onButtonClick() {
  Serial.println("=== Button Clicked! ===");

  // 循环切换眼睛类型
  if (currentEyeType == NORMAL_EYE) {
    currentEyeType = DEMON_EYE;
    Serial.println("Switched to Demon Eye!");

    // 清空两个屏幕为黑色（魅魔眼睛背景）
    display.fillScreen(0x0000);
    display2.fillScreen(0x0000);

    // 立即渲染一次魅魔眼睛
    demonRenderer.render(demonEye);
  } else if (currentEyeType == DEMON_EYE) {
    currentEyeType = BEAUTIFUL_EYE;
    Serial.println("Switched to Beautiful Eye!");

    // 重新初始化美丽眼睛对象,避免眨眼状态异常
    beautifulEye = BeautifulEye();

    // 清空两个屏幕为白色（美丽眼睛背景）
    display.fillScreen(BeautifulColorConfig::BG_COLOR);
    display2.fillScreen(BeautifulColorConfig::BG_COLOR);

    // 立即渲染一次美丽眼睛
    beautifulRenderer.render(beautifulEye);
  } else if (currentEyeType == BEAUTIFUL_EYE) {
    currentEyeType = CYBER_EYE;
    Serial.println("Switched to Cyber Eye!");

    // 重新初始化赛博眼睛对象
    cyberEye = CyberEye();

    // 清空两个屏幕为黑色（赛博眼睛背景）
    display.fillScreen(CyberColorConfig::BG_COLOR);
    display2.fillScreen(CyberColorConfig::BG_COLOR);

    // 立即渲染一次赛博眼睛
    cyberRenderer.render(cyberEye);
  } else if (currentEyeType == CYBER_EYE) {
    currentEyeType = COSMIC_EYE;
    Serial.println("Switched to Cosmic Eye!");

    // 重新初始化星空眼睛对象
    cosmicEye = CosmicEye();

    // 清空两个屏幕为深色宇宙背景
    display.fillScreen(CosmicColorConfig::BG_COLOR);
    display2.fillScreen(CosmicColorConfig::BG_COLOR);

    // 立即渲染一次星空眼睛
    cosmicRenderer.render(cosmicEye);
  } else {
    currentEyeType = NORMAL_EYE;
    Serial.println("Switched to Normal Eye!");

    // 清空两个屏幕为白色（普通眼睛背景）
    display.fillScreen(ColorConfig::BG_COLOR);
    display2.fillScreen(ColorConfig::BG_COLOR);

    // 立即渲染一次普通眼睛
    normalRenderer.render(normalEye);
  }
}

void setup() {
  Serial.begin(115200);
  delay(500);

  Serial.println("\n=== Beautiful Eye Animation Started! ===");

  // 初始化两个显示屏
  display.begin();
  display2.begin();

  // 创建共享的 sprite (只创建一个,两个屏幕共用以节省内存)
  sharedSprite = new LGFX_Sprite(&display);
  bool created = sharedSprite->createSprite(HardwareConfig::SCREEN_WIDTH, HardwareConfig::SCREEN_HEIGHT);
  sharedSprite->setColorDepth(16);

  Serial.print("Shared sprite created: ");
  Serial.println(created ? "SUCCESS" : "FAILED");
  if (created) {
    Serial.print("Sprite size: ");
    Serial.print(sharedSprite->width());
    Serial.print(" x ");
    Serial.println(sharedSprite->height());
    Serial.print("Memory usage: ");
    Serial.print((HardwareConfig::SCREEN_WIDTH * HardwareConfig::SCREEN_HEIGHT * 2) / 1024);
    Serial.println(" KB (shared by both displays)");
  }

  // 初始化渲染器（使用共享的 sprite）
  normalRenderer.begin(sharedSprite);
  demonRenderer.begin(sharedSprite);
  beautifulRenderer.begin(sharedSprite);
  cyberRenderer.begin(sharedSprite);
  cosmicRenderer.begin(sharedSprite);

  // 配置按钮
  bootButton.attachClick(onButtonClick);
  bootButton.setDebounceMs(50);
  bootButton.setClickMs(400);

  Serial.println("Press BOOT button (GPIO9) to switch eye type.");
  Serial.println("Starting with Normal Eye on both displays.");
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

    // 渲染普通眼睛到屏幕一
    normalRenderer.render(normalEye);

    // 复制内容到屏幕二
    sharedSprite->pushSprite(&display2, 0, 0);

    delay(EyeConfig::FRAME_DELAY);
  } else if (currentEyeType == DEMON_EYE) {
    // 更新魅魔眼球状态
    demonEye.randomMove();
    demonEye.updateMovement();
    demonEye.updateBlink();
    demonEye.updateGlow();

    // 渲染魅魔眼睛到屏幕一
    demonRenderer.render(demonEye);

    // 复制内容到屏幕二
    sharedSprite->pushSprite(&display2, 0, 0);

    delay(DemonEyeConfig::FRAME_DELAY);
  } else if (currentEyeType == BEAUTIFUL_EYE) {
    // 更新美丽女生眼球状态
    beautifulEye.randomMove();
    beautifulEye.updateMovement();
    beautifulEye.updateBlink();
    beautifulEye.updateSparkle();

    // 渲染美丽眼睛到屏幕一
    beautifulRenderer.render(beautifulEye);

    // 复制内容到屏幕二
    sharedSprite->pushSprite(&display2, 0, 0);

    delay(BeautifulEyeConfig::FRAME_DELAY);
  } else if (currentEyeType == CYBER_EYE) {
    // 更新赛博眼球状态
    cyberEye.randomMove();
    cyberEye.updateMovement();
    cyberEye.updateBlink();
    cyberEye.updateScanLine();
    cyberEye.updateHUD();
    cyberEye.updateGlow();
    cyberEye.updateDataStream();

    // 渲染赛博眼睛到屏幕一
    cyberRenderer.render(cyberEye);

    // 复制内容到屏幕二
    sharedSprite->pushSprite(&display2, 0, 0);

    delay(CyberEyeConfig::FRAME_DELAY);
  } else {  // COSMIC_EYE
    // 更新星空眼球状态
    cosmicEye.randomMove();
    cosmicEye.updateMovement();
    cosmicEye.updateBlink();
    cosmicEye.updateNebula();
    cosmicEye.updateGalaxy();
    cosmicEye.updateStars();
    cosmicEye.updateMeteor();
    cosmicEye.updatePulse();

    // 渲染星空眼睛到屏幕一
    cosmicRenderer.render(cosmicEye);

    // 复制内容到屏幕二
    sharedSprite->pushSprite(&display2, 0, 0);

    delay(CosmicEyeConfig::FRAME_DELAY);
  }
}