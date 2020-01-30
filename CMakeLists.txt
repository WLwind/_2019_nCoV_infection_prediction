cmake_minimum_required( VERSION 2.8 )
project(_2019_nCoV_infection_prediction)

set( CMAKE_BUILD_TYPE "Release" )
set( CMAKE_CXX_FLAGS "-std=c++11 -O3" )

# add cmake module to find ceres
list( APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake_modules )

# find Ceres add header file
find_package( Ceres REQUIRED )
include_directories(include ${CERES_INCLUDE_DIRS})

add_executable(_2019_nCoV_infection_prediction main.cpp )
# link Ceres lib
target_link_libraries(_2019_nCoV_infection_prediction ${CERES_LIBRARIES})
