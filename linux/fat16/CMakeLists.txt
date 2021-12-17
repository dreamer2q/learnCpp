# CMake 最低版本号要求
cmake_minimum_required (VERSION 2.8)

# 项目信息
project (filesys)

# 指定生成目标
add_executable(filesys filesys.c texor.c main.c)

# add_compile_options(
#   "-Wall" "-Wpedantic" "-Wextra" "-fexceptions"
#   "$<$<CONFIG:DEBUG>:-O0;-g3;-ggdb>"
# )
