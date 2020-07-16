cmake_minimum_required( VERSION 2.8 )
project(_2019_nCoV_infection_prediction)

set( CMAKE_BUILD_TYPE "Release" )
set( CMAKE_CXX_FLAGS "-std=c++11 -O3" )

find_package(Eigen3 REQUIRED)
message(STATUS "EIGEN3_INCLUDE_DIRS: ${EIGEN3_INCLUDE_DIRS}")
# add cmake module to find g2o
list( APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake_modules )

# find G2O OpenCV
find_package(G2O REQUIRED)
find_package(OpenCV REQUIRED)

set(EXTERNAL_INCLUDE_DIRS ${EIGEN3_INCLUDE_DIRS} ${G2O_INCLUDE_DIR} ${G2O_INCLUDE_DIR}/.. ${OpenCV_INCLUDE_DIRS})
set(EXTERNAL_LIBS ${G2O_LIBRARIES} ${OpenCV_LIBRARIES})

include_directories(
    include
    ${EXTERNAL_INCLUDE_DIRS}
)

aux_source_directory(src DIRS_SRCS)
add_executable(${PROJECT_NAME}
    ${DIRS_SRCS}
)
target_link_libraries(${PROJECT_NAME} 
    ${EXTERNAL_LIBS}
)
