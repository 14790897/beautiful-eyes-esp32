# Beautiful Eyes

一个基于 ESP32-C3 和 GC9A01 圆形屏幕的动态眼睛动画项目，通过 LovyanGFX 库实现流畅的眼球运动、眨眼和虹膜细节渲染。支持普通人眼和魅魔眼睛两种风格。

## 功能特性

### 普通眼睛
- **逼真的眼睛渲染**：包含巩膜、虹膜、瞳孔、血管纹理和高光反射
- **流畅的眼球运动**：平滑的瞳孔移动和随机注视行为
- **自然的眨眼动画**：随机触发的眨眼效果，包含眼睑和睫毛
- **细节渲染**：虹膜纹理、血管、高光、睫毛等细节元素

### 魅魔眼睛 (NEW!)
- **竖瞳设计**：猫科动物般的竖直瞳孔
- **发光效果**：脉动的红色/品红发光光晕
- **性感配色**：深红虹膜、黑色巩膜、火焰状纹理
- **心形高光**：独特的心形反光效果
- **浓密睫毛**：更长、更夸张的睫毛渲染
- **快速反应**：更主动、更具侵略性的眼神移动

### 通用特性
- **高性能渲染**：使用 Sprite 双缓冲和 DMA 传输，达到约 20fps
- **模块化架构**：清晰的代码结构，易于扩展和维护
- **灵活配置**：集中式配置管理，轻松切换眼睛类型

## 硬件要求

- **MCU**: ESP32-C3 开发板（合宙 Air M2M Core ESP32-C3）
- **显示屏**: GC9A01 240x240 圆形 TFT 屏幕
- **接口**: SPI 通信

### 引脚连接

| 功能 | ESP32-C3 引脚 |
|------|--------------|
| SCK (时钟) | GPIO 2 |
| MOSI (数据) | GPIO 3 |
| DC (数据/命令) | GPIO 10 |
| CS (片选) | GPIO 6 |
| RST (复位) | GPIO 7 |

## 软件环境

- **开发平台**: PlatformIO
- **框架**: Arduino
- **核心库**: LovyanGFX v1.1.16
- **波特率**: 115200

## 快速开始

### 1. 安装 PlatformIO

如果还未安装 PlatformIO，请参考 [官方文档](https://platformio.org/install)。

### 2. 克隆项目

```bash
git clone <repository-url>
cd beautiful-eyes
```

### 3. 连接硬件

按照上述引脚连接表，将 GC9A01 屏幕连接到 ESP32-C3 开发板。

### 4. 编译并上传

```bash
pio run --target upload
```

### 5. 查看串口输出（可选）

```bash
pio device monitor
```

## 代码结构

项目采用模块化设计，职责分离清晰：

```
beautiful-eyes/
├── include/
│   ├── Config.h            # 配置文件（硬件引脚、颜色、参数）
│   ├── Display.h           # 显示屏配置类
│   ├── Eye.h               # 普通眼睛数据和逻辑类
│   ├── EyeRenderer.h       # 普通眼睛渲染器类
│   ├── DemonEye.h          # 魅魔眼睛数据和逻辑类
│   └── DemonEyeRenderer.h  # 魅魔眼睛渲染器类
├── src/
│   ├── Display.cpp         # 显示屏实现
│   ├── Eye.cpp             # 普通眼睛逻辑实现
│   ├── EyeRenderer.cpp     # 普通眼睛渲染实现
│   ├── DemonEye.cpp        # 魅魔眼睛逻辑实现
│   ├── DemonEyeRenderer.cpp# 魅魔眼睛渲染实现
│   └── main.cpp            # 主程序入口（支持切换）
├── lib/                    # 本地库目录
├── platformio.ini          # PlatformIO 配置
└── README.md              # 项目说明
```

## 架构设计

### 模块职责

#### 1. **Config.h** - 配置管理
集中管理所有配置参数，便于调整：
- `HardwareConfig`: 硬件引脚和 SPI 配置
- `ColorConfig`: 普通眼睛颜色定义
- `EyeConfig`: 普通眼睛参数
- `DemonColorConfig`: 魅魔眼睛颜色定义
- `DemonEyeConfig`: 魅魔眼睛参数（包含发光效果）

#### 2. **Display** - 显示屏抽象层
封装 GC9A01 屏幕的初始化和配置：
- 继承自 `lgfx::LGFX_Device`
- 配置 SPI 总线和面板参数
- 提供简洁的 `begin()` 接口

#### 3. **Eye / DemonEye** - 眼睛数据模型
管理眼睛的状态和行为逻辑：
- **普通眼睛 (Eye)**:
  - 圆形瞳孔
  - 标准眨眼速度
  - 平滑眼球运动

- **魅魔眼睛 (DemonEye)**:
  - 竖直瞳孔（猫眼效果）
  - 更慢、更性感的眨眼
  - 更快速、更主动的移动
  - 脉动发光效果 (`updateGlow()`)

#### 4. **EyeRenderer / DemonEyeRenderer** - 渲染器
负责将眼睛数据绘制到屏幕：
- **普通眼睛渲染器**:
  - 白色巩膜 + 棕色虹膜
  - 圆形瞳孔 + 圆形高光
  - 血管纹理

- **魅魔眼睛渲染器**:
  - 黑色巩膜 + 红色虹膜
  - 竖直瞳孔 + 心形高光
  - 发光光晕效果
  - 火焰状虹膜纹理
  - 更浓密夸张的睫毛

#### 5. **main.cpp** - 主程序
通过宏定义轻松切换眼睛类型：
```cpp
#define EYE_TYPE 0  // 0=普通眼睛, 1=魅魔眼睛
```

## 设计优势

### 解耦与模块化
- **单一职责**: 每个类只负责一个功能域
- **低耦合**: 模块间通过接口通信，易于替换
- **高内聚**: 相关功能集中在同一模块

### 可维护性
- **集中配置**: 所有参数在 `Config.h` 统一管理
- **清晰分层**: 数据（Eye）与表现（Renderer）分离
- **易于调试**: 可独立测试每个模块

### 可扩展性
- **添加新特性**: 如添加双眼只需创建两个 Eye 实例
- **更换显示屏**: 只需修改 Display 类
- **自定义渲染**: 继承 EyeRenderer 实现新风格
- **新眼睛类型**: 按照 DemonEye 的模式轻松添加新类型（如龙眼、外星眼等）

## 使用指南

### 切换眼睛类型

在 `src/main.cpp` 中修改宏定义：

```cpp
#define EYE_TYPE 0  // 0=普通眼睛
#define EYE_TYPE 1  // 1=魅魔眼睛
```

重新编译上传即可切换。

## 性能优化

1. **双缓冲技术**: 使用 `LGFX_Sprite` 在内存中完成所有绘制，最后一次性推送到屏幕
2. **DMA 传输**: 利用 SPI DMA 通道进行高速数据传输（80MHz 写入频率）
3. **16位色深**: 平衡色彩质量和传输速度
4. **帧率控制**: 约 20fps 的刷新率，平衡流畅度和性能

## 自定义配置

得益于模块化设计，所有配置都集中在 `include/Config.h` 文件中。

### 修改颜色

在 `Config.h` 的 `ColorConfig` 命名空间中修改：

```cpp
namespace ColorConfig {
    constexpr uint16_t IRIS_COLOR = 0x4208;      // 虹膜颜色
    constexpr uint16_t PUPIL_COLOR = 0x0000;     // 瞳孔颜色
    constexpr uint16_t EYELID_COLOR = 0xFBE4;    // 眼睑颜色
    // ... 更多颜色配置
}
```

### 调整眼球参数

在 `Config.h` 的 `EyeConfig` 命名空间中修改：

```cpp
namespace EyeConfig {
    constexpr float IRIS_SIZE = 50.0f;           // 虹膜大小
    constexpr float PUPIL_SIZE = 20.0f;          // 瞳孔大小
    constexpr float MAX_PUPIL_MOVE = 25.0f;      // 瞳孔最大移动距离
    constexpr int BLINK_MIN_INTERVAL = 2000;     // 最小眨眼间隔(ms)
    constexpr int BLINK_MAX_INTERVAL = 5000;     // 最大眨眼间隔(ms)
}
```

### 修改引脚连接

在 `Config.h` 的 `HardwareConfig` 命名空间中修改：

```cpp
namespace HardwareConfig {
    constexpr int PIN_SCLK = 2;   // 时钟引脚
    constexpr int PIN_MOSI = 3;   // 数据引脚
    constexpr int PIN_DC = 10;    // 数据/命令引脚
    constexpr int PIN_CS = 6;     // 片选引脚
    constexpr int PIN_RST = 7;    // 复位引脚
}
```

## 故障排除

### 屏幕无显示

1. 检查引脚连接是否正确
2. 确认屏幕供电是否正常（通常为 3.3V）
3. 查看串口输出是否有错误信息

### 显示闪烁

1. 尝试降低 SPI 频率（修改 `cfg.freq_write`）
2. 检查供电是否稳定
3. 确保使用了合适的电源（至少 500mA）

### 编译错误

1. 确保已安装 LovyanGFX 库
2. 检查 PlatformIO 平台是否为最新版本
3. 清理项目后重新编译：`pio run --target clean`
4. 检查头文件包含路径是否正确

## 扩展示例

### 示例 1: 切换到魅魔眼睛

```cpp
// src/main.cpp
#define EYE_TYPE 1  // 切换为魅魔眼睛
```

### 示例 2: 自定义魅魔眼睛颜色（紫色魅魔）

在 `include/Config.h` 中修改：

```cpp
namespace DemonColorConfig {
    constexpr uint16_t IRIS_COLOR = 0x8010;      // 紫色虹膜
    constexpr uint16_t IRIS_OUTER = 0x5008;      // 深紫外圈
    constexpr uint16_t IRIS_INNER = 0xA815;      // 亮紫内圈
    constexpr uint16_t GLOW_COLOR = 0x801F;      // 紫蓝发光
    constexpr uint16_t HIGHLIGHT_HEART = 0xFC1F; // 粉红心形高光
}
```

### 示例 3: 调整魅魔眼睛行为

在 `include/Config.h` 中修改：

```cpp
namespace DemonEyeConfig {
    constexpr float PUPIL_WIDTH = 10.0f;         // 更宽的竖瞳
    constexpr float PUPIL_HEIGHT = 40.0f;        // 更长的竖瞳
    constexpr int GLOW_INTENSITY = 20;           // 更强的发光
    constexpr int BLINK_MIN_INTERVAL = 5000;     // 更少眨眼（更慑人）
}
```

### 示例 4: 创建双眼动画（左右眼不同类型）

```cpp
// 在 main.cpp 中创建混合眼睛
Eye leftEye;                    // 左眼：普通眼睛
DemonEye rightEye;              // 右眼：魅魔眼睛

EyeRenderer leftRenderer;
DemonEyeRenderer rightRenderer;

void setup() {
  // 初始化两个渲染器...
}

void loop() {
  // 分别更新
  leftEye.randomMove();
  leftEye.updateMovement();
  leftEye.updateBlink();

  rightEye.randomMove();
  rightEye.updateMovement();
  rightEye.updateBlink();
  rightEye.updateGlow();

  // 分别渲染
  leftRenderer.render(leftEye);
  rightRenderer.render(rightEye);
}
```

## 参考资料

- [LovyanGFX 库文档](https://github.com/lovyan03/LovyanGFX)
- [GC9A01 数据手册](https://www.buydisplay.com/download/ic/GC9A01A.pdf)
- [ESP32-C3 技术规格](https://www.espressif.com/sites/default/files/documentation/esp32-c3_datasheet_en.pdf)

## 许可证

本项目遵循 MIT 许可证。

## 贡献

欢迎提交 Issue 和 Pull Request！

## 作者

Beautiful Eyes Project

---

**享受你的动态眼睛动画！**
