cmake_minimum_required( VERSION 2.8 )
project(_2019_nCoV_infection_prediction)

set( CMAKE_BUILD_TYPE "Release" )
set( CMAKE_CXX_FLAGS "-std=c++11 -O3" )

# add cmake module to find ceres
list( APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake_modules )

# find Ceres add header file
find_package( Ceres REQUIRED )
find_package(OpenCV REQUIRED)
message(STATUS "Include directories of OpenCV: ${OpenCV_INCLUDE_DIRS}")

include_directories(include ${CERES_INCLUDE_DIRS} ${OpenCV_INCLUDE_DIRS})
aux_source_directory(src DIRS_SRCS)

add_executable(${PROJECT_NAME}
  ${DIRS_SRCS}
)
# link Ceres lib
target_link_libraries(_2019_nCoV_infection_prediction ${CERES_LIBRARIES} ${OpenCV_LIBRARIES})
