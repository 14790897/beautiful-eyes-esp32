# CI/CD 配置说明

本项目使用 GitHub Actions 自动构建和发布固件。

## 工作流说明

### 1. 构建工作流 (build.yml)

**触发条件:**
- 推送到 `main` 或 `dev` 分支
- 向 `main` 分支提交 Pull Request
- 手动触发 (workflow_dispatch)

**功能:**
- ✅ 自动编译固件
- ✅ 缓存 PlatformIO 和依赖项(加速构建)
- ✅ 生成构建产物 (firmware.bin, bootloader.bin, partitions.bin)
- ✅ 上传构建产物到 Artifacts(保留 30 天)
- ✅ 显示固件大小和内存使用情况
- ✅ 自动生成烧录说明文件

**产物下载:**
1. 进入 Actions 页面
2. 选择最新的成功构建
3. 下载 `beautiful-eyes-firmware-xxxxx` 压缩包

### 2. 发布工作流 (release.yml)

**触发条件:**
- 创建 Release 时自动触发
- 手动触发并指定版本号

**功能:**
- ✅ 构建 Release 版本固件
- ✅ 生成详细的版本信息
- ✅ 创建完整的烧录指南
- ✅ 生成 SHA256 校验和
- ✅ 打包所有文件为 zip
- ✅ 自动上传到 GitHub Release

## 使用方法

### 日常开发构建

每次推送代码到 `main` 或 `dev` 分支时，会自动触发构建。

```bash
git add .
git commit -m "feat: add new feature"
git push origin main
```

构建完成后，可以在 Actions 页面下载最新的固件。

### 手动触发构建

1. 进入 Actions 页面
2. 选择 "PlatformIO CI"
3. 点击 "Run workflow"
4. 选择分支并运行

### 发布新版本

#### 方法 1: 通过 Git Tag (推荐)

```bash
# 创建版本标签
git tag -a v1.0.0 -m "Release version 1.0.0"

# 推送标签
git push origin v1.0.0
```

#### 方法 2: 通过 GitHub Release

1. 进入仓库的 Releases 页面
2. 点击 "Draft a new release"
3. 输入版本号 (如 `v1.0.0`)
4. 填写发布说明
5. 点击 "Publish release"

#### 方法 3: 手动触发发布工作流

1. 进入 Actions 页面
2. 选择 "Release Firmware"
3. 点击 "Run workflow"
4. 输入版本号 (如 `v1.0.0`)
5. 运行工作流

### 下载发布版本

访问 Releases 页面：
```
https://github.com/YOUR_USERNAME/beautiful-eyes/releases
```

每个 Release 包含:
- `firmware.bin` - 应用程序固件
- `bootloader.bin` - ESP32-C3 引导程序
- `partitions.bin` - 分区表
- `firmware.elf` - ELF 格式文件(用于调试)
- `VERSION.txt` - 版本信息
- `FLASH_GUIDE.md` - 详细的烧录指南
- `SHA256SUMS.txt` - 文件校验和
- `beautiful-eyes-vX.X.X.zip` - 完整打包文件

## 构建缓存

为了加速构建，工作流使用了以下缓存:

1. **pip 缓存**: Python 包缓存
2. **PlatformIO 缓存**: 工具链和库缓存

缓存失效条件:
- `platformio.ini` 文件变化
- 超过 7 天未使用

手动清除缓存:
1. 进入 Actions 页面
2. 点击 "Caches"
3. 删除旧的缓存

## 构建状态徽章

在 README.md 中添加构建状态徽章:

```markdown
[![PlatformIO CI](https://github.com/YOUR_USERNAME/beautiful-eyes/actions/workflows/build.yml/badge.svg)](https://github.com/YOUR_USERNAME/beautiful-eyes/actions/workflows/build.yml)
```

## 本地测试 CI 配置

使用 [act](https://github.com/nektos/act) 在本地测试 GitHub Actions:

```bash
# 安装 act
# Windows (使用 Chocolatey)
choco install act-cli

# Linux
curl https://raw.githubusercontent.com/nektos/act/master/install.sh | sudo bash

# 运行构建工作流
act push

# 运行特定工作流
act -W .github/workflows/build.yml
```

## 故障排除

### 构建失败

1. 查看构建日志找到错误信息
2. 常见问题:
   - 依赖项版本冲突
   - PlatformIO 配置错误
   - 代码编译错误

### 产物上传失败

检查:
- 文件路径是否正确
- 文件是否存在
- GitHub Actions 权限设置

### Release 创建失败

确保:
- 版本标签格式正确 (如 `v1.0.0`)
- `GITHUB_TOKEN` 有足够权限
- 不存在同名 Release

## 高级配置

### 自定义构建参数

修改 `.github/workflows/build.yml`:

```yaml
- name: Build firmware
  run: |
    # 自定义构建选项
    pio run --environment prod
    # 或者构建多个环境
    pio run --environment debug
    pio run --environment release
```

### 添加自动化测试

```yaml
- name: Run tests
  run: |
    pio test
```

### 构建多个目标平台

```yaml
strategy:
  matrix:
    board: [airm2m_core_esp32c3, esp32-c3-devkitm-1]
steps:
  - name: Build for ${{ matrix.board }}
    run: pio run --environment ${{ matrix.board }}
```

## 安全注意事项

1. **不要提交敏感信息**:
   - API 密钥
   - 密码
   - 证书

2. **使用 GitHub Secrets** 存储敏感数据:
   - 进入仓库 Settings > Secrets
   - 添加所需的 secrets
   - 在工作流中使用 `${{ secrets.SECRET_NAME }}`

3. **限制工作流权限**:
   ```yaml
   permissions:
     contents: read
     packages: write
   ```

## 资源链接

- [GitHub Actions 文档](https://docs.github.com/en/actions)
- [PlatformIO CI/CD](https://docs.platformio.org/en/latest/integration/ci/index.html)
- [action-gh-release](https://github.com/softprops/action-gh-release)
