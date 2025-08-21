cmake_minimum_required(VERSION 3.19)
project(helloman LANGUAGES CXX)

# 查找 Qt6 组件
find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets)

# Qt 标准项目设置
qt_standard_project_setup()

# 安装配置
include(GNUInstallDirs)

# 添加 src 子目录
add_subdirectory(src)
