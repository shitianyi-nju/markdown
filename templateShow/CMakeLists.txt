cmake_minimum_required(VERSION 3.24)
project(templateShow)

set(CMAKE_CXX_STANDARD 17)

#add_subdirectory(test/lib)
#add_subdirectory(./test)

# 增加一个子目录准备使用gtest自带的cmakelists.txt去编译gtest
add_subdirectory(test/lib)
# 指定gtest的头文件目录
include_directories(test/lib/googletest/include test/lib/googletest)
# 指定gmock的头文件目录
include_directories(test/lib/googlemock/include test/lib/googlemock)
# 指定自己源代码中的头文件目录
include_directories(include)
# 指定自己的源代码所在的目录，并把所有的源代码文件名用GTEST_DEMO_SRC变量代替
aux_source_directory(src GTEST_DEMO_SRC)
# 指定生成gtest01(可执行程序的名字)的工程(即gtest01.exe)所需要的源文件
add_executable(templateShow test/testTemplateFunc.cpp src/templateFunc.cpp ${GTEST_DEMO_SRC} include/templateClass.h src/templateClass.cpp)
# 指定将gtest gtest_main两个链接库，链接到gtest01工程中
target_link_libraries(templateShow gtest gtest_main gmock gmock_main)
