cmake_minimum_required( VERSION 2.8 )
project(_2019_nCoV_infection_prediction)

set( CMAKE_BUILD_TYPE "Release" )
set( CMAKE_CXX_FLAGS "-std=c++11 -O3" )

# add cmake module to find g2o
list( APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake_modules )

# find G2O
find_package( G2O REQUIRED )
find_package(OpenCV REQUIRED)
message(STATUS "Include directories of OpenCV: ${OpenCV_INCLUDE_DIRS}")

include_directories(
    include
    ${G2O_INCLUDE_DIR}
    ${G2O_INCLUDE_DIR}/..
    "/usr/include/eigen3"
    ${OpenCV_INCLUDE_DIRS}
)
aux_source_directory(src DIRS_SRCS)

add_executable(${PROJECT_NAME}
    ${DIRS_SRCS}
)
# link G2O lib
target_link_libraries(${PROJECT_NAME} 
    g2o_core
    g2o_stuff
    ${OpenCV_LIBRARIES}
)
