# 文件结构说明

## 项目结构

```
beautiful-eyes/
├── include/
│   ├── eyes/                    # 眼睛模块
│   │   ├── normal/             # 普通人类眼睛
│   │   │   ├── Eye.h           # 眼睛数据类
│   │   │   └── EyeRenderer.h   # 眼睛渲染器
│   │   ├── demon/              # 魅魔眼睛
│   │   │   ├── DemonEye.h
│   │   │   └── DemonEyeRenderer.h
│   │   └── beautiful/          # 美丽女生眼睛
│   │       ├── BeautifulEye.h
│   │       └── BeautifulEyeRenderer.h
│   ├── Config.h                # 全局配置文件
│   └── Display.h               # 显示屏驱动
│
├── src/
│   ├── eyes/                    # 眼睛模块实现
│   │   ├── normal/
│   │   │   ├── Eye.cpp
│   │   │   └── EyeRenderer.cpp
│   │   ├── demon/
│   │   │   ├── DemonEye.cpp
│   │   │   └── DemonEyeRenderer.cpp
│   │   └── beautiful/
│   │       ├── BeautifulEye.cpp
│   │       └── BeautifulEyeRenderer.cpp
│   ├── Display.cpp
│   └── main.cpp                # 主程序入口
│
└── docs/
    └── FILE_STRUCTURE.md       # 本文档
```

## 模块说明

### 1. 普通眼睛 (normal)
- **路径**: `include/eyes/normal/`, `src/eyes/normal/`
- **功能**: 标准的人类眼睛渲染
- **特点**:
  - 白色眼白
  - 棕色虹膜
  - 标准眨眼动画
  - 简单的睫毛

### 2. 魅魔眼睛 (demon)
- **路径**: `include/eyes/demon/`, `src/eyes/demon/`
- **功能**: 魅魔风格的眼睛
- **特点**:
  - 深灰色巩膜
  - 红色虹膜
  - 竖瞳
  - 发光效果
  - 心形高光

### 3. 美丽女生眼睛 (beautiful)
- **路径**: `include/eyes/beautiful/`, `src/eyes/beautiful/`
- **功能**: 精致的女生眼睛
- **特点**:
  - 纯净的眼白
  - 温柔的棕色虹膜(多层渐变)
  - 淡粉色眼影
  - 深棕色眼线
  - 浓密睫毛(18根上睫毛 + 12根下睫毛)
  - 三重高光效果
  - 闪亮动画

## 配置文件 (Config.h)

配置文件包含所有眼睛类型的参数：

- **HardwareConfig**: 硬件引脚配置
- **ColorConfig**: 普通眼睛颜色配置
- **EyeConfig**: 普通眼睛参数配置
- **DemonEyeConfig**: 魅魔眼睛参数配置
- **DemonColorConfig**: 魅魔眼睛颜色配置
- **BeautifulEyeConfig**: 美丽眼睛参数配置
- **BeautifulColorConfig**: 美丽眼睛颜色配置

## 使用方法

### 添加新的眼睛类型

1. 在 `include/eyes/` 和 `src/eyes/` 下创建新目录
2. 创建眼睛数据类(如 `NewEye.h/cpp`)
3. 创建眼睛渲染器(如 `NewEyeRenderer.h/cpp`)
4. 在 `Config.h` 中添加配置
5. 在 `main.cpp` 中集成新眼睛类型

### Include 路径规范

所有眼睛模块的 include 必须使用完整路径：

```cpp
// 正确
#include "eyes/normal/Eye.h"
#include "eyes/demon/DemonEye.h"
#include "eyes/beautiful/BeautifulEye.h"

// 错误
#include "Eye.h"
#include "DemonEye.h"
```

## 编译

```bash
# 编译
pio run

# 编译并上传
pio run -t upload

# 清理
pio run -t clean
```

## 切换眼睛类型

按下 BOOT 按钮 (GPIO9) 可以循环切换眼睛类型：
- 普通眼睛 → 魅魔眼睛 → 美丽女生眼睛 → (循环)
