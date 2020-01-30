cmake_minimum_required( VERSION 2.8 )
project(_2019_nCoV_infection_prediction)

set( CMAKE_BUILD_TYPE "Release" )
set( CMAKE_CXX_FLAGS "-std=c++11 -O3" )

# 添加cmake模块以使用ceres库
list( APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake_modules )

# 寻找Ceres库并添加它的头文件
find_package( Ceres REQUIRED )
include_directories(include ${CERES_INCLUDE_DIRS})

add_executable(_2019_nCoV_infection_prediction main.cpp )
# 与Ceres链接
target_link_libraries(_2019_nCoV_infection_prediction ${CERES_LIBRARIES})
