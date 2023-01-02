cmake_minimum_required(VERSION 3.24)
project(Mac_Calculator_GUI C)

set(CMAKE_C_STANDARD 11)

#尋找PkgConfig
FIND_PACKAGE(PkgConfig REQUIRED)
PKG_CHECK_MODULES(GTK3 REQUIRED gtk+-3.0)

#設定函數庫與動態連結庫位置
INCLUDE_DIRECTORIES(${GTK3_INCLUDE_DIRS})
LINK_DIRECTORIES(${GTK3_LIBRARY_DIRS})

add_executable(Mac_Calculator_GUI main.c operation.c calculator.c console_ui.c unit_test_ui.c gtk_ui.c)

#鏈結庫到工程中
target_link_libraries(Mac_Calculator_GUI ${GTK3_LIBRARIES})

set(CMAKE_C_FLAGS_RELEASE -mwindows)