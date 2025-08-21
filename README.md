# HelloMan 项目

## 项目概述
HelloMan 是一个基于 Qt6 的桌面应用程序项目，使用 C++ 开发。

## 项目结构
```
helloman/
├── CMakeLists.txt          # 根目录构建配置文件
├── src/                    # 源代码目录
│   ├── CMakeLists.txt      # 源代码构建配置
│   ├── main.cpp            # 主程序入口
│   ├── mainwindow.cpp      # 主窗口实现
│   └── mainwindow.h        # 主窗口头文件
└── README.md               # 项目说明文档
```

## 技术栈
- **语言**: C++
- **GUI框架**: Qt6 (6.5+)
- **构建系统**: CMake (3.19+)

## 构建要求
- CMake 3.19 或更高版本
- Qt6 6.5 或更高版本（需要 Core 和 Widgets 组件）
- 支持 C++ 的编译器（GCC、Clang 或 MSVC）

## 构建和运行

### 1. 配置构建环境
确保已安装 Qt6 和 CMake，并且环境变量配置正确。

### 2. 构建项目
```bash
# 创建构建目录
mkdir build
cd build

# 配置项目
cmake ..

# 编译项目
cmake --build .
```

### 3. 运行程序
```bash
# 在构建目录中运行
./helloman
```

## 项目架构说明

### 构建系统架构
- **根 CMakeLists.txt**: 负责项目的总体配置，包括 Qt6 查找和项目设置
- **src/CMakeLists.txt**: 负责源文件的定义、可执行文件的创建和安装配置

### 代码架构
- **main.cpp**: 程序的入口点，初始化 Qt 应用程序并显示主窗口
- **mainwindow.h/cpp**: 主窗口类的声明和实现，包含应用程序的主要用户界面

## 开发指南

### 添加新的源文件
1. 将新的 .cpp 和 .h 文件添加到 `src/` 目录
2. 在 `src/CMakeLists.txt` 中的 `HELLOMAN_SOURCES` 变量中添加新文件
3. 重新构建项目

### 添加新的 Qt 组件
1. 在根目录的 `CMakeLists.txt` 中的 `find_package` 命令中添加所需组件
2. 在 `src/CMakeLists.txt` 中的 `target_link_libraries` 中添加对应的库链接

## 安装和部署
项目配置了标准的 CMake 安装规则，可以通过以下命令进行安装：

```bash
# 在构建目录中
cmake --install . --prefix /path/to/install
```

安装配置位于 `src/CMakeLists.txt` 中，遵循 GNU 安装目录标准。

### DEB 包构建

项目包含完整的 Debian 打包配置，可以构建 DEB 包：

#### 安装构建依赖
```bash
sudo apt-get install build-essential devscripts debhelper cmake qt6-base-dev qt6-base-dev-tools
```

#### 构建 DEB 包
```bash
# 使用提供的构建脚本
./build-deb.sh

# 或手动构建
dpkg-buildpackage -us -uc -b
```

#### 安装 DEB 包
```bash
sudo dpkg -i ../helloman_*.deb
sudo apt-get install -f  # 如果有依赖问题
```

构建成功后，应用程序将出现在系统的应用程序菜单中，并包含自定义图标。

## 许可证
[请根据实际情况添加许可证信息]

## 贡献指南
[请根据实际情况添加贡献指南] 