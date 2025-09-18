#!/bin/bash

# スクリプトがあるディレクトリを基準に動作するようにする
cd "$(dirname "$0")"

# 1. 古いbuildディレクトリを削除
echo "--- Cleaning up old build directory..."
rm -rf build

# 2. buildディレクトリを再作成して移動
echo "--- Creating new build directory..."
mkdir build
cd build

# 3. ビルドファイルを生成
echo "--- Running CMake..."
cmake ..

# 4. コンパイル
echo "--- Running Make..."
make