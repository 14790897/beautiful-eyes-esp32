# GitHub Actions 快速参考

## 📦 创建的文件

```
.github/workflows/
├── build.yml           # 自动构建工作流
└── release.yml         # 版本发布工作流

docs/
├── CI_CD_GUIDE.md      # 详细的 CI/CD 使用指南
└── FILE_STRUCTURE.md   # 项目文件结构说明

README.md               # 项目主文档(已更新)
.gitignore              # Git 忽略文件(已更新)
```

## 🚀 快速使用

### 1. 自动构建

**触发方式:**
- 推送到 `main` 或 `dev` 分支
- 提交 Pull Request 到 `main`
- 手动触发

**下载构建产物:**
1. 进入仓库的 Actions 页面
2. 选择最新的成功构建
3. 下载 `beautiful-eyes-firmware-xxxxx` 压缩包

### 2. 发布版本

**方法 1: 使用 Git Tag**
```bash
git tag -a v1.0.0 -m "Release version 1.0.0"
git push origin v1.0.0
```

**方法 2: 在 GitHub 网页创建 Release**
1. 进入 Releases 页面
2. 点击 "Draft a new release"
3. 输入版本号并发布

**方法 3: 手动触发工作流**
1. 进入 Actions 页面
2. 选择 "Release Firmware"
3. 点击 "Run workflow"
4. 输入版本号

## 📋 构建产物说明

### 自动构建产物

每次构建会生成以下文件:
- `firmware.bin` - 应用程序固件
- `firmware.elf` - ELF 格式(用于调试)
- `bootloader.bin` - ESP32-C3 引导程序
- `partitions.bin` - 分区表
- `build_info.txt` - 构建信息
- `FLASH_INSTRUCTIONS.txt` - 烧录说明

### Release 产物

发布版本会额外包含:
- `VERSION.txt` - 详细版本信息
- `FLASH_GUIDE.md` - 完整烧录指南
- `SHA256SUMS.txt` - 文件校验和
- `beautiful-eyes-vX.X.X.zip` - 完整打包

## 🔍 查看构建状态

### 添加徽章到 README

```markdown
[![PlatformIO CI](https://github.com/YOUR_USERNAME/beautiful-eyes/actions/workflows/build.yml/badge.svg)](https://github.com/YOUR_USERNAME/beautiful-eyes/actions/workflows/build.yml)
```

### 查看构建日志

1. 进入 Actions 页面
2. 选择工作流运行
3. 点击任务查看详细日志

## ⚙️ 自定义配置

### 修改触发分支

编辑 `.github/workflows/build.yml`:
```yaml
on:
  push:
    branches: [ main, dev, feature/* ]  # 添加更多分支
```

### 修改产物保留时间

```yaml
- name: Upload firmware artifacts
  uses: actions/upload-artifact@v4
  with:
    retention-days: 90  # 默认 30 天，改为 90 天
```

### 添加构建通知

在工作流末尾添加:
```yaml
- name: Send notification
  if: always()
  run: |
    # 发送邮件或其他通知
```

## 📝 版本号规范

推荐使用语义化版本:
- `v1.0.0` - 主版本.次版本.修订号
- `v1.0.0-beta` - 测试版本
- `v1.0.0-rc.1` - 候选版本

示例:
```bash
git tag -a v1.0.0 -m "First stable release"
git tag -a v1.1.0 -m "Add beautiful eye feature"
git tag -a v1.1.1 -m "Fix blinking bug"
```

## 🔧 故障排除

### 构建失败

1. 查看错误日志
2. 本地测试编译: `pio run`
3. 检查依赖项版本

### 产物上传失败

- 检查文件路径是否正确
- 验证 GitHub Actions 权限

### Release 创建失败

- 确保版本标签格式正确
- 检查 GITHUB_TOKEN 权限
- 避免重复的版本号

## 📚 相关资源

- [详细 CI/CD 指南](CI_CD_GUIDE.md)
- [项目文件结构](FILE_STRUCTURE.md)
- [GitHub Actions 文档](https://docs.github.com/en/actions)
- [PlatformIO CI/CD](https://docs.platformio.org/en/latest/integration/ci/)

## 💡 最佳实践

1. **经常提交**: 每个功能或修复提交一次
2. **编写测试**: 添加单元测试确保质量
3. **语义化版本**: 遵循版本号规范
4. **编写 Release Notes**: 详细说明每个版本的变化
5. **保持文档更新**: 及时更新 README 和文档

## 🎯 下一步

1. 替换 README.md 中的 `YOUR_USERNAME` 为实际用户名
2. 推送代码到 GitHub
3. 验证 Actions 是否正常运行
4. 创建第一个 Release 测试发布流程
