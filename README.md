# Beautiful Eyes - 嵌入式眼睛动画项目

[![PlatformIO CI](https://github.com/14790897/beautiful-eyes/actions/workflows/build.yml/badge.svg)](https://github.com/14790897/beautiful-eyes/actions/workflows/build.yml)
[![Release](https://img.shields.io/github/v/release/14790897/beautiful-eyes)](https://github.com/14790897/beautiful-eyes/releases)
[![License](https://img.shields.io/badge/license-MIT-blue.svg)](LICENSE)

一个运行在 ESP32-C3 上的眼睛动画项目，支持多种风格的眼睛效果。双屏同步显示，营造立体生动的眼睛效果。

## ✨ 特性

### 七种眼睛风格

#### 1. 普通眼睛 (Normal Eye)
- 白色眼白，棕色虹膜
- 自然的眨眼动画
- 简单的睫毛和血管纹理
- 标准的眼球移动

#### 2. 恶魔眼睛 (Demon Eye)
- 深灰色巩膜，红色虹膜
- **竖瞳设计** - 猫科动物般的竖直瞳孔
- **发光效果** - 脉动的发光光晕
- **心形高光** - 独特的反光效果
- 更快速、更主动的眼神移动

#### 3. 美丽女生眼睛 (Beautiful Eye)
- 纯净的眼白
- **多层虹膜渐变** - 温柔的棕色渐变
- **淡粉色眼影** - 精致的眼妆效果
- **深棕色眼线** - 从眼头到眼尾的渐变眼线
- **浓密睫毛** - 18根上睫毛 + 12根下睫毛
- **三重高光** - 主高光、淡蓝色次高光、下方小高光
- **闪亮动画** - 虹膜上的动态闪光点
- 温柔优雅的眨眼动画

#### 4. 赛博朋克眼睛 (Cyber Eye) 🆕
- 深蓝灰色巩膜，青色虹膜
- **HUD显示** - 科幻感十足的抬头显示界面
- **扫描线** - 动态扫描线效果
- **网格纹理** - 机械感的虹膜网格
- **数据流动画** - 随机数据流显示
- **准星瞄准** - 红色瞄准准星
- 快速精确的机械眼球移动

#### 5. 星空宇宙眼睛 (Cosmic Eye) 🆕
- 深紫灰巩膜，神秘宇宙色
- **星云渐变** - 多层星云色彩渐变
- **星系旋转** - 虹膜内的星系螺旋效果
- **闪烁星星** - 随机分布的闪烁星点
- **流星划过** - 偶尔出现的流星效果
- **脉冲发光** - 神秘的发光脉动
- 缓慢优雅的眼球移动

#### 6. 显轮眼 (Sharingan - Wheel Eye) 🆕
- 纯白巩膜，鲜红色虹膜
- **三勾玉设计** - 经典的三勾玉图案
- **勾玉旋转** - 持续旋转的勾玉动画
- **红色发光** - 强烈的红色光晕效果
- **黑色轮廓** - 清晰的图案轮廓线
- 凌厉快速的眼神移动

#### 7. 星瞳眼 (Anime Star Pupil Eye) 🆕
- 纯白巩膜，粉紫色虹膜
- **五角星瞳孔** - 可爱的星形瞳孔设计
- **多层渐变** - 粉色系多层虹膜渐变
- **闪烁效果** - 虹膜周围的闪烁星光
- **粉色发光** - 梦幻的粉色光晕
- **星星旋转** - 瞳孔星星的缓慢旋转
- 活泼灵动的眼球移动

### 真实动画效果
- 自然的眨眼动画
- 灵动的眼球移动
- 精致的虹膜渐变
- 多重高光效果
- 双屏同步显示
- **共享 Sprite** - 单个图像缓冲区双屏复用，节省内存

### 简单交互
- **单击** BOOT 按钮 (GPIO9) - 向下翻页(下一个眼睛类型)
- **双击** BOOT 按钮 (GPIO9) - 向上翻页(上一个眼睛类型)
- 即按即切，无需重启
- 可配置的按钮响应参数

## 🔧 硬件要求

- **开发板**: ESP32-C3 (推荐: AirM2M Core ESP32-C3)
- **显示屏**: 2块 ST7789 240x240 LCD (双屏同步显示)
- **数据线**: USB Type-C

### 引脚连接

#### 共享 SPI 引脚
| SPI 引脚 | ESP32-C3 GPIO |
|---------|---------------|
| SCLK    | 2             |
| MOSI    | 3             |

#### 屏幕一引脚
| LCD 引脚 | ESP32-C3 GPIO |
|---------|---------------|
| DC      | 10            |
| CS      | 6             |
| RST     | 7             |

#### 屏幕二引脚
| LCD 引脚 | ESP32-C3 GPIO |
|---------|---------------|
| DC      | 1             |
| CS      | 0             |
| RST     | 4             |

#### 按钮
| 功能     | ESP32-C3 GPIO |
|---------|---------------|
| BOOT 按钮 | 9           |

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

#### 单击 BOOT 按钮 (GPIO9) - 向下翻页

```
普通眼睛 → 魅魔眼睛 → 美丽女生眼睛 → 赛博朋克眼睛 → 星空宇宙眼睛 → 显轮眼 → 星瞳眼 → (循环)
```

#### 双击 BOOT 按钮 (GPIO9) - 向上翻页

```
普通眼睛 → 星瞳眼 → 显轮眼 → 星空宇宙眼睛 → 赛博朋克眼睛 → 美丽女生眼睛 → 魅魔眼睛 → (循环)
```

串口会输出当前切换的眼睛类型。

### 双击设置说明

如果双击不灵敏，可以在 `src/main.cpp` 中调整以下参数：

```cpp
bootButton.setClickMs(300);   // 单击判定时间(ms) - 越小越快识别
bootButton.setIdleMs(600);    // 双击间隔时间(ms) - 越大越容易触发
```

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
│   │   ├── beautiful/      # 美丽女生眼睛
│   │   ├── cyber/          # 赛博朋克眼睛
│   │   ├── cosmic/         # 星空宇宙眼睛
│   │   ├── wheel/          # 显轮眼
│   │   └── star/           # 星瞳眼
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
- **硬件引脚配置** - 双屏幕的 SPI、DC、CS、RST 引脚
- **颜色配置** - 每种眼睛类型独立的颜色方案
- **动画参数** - 眨眼频率、移动速度、旋转速度等
- **特效参数** - 发光强度、闪烁速度、扫描线速度等
- **睫毛参数** - 数量和长度

编辑 `src/main.cpp` 可修改:
- **按钮响应参数**:
  - `setClickMs()` - 单击判定时间
  - `setIdleMs()` - 双击间隔时间
  - `setDebounceMs()` - 去抖动时间
  - `setPressMs()` - 长按判定时间

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

### 双击不工作或难以触发
- 检查串口输出是否有双击日志
- 调整 `setIdleMs()` 参数 (增大到 800 或 1000ms)
- 调整 `setClickMs()` 参数 (减小到 200 或 250ms)
- 确保两次点击间隔在设定时间内
- 示例代码在 `src/main.cpp` 的 `setup()` 函数中

## 📊 性能指标

- **显示屏数量**: 2块 (双屏同步)
- **眼睛类型**: 7种不同风格
- **共享内存**: 单个 sprite 双屏共用，节省内存
- **帧率**: ~20 FPS
- **眨眼间隔**: 2-8秒 (不同眼睛类型可配置)
- **按钮响应**:
  - 单击判定: 300ms
  - 双击间隔: 600ms
  - 去抖动: 50ms

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
- ✅ 添加双击向上翻页功能
- ✅ 添加星瞳眼效果 - 五角星瞳孔，粉色梦幻
- ✅ 添加显轮眼效果 - 三勾玉旋转，红色发光
- ✅ 添加星空宇宙眼睛效果 - 星云、星系、流星
- ✅ 添加赛博朋克眼睛效果 - HUD、扫描线、准星
- ✅ 添加美丽女生眼睛效果 - 眼线、眼影、浓密睫毛
- ✅ 双屏同步显示，营造立体效果
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
