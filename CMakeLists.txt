cmake_minimum_required(VERSION 3.10)
project(scrs_app)

set(CMAKE_CXX_STANDARD 14)
aux_source_directory(. SOURCE_DIR) # 根目录编译目录
#aux_source_directory(./weixin SOURCE_DIR2) # 小程序编译目录
#aux_source_directory(./clie SOURCE_DIR3) # 客户端编译目录
add_subdirectory(weixin)  #将tool1文件夹加入子目录,这样他就可以去tool1文件夹中查找编译
add_subdirectory(clie)
add_executable(scrs_app ${SOURCE_DIR})
#target_link_directories(scrs_app .)
target_link_libraries(scrs_app pthread)
target_link_libraries(scrs_app tool1lib)
target_link_libraries(scrs_app tool2lib)
SET(CMAKE_BUILD_TYPE "Debug")
SET(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g2 -ggdb")
SET(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -Wall")
