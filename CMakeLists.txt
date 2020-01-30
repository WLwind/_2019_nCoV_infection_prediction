cmake_minimum_required( VERSION 2.8 )
project(_2019_nCoV_infection_prediction)

set( CMAKE_BUILD_TYPE "Release" )
set( CMAKE_CXX_FLAGS "-std=c++11 -O3" )

# add cmake module to find g2o
list( APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake_modules )

# find G2O
find_package( G2O REQUIRED )
include_directories(
    include
    ${G2O_INCLUDE_DIRS}
    "/usr/include/eigen3"
)

add_executable(_2019_nCoV_infection_prediction src/main.cpp )
# link G2O lib
target_link_libraries(_2019_nCoV_infection_prediction 
    g2o_core g2o_stuff
)
