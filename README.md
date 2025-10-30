# Beautiful Eyes - 嵌入式眼睛动画项目

[![PlatformIO CI](https://github.com/YOUR_USERNAME/beautiful-eyes/actions/workflows/build.yml/badge.svg)](https://github.com/YOUR_USERNAME/beautiful-eyes/actions/workflows/build.yml)
[![Release](https://img.shields.io/github/v/release/YOUR_USERNAME/beautiful-eyes)](https://github.com/YOUR_USERNAME/beautiful-eyes/releases)
[![License](https://img.shields.io/badge/license-MIT-blue.svg)](LICENSE)

一个运行在 ESP32-C3 上的眼睛动画项目，支持多种风格的眼睛效果，包括普通眼睛、魅魔眼睛和美丽女生眼睛。

## ✨ 特性

### 三种眼睛风格

#### 1. 普通眼睛 (Normal Eye)
- 白色眼白，棕色虹膜
- 自然的眨眼动画
- 简单的睫毛和血管纹理
- 标准的眼球移动

#### 2. 魅魔眼睛 (Demon Eye)
- 深灰色巩膜，红色虹膜
- **竖瞳设计** - 猫科动物般的竖直瞳孔
- **发光效果** - 脉动的发光光晕
- **心形高光** - 独特的反光效果
- 更快速、更主动的眼神移动

#### 3. 美丽女生眼睛 (Beautiful Eye) 🆕
- 纯净的眼白
- **多层虹膜渐变** - 温柔的棕色渐变
- **淡粉色眼影** - 精致的眼妆效果
- **深棕色眼线** - 从眼头到眼尾的渐变眼线
- **浓密睫毛** - 18根上睫毛 + 12根下睫毛
- **三重高光** - 主高光、淡蓝色次高光、下方小高光
- **闪亮动画** - 虹膜上的动态闪光点
- 温柔优雅的眨眼动画

### 真实动画效果
- 自然的眨眼动画
- 灵动的眼球移动
- 精致的虹膜渐变
- 多重高光效果

### 简单交互
- 按 BOOT 按钮 (GPIO9) 切换眼睛风格
- 即按即切，无需重启

## 🔧 硬件要求

- **开发板**: ESP32-C3 (推荐: AirM2M Core ESP32-C3)
- **显示屏**: ST7789 240x240 LCD
- **数据线**: USB Type-C

### 引脚连接

| LCD 引脚 | ESP32-C3 GPIO |
|---------|---------------|
| SCLK    | 2             |
| MOSI    | 3             |
| DC      | 10            |
| CS      | 6             |
| RST     | 7             |
| BOOT    | 9 (按钮)       |

## 🚀 快速开始

### 方法 1: 下载预编译固件 (推荐)

1. 前往 [Releases](https://github.com/YOUR_USERNAME/beautiful-eyes/releases) 页面
2. 下载最新版本的固件包
3. 解压并按照 `FLASH_GUIDE.md` 说明烧录

**使用 esptool 烧录:**
```bash
pip install esptool

esptool.py --chip esp32c3 --port COM5 --baud 460800 \
  --before default_reset --after hard_reset write_flash \
  0x0 bootloader.bin \
  0x8000 partitions.bin \
  0x10000 firmware.bin
```

### 方法 2: 从源码构建

#### 前置要求
- Python 3.7+
- PlatformIO Core

#### 构建步骤

```bash
# 克隆仓库
git clone https://github.com/YOUR_USERNAME/beautiful-eyes.git
cd beautiful-eyes

# 安装 PlatformIO
pip install platformio

# 编译
pio run

# 编译并上传
pio run -t upload

# 查看串口输出
pio device monitor
```

## 📖 使用说明

### 切换眼睛类型

按下 **BOOT 按钮** (GPIO9) 循环切换:

```
普通眼睛 → 魅魔眼睛 → 美丽女生眼睛 → (循环)
```

串口会输出当前切换的眼睛类型。

## 📁 项目结构

```
beautiful-eyes/
├── .github/
│   └── workflows/          # GitHub Actions CI/CD
│       ├── build.yml       # 自动构建工作流
│       └── release.yml     # 版本发布工作流
├── include/
│   ├── eyes/               # 眼睛模块头文件
│   │   ├── normal/         # 普通眼睛
│   │   ├── demon/          # 魅魔眼睛
│   │   └── beautiful/      # 美丽女生眼睛
│   ├── Config.h            # 全局配置
│   └── Display.h           # 显示驱动
├── src/
│   ├── eyes/               # 眼睛模块实现
│   ├── Display.cpp
│   └── main.cpp
├── docs/
│   ├── FILE_STRUCTURE.md   # 文件结构说明
│   └── CI_CD_GUIDE.md      # CI/CD 指南
└── platformio.ini          # PlatformIO 配置
```

详细说明: [FILE_STRUCTURE.md](docs/FILE_STRUCTURE.md)

## 🔄 CI/CD

本项目使用 GitHub Actions 实现自动化构建和发布:

### 自动构建
- ✅ 推送到 `main` 或 `dev` 分支时自动构建
- ✅ Pull Request 时自动构建验证
- ✅ 构建产物保留 30 天，可在 Actions 页面下载

### 自动发布
- ✅ 创建 Git Tag 自动触发发布流程
- ✅ 自动生成完整的烧录指南
- ✅ 自动打包固件、bootloader、分区表
- ✅ 生成 SHA256 校验和

### 如何发布新版本

```bash
# 创建版本标签
git tag -a v1.0.0 -m "Release version 1.0.0"

# 推送标签触发发布
git push origin v1.0.0
```

详细说明请查看 [CI/CD 指南](docs/CI_CD_GUIDE.md)

## 🛠️ 开发指南

### 添加新的眼睛类型

1. 在 `include/eyes/` 和 `src/eyes/` 创建新目录
2. 创建眼睛数据类 (如 `NewEye.h/cpp`)
3. 创建渲染器 (如 `NewEyeRenderer.h/cpp`)
4. 在 `Config.h` 添加配置参数
5. 在 `main.cpp` 集成新类型

详细步骤: [FILE_STRUCTURE.md](docs/FILE_STRUCTURE.md)

### 自定义配置

编辑 `include/Config.h` 可修改:
- 硬件引脚配置
- 颜色配置
- 动画参数(眨眼频率、移动速度等)
- 睫毛数量和长度

### 代码规范

- 使用完整的 include 路径: `#include "eyes/normal/Eye.h"`
- 每种眼睛类型独立目录
- 配置参数统一放在 `Config.h`

## 🐛 故障排除

### 编译错误
```bash
# 清理构建缓存
pio run -t clean
# 重新构建
pio run
```

### 烧录失败
- 确保设备已连接且驱动已安装
- 尝试按住 BOOT 按钮再烧录
- 降低波特率: `pio run -t upload --upload-speed 115200`

### 屏幕无显示
- 检查引脚连接是否正确
- 验证显示屏电源供应
- 查看串口输出: `pio device monitor`

### 眼睛闭合不动
- 这是旧版本的 bug，已在最新版修复
- 更新到最新固件即可

## 📊 性能指标

- **RAM 使用**: 13 KB / 320 KB (4.0%)
- **Flash 使用**: 385 KB / 1280 KB (29.4%)
- **帧率**: ~20 FPS
- **眨眼间隔**: 2-6秒 (可配置)

## 🤝 贡献

欢迎贡献! 步骤:

1. Fork 本仓库
2. 创建特性分支 (`git checkout -b feature/AmazingFeature`)
3. 提交更改 (`git commit -m 'Add some AmazingFeature'`)
4. 推送到分支 (`git push origin feature/AmazingFeature`)
5. 开启 Pull Request

## 📝 更新日志

查看 [Releases](https://github.com/YOUR_USERNAME/beautiful-eyes/releases) 获取完整更新日志。

### 最新更新
- ✅ 添加美丽女生眼睛效果
- ✅ 重构文件结构，模块化设计
- ✅ 修复眼睛闭合不动的 bug
- ✅ 添加 GitHub Actions CI/CD

## 📄 许可证

本项目采用 MIT 许可证 - 查看 [LICENSE](LICENSE) 了解详情。

## 🙏 致谢

- [LovyanGFX](https://github.com/lovyan03/LovyanGFX) - 强大的图形库
- [OneButton](https://github.com/mathertel/OneButton) - 简单的按钮库
- [PlatformIO](https://platformio.org/) - 优秀的构建系统

## 📧 联系方式

- 提交 Issue: [GitHub Issues](https://github.com/YOUR_USERNAME/beautiful-eyes/issues)
- 邮件: your.email@example.com

---

⭐ 如果这个项目对你有帮助，请给个 Star!
