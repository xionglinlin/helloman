# HelloMan 项目

## 项目简介
HelloMan 是一个简单的 Qt6 桌面应用程序，使用 C++ 开发。该项目主要用于演示 Qt6 应用程序的基本结构，并可作为 Qt6 桌面应用开发的起始模板。

## 技术栈
- **语言**: C++
- **GUI框架**: Qt6 (6.5+)
- **构建系统**: CMake (3.19+)

## 快速构建

### 基本构建
```bash
mkdir build && cd build
cmake ..
cmake --build .
./helloman
```

## DEB 包构建

项目包含完整的 Debian 打包配置，支持构建标准的 DEB 安装包。

### 安装构建依赖
```bash
sudo apt-get install build-essential devscripts debhelper cmake qt6-base-dev qt6-base-dev-tools
```

### 构建 DEB 包
```bash
dpkg-buildpackage -us -uc -b
```

构建成功后会在上级目录生成 `helloman_*.deb` 安装包。

### 安装 DEB 包
```bash
sudo dpkg -i ../helloman_*.deb
sudo apt-get install -f  # 解决可能的依赖问题
```

## Debian 打包文件说明

### 核心配置文件

#### control 文件
`debian/control` 定义了包的基本信息：
- 包名称、版本、维护者信息
- 构建依赖：qt6-base-dev、cmake 等
- 运行时依赖和包描述
- 软件包的架构支持

#### rules 文件
`debian/rules` 是构建脚本，基于 debhelper：
- 定义 CMake 构建参数（Release 模式、安装前缀）
- 自动安装桌面文件到 `/usr/share/applications/`
- 自动安装图标到系统图标目录
- 使用标准的 `dh` 构建系统

#### changelog 文件
`debian/changelog` 记录版本历史：
- 当前版本为 1.0.0
- 包含版本更新记录和发布说明
- 维护者信息和发布时间

#### copyright 文件
`debian/copyright` 声明版权和许可证：
- 使用 GPL-3.0+ 许可证
- 包含完整的版权声明和许可证文本
- 符合 Debian 版权格式标准

### 用户交互配置(debconf)

> **[debconf说明文档见此](./debconf.md)**

#### config 文件
`debian/config` 是 debconf 配置脚本，用于安装时与用户交互：
- 使用 debconf 系统收集用户输入
- 在安装时询问用户姓名信息
- 为后续配置文件生成提供数据

#### templates 文件  
`debian/templates` 定义了 [debconf](./debconf.md) 的问题模板,
- 定义了 `helloman/username` 模板
- 设置问题类型为字符串输入
- 提供用户友好的问题描述

#### helloman.postinst 文件
安装后执行脚本：
- 读取用户在安装时输入的姓名
- 生成个性化配置文件 `/etc/hello_man.conf`
- 完成安装后的初始化工作

### 安装配置文件

#### helloman.install 文件
定义额外的文件安装规则：
- 安装桌面文件到应用程序菜单
- 安装 SVG 图标到系统图标目录

#### source/format 文件
指定源码包格式为 `3.0 (native)`，表示这是一个原生 Debian 包。

### 详细安装流程

#### 1. DEB 包构建阶段
```bash
dpkg-buildpackage -us -uc -b
```
- **依赖检查**：根据 `control` 文件检查构建依赖（cmake、qt6-base-dev 等）
- **源码编译**：`rules` 文件执行以下步骤：
  - 运行 `cmake .. -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=/usr`
  - 编译生成 `helloman` 可执行文件
  - 创建临时安装目录 `debian/helloman/`
- **文件安装**：
  - 主程序安装到 `debian/helloman/usr/bin/helloman`
  - 桌面文件安装到 `debian/helloman/usr/share/applications/helloman.desktop`
  - 图标文件安装到 `debian/helloman/usr/share/icons/hicolor/scalable/apps/helloman.svg`
- **打包生成**：创建 `helloman_1.0.0_amd64.deb` 文件

#### 2. 用户安装 DEB 包阶段
```bash
sudo dpkg -i helloman_1.0.0_amd64.deb
```

**第一步：预安装检查**
- dpkg 解析包信息，检查 `control` 文件中的依赖关系
- 验证系统是否满足运行时依赖要求

**第二步：用户交互配置**
- 执行 `debian/config` 脚本：
  ```bash
  #!/bin/sh
  . /usr/share/debconf/confmodule
  db_input high helloman/username || true
  db_go
  ```
- 根据 `templates` 文件显示问题：
  ```
  Please enter your name:
  This name will be used to generate a config file.
  ```
- 用户输入姓名（例如：张三），debconf 将答案存储在数据库中

**第三步：文件解包和安装**
- 解压 DEB 包内容到系统目录：
  - `/usr/bin/helloman` - 主程序可执行文件
  - `/usr/share/applications/helloman.desktop` - 桌面快捷方式
  - `/usr/share/icons/hicolor/scalable/apps/helloman.svg` - 应用图标
- 更新桌面数据库和图标缓存

**第四步：安装后配置**
- 执行 `debian/helloman.postinst` 脚本：
  ```bash
  #!/bin/sh
  set -e
  . /usr/share/debconf/confmodule
  
  db_get helloman/username    # 获取用户输入的姓名
  USERNAME="$RET"             # 存储到变量中
  
  echo "$USERNAME!" > /etc/hello_man.conf  # 生成配置文件
  ```
- 如果用户输入"张三"，则生成 `/etc/hello_man.conf` 文件，内容为：`张三!`

**第五步：系统集成**
- 更新应用程序菜单，HelloMan 出现在系统应用列表中
- 图标在文件管理器和启动器中正确显示
- 用户可以通过命令行 `helloman` 或点击桌面图标启动应用

#### 3. 安装验证
安装完成后可以验证：
```bash
# 检查程序是否安装
which helloman
# 输出：/usr/bin/helloman

# 检查配置文件是否生成
cat /etc/hello_man.conf
# 输出：张三!

# 检查桌面文件
ls /usr/share/applications/helloman.desktop

# 运行程序
helloman
```

## 许可证
[请根据实际情况添加许可证信息] 