# CMakeLists.txt

cmake_minimum_required(VERSION 3.10)

# 设置项目名称
project(hello_world)

# 设置CMAKE_PREFIX_PATH变量
set(CMAKE_PREFIX_PATH "F:/git/boost_1_81_0")
# 查找Boost库
find_package(Boost REQUIRED)
# 查找Boost库
find_package(Boost REQUIRED COMPONENTS system)

# 查找boost::numeric::ublas库
#find_package(Boost REQUIRED COMPONENTS numeric_ublas)

# 添加可执行文件
#add_executable(example example.cpp)
add_library(example SHARED example.cpp)


# 添加Boost库的链接库路径
target_link_directories(example PRIVATE ${Boost_LIBRARY_DIRS})

# 添加头文件路径 
# 添加Boost库的头文件路径
target_include_directories(example PRIVATE ${CMAKE_CURRENT_SOURCE_DIR} ${Boost_INCLUDE_DIRS})

# 链接Boost库
target_link_libraries(example PRIVATE ${Boost_LIBRARIES} ${LIBRARIES})



