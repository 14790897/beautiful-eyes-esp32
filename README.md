# Beautiful Eyes

一个基于 ESP32-C3 和 GC9A01 圆形屏幕的动态眼睛动画项目，通过 LovyanGFX 库实现流畅的眼球运动、眨眼和虹膜细节渲染。

## 功能特性

- **逼真的眼睛渲染**：包含巩膜、虹膜、瞳孔、血管纹理和高光反射
- **流畅的眼球运动**：平滑的瞳孔移动和随机注视行为
- **自然的眨眼动画**：随机触发的眨眼效果，包含眼睑和睫毛
- **高性能渲染**：使用 Sprite 双缓冲和 DMA 传输，达到约 20fps
- **细节渲染**：虹膜纹理、血管、高光、睫毛等细节元素

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
│   ├── Config.h          # 配置文件（硬件引脚、颜色、参数）
│   ├── Display.h         # 显示屏配置类
│   ├── Eye.h             # 眼睛数据和逻辑类
│   └── EyeRenderer.h     # 眼睛渲染器类
├── src/
│   ├── Display.cpp       # 显示屏实现
│   ├── Eye.cpp           # 眼睛逻辑实现
│   ├── EyeRenderer.cpp   # 渲染实现
│   └── main.cpp          # 主程序入口（简洁）
├── lib/                  # 本地库目录
├── platformio.ini        # PlatformIO 配置
└── README.md            # 项目说明
```

## 架构设计

### 模块职责

#### 1. **Config.h** - 配置管理
集中管理所有配置参数，便于调整：
- `HardwareConfig`: 硬件引脚和 SPI 配置
- `ColorConfig`: 颜色定义（虹膜、瞳孔、眼睑等）
- `EyeConfig`: 眼睛参数（大小、运动范围、眨眼间隔）

#### 2. **Display** - 显示屏抽象层
封装 GC9A01 屏幕的初始化和配置：
- 继承自 `lgfx::LGFX_Device`
- 配置 SPI 总线和面板参数
- 提供简洁的 `begin()` 接口

#### 3. **Eye** - 眼睛数据模型
管理眼睛的状态和行为逻辑：
- **数据**: 位置、大小、眨眼进度
- **行为**:
  - `updateMovement()`: 平滑的瞳孔移动
  - `updateBlink()`: 自动眨眼动画
  - `randomMove()`: 随机注视点生成
- **封装**: 私有数据，公开获取器

#### 4. **EyeRenderer** - 渲染器
负责将眼睛数据绘制到屏幕：
- 使用 Sprite 双缓冲技术
- 分层渲染：血管 → 虹膜 → 瞳孔 → 高光 → 眼睑
- 细节方法：
  - `drawVeins()`: 血管纹理
  - `drawIrisDetail()`: 虹膜径向纹理
  - `drawReflections()`: 高光反射
  - `drawEyelashes()`: 睫毛

#### 5. **main.cpp** - 主程序
保持简洁，只负责组装和调度：
```cpp
void loop() {
  eye.randomMove();        // 生成运动目标
  eye.updateMovement();    // 更新位置
  eye.updateBlink();       // 更新眨眼
  renderer.render(eye);    // 渲染到屏幕
}
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

### 创建双眼动画

```cpp
// 在 main.cpp 中创建两个眼睛实例
Eye leftEye, rightEye;
EyeRenderer leftRenderer, rightRenderer;

void setup() {
  // 初始化两个渲染器
  leftRenderer.begin(&display);
  rightRenderer.begin(&display);
}

void loop() {
  // 分别更新和渲染
  leftEye.randomMove();
  leftEye.updateMovement();
  leftEye.updateBlink();

  rightEye.randomMove();
  rightEye.updateMovement();
  rightEye.updateBlink();

  // 渲染到不同区域
  leftRenderer.render(leftEye);
  rightRenderer.render(rightEye);
}
```

### 自定义眼睛颜色

通过修改 `Config.h` 轻松创建不同颜色的眼睛（蓝色、绿色等）：

```cpp
// 蓝色眼睛
namespace ColorConfig {
    constexpr uint16_t IRIS_COLOR = 0x1C9F;      // 蓝色虹膜
    constexpr uint16_t IRIS_DETAIL = 0x3D5F;     // 浅蓝纹理
}

// 绿色眼睛
namespace ColorConfig {
    constexpr uint16_t IRIS_COLOR = 0x2E65;      // 绿色虹膜
    constexpr uint16_t IRIS_DETAIL = 0x4F06;     // 浅绿纹理
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
