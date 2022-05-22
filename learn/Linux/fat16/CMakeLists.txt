# CMake 最低版本号要求
cmake_minimum_required (VERSION 2.8)

# 项目信息
project (filesys)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# include header
include_directories(include)

# 添加源码目录
aux_source_directory(. SRC_DIR)

aux_source_directory(util SRC_UTIL_DIR)

# 指定生成目标
add_executable(filesys ${SRC_UTIL_DIR} ${SRC_DIR})

# add_compile_options(
#   "-Wall" "-Wpedantic" "-Wextra" "-fexceptions"
#   "$<$<CONFIG:DEBUG>:-O0;-g3;-ggdb>"
# )
