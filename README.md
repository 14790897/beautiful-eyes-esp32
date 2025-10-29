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

```
beautiful-eyes/
├── src/
│   └── main.cpp          # 主程序文件
├── include/              # 头文件目录
├── lib/                  # 本地库目录
├── platformio.ini        # PlatformIO 配置
└── README.md            # 项目说明
```

## 主要组件说明

### 眼睛结构体 (`Eye`)

包含眼球的所有参数：
- 眼球中心位置
- 瞳孔位置和大小
- 虹膜大小
- 眨眼进度
- 眼睑位置

### 渲染函数

- `drawVeins()`: 绘制眼白上的血管纹理
- `drawIrisDetail()`: 绘制虹膜的径向纹理和边缘细节
- `drawReflections()`: 绘制瞳孔上的高光反射
- `drawEye()`: 主渲染函数，整合所有元素

### 动画函数

- `updateEyeMovement()`: 更新瞳孔的平滑移动
- `updateBlink()`: 处理眨眼动画
- `randomEyeMovement()`: 生成随机的眼球运动

## 性能优化

1. **双缓冲技术**: 使用 `LGFX_Sprite` 在内存中完成所有绘制，最后一次性推送到屏幕
2. **DMA 传输**: 利用 SPI DMA 通道进行高速数据传输（80MHz 写入频率）
3. **16位色深**: 平衡色彩质量和传输速度
4. **帧率控制**: 约 20fps 的刷新率，平衡流畅度和性能

## 自定义配置

### 修改颜色

在 `main.cpp` 中可以自定义颜色：

```cpp
const uint16_t BG_COLOR = 0xFFFF;        // 背景色
const uint16_t IRIS_COLOR = 0x4208;      // 虹膜颜色
const uint16_t PUPIL_COLOR = 0x0000;     // 瞳孔颜色
const uint16_t EYELID_COLOR = 0xFBE4;    // 眼睑颜色
```

### 调整眼球参数

在 `initEye()` 函数中修改：

```cpp
eye.irisSize = 50;      // 虹膜大小
eye.pupilSize = 20;     // 瞳孔大小
eye.blinkDuration = 150; // 眨眼持续时间
```

### 修改引脚连接

如果使用不同的引脚连接，请在 `LGFX` 类构造函数中修改：

```cpp
cfg.pin_sclk = 2;   // 时钟引脚
cfg.pin_mosi = 3;   // 数据引脚
cfg.pin_dc = 10;    // 数据/命令引脚
cfg.pin_cs = 6;     // 片选引脚
cfg.pin_rst = 7;    // 复位引脚
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
