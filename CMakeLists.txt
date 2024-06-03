cmake_minimum_required(VERSION 3.15.2)

project(TestLua VERSION 0.0.1)






# INCLUDE  ======================================================
# the project should not directly use chaos' cmake files, this is temporary solution
# include(${PROJECT_ROOT_DIR}/cmake/lib/utils.cmake)


# 设置C++标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)


set(src_files  ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp)
set(others ${CMAKE_CURRENT_SOURCE_DIR}/src/lua_manager.cpp
           ${CMAKE_CURRENT_SOURCE_DIR}/src/lua_manager.h
)

# 添加可执行文件
add_executable(MyProject ${src_files} ${others})

# 添加子目录
# add_subdirectory(external/some_library)

include_directories(MyProject PRIVATE 3rd_parties/luajit/src)
# 链接第三方库
target_link_directories(MyProject PRIVATE 3rd_parties/luajit/src)
target_link_libraries(MyProject PRIVATE lua51)




