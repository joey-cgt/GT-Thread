#!/bin/bash

# 检查 CMake 是否安装
if ! command -v cmake &> /dev/null; then
    echo "错误：未找到 CMake。请先安装 CMake（建议版本 3.10+）。"
    exit 1
fi

# 定义构建目录及子目录（bin: 可执行文件，lib: 静态库）
BUILD_DIR="build"
BIN_DIR="${BUILD_DIR}/bin"
LIB_DIR="${BUILD_DIR}/lib"

# 创建构建目录及子目录（确保目录存在）
mkdir -p "$BUILD_DIR" "$BIN_DIR" "$LIB_DIR" || { 
    echo "错误：无法创建目录 $BUILD_DIR/$BIN_DIR/$LIB_DIR"; exit 1; 
}

# 进入构建目录
cd "$BUILD_DIR" || { echo "错误：无法进入构建目录 $BUILD_DIR"; exit 1; }

# 生成构建文件（使用源码目录的 CMakeLists.txt）
echo "正在生成构建文件..."
cmake .. || { echo "错误：CMake 生成构建文件失败"; exit 1; }

# 编译项目（静态库输出到 lib/，可执行文件输出到 bin/）
echo "正在编译项目..."
cmake --build . --config Release || { echo "错误：项目编译失败"; exit 1; }

echo "构建成功！"
echo "动/静态库路径：${LIB_DIR}"
echo "可执行文件路径：${BIN_DIR}"