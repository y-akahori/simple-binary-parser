# CMakeの最低要求バージョンを指定
cmake_minimum_required(VERSION 3.10)

# プロジェクト名と使用言語を定義
project(PacketParser C)

# C言語の規格をC11に設定
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

# コンパイルオプションを追加
add_compile_options(-Wall -Wextra -g)

# --------------------------------------------------------------------
# 1. パーサー機能をライブラリとして定義
# --------------------------------------------------------------------
add_library(parser_lib STATIC src/parser.c)
target_include_directories(parser_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

# --------------------------------------------------------------------
# 2. メインの実行可能ファイルを定義
# --------------------------------------------------------------------
add_executable(parser src/main.c)
target_link_libraries(parser PRIVATE parser_lib)

# --------------------------------------------------------------------
# 3. テスト機能の有効化とテストプログラムの定義
# --------------------------------------------------------------------
# CTest（CMakeのテスト機能）を有効にする
enable_testing()

# Unityフレームワーク自体をライブラリとして定義
add_library(unity STATIC lib/unity/unity.c)
target_include_directories(unity PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/lib/unity)

# テスト用の実行可能ファイルを定義
add_executable(run_tests tests/test_parser.c)

# テスト実行可能ファイルは、parser_libとunityの両ライブラリに依存
target_link_libraries(run_tests PRIVATE parser_lib unity)

# "ParserTests"という名前のテストを登録し、実行コマンドを'run_tests'に設定
add_test(NAME ParserTests COMMAND run_tests)