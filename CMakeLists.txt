cmake_minimum_required(VERSION 3.28)

set( CMAKE_CXX_FLAGS "-std=c++11")

project( orb_cv )
project( readcam )

find_package( OpenCV REQUIRED)

include_directories( ${OpenCV_INCLUDE_DIRS})

add_executable( orb_cv src/orb_cv.cpp)
add_executable( readcam src/readcam.cpp)
add_executable( pos_estimation src/pos_estimation.cpp)
add_executable( triangulation src/triangulation.cpp)
add_executable( undistort src/undistort.cpp)




target_link_libraries( orb_cv ${OpenCV_LIBS})
target_link_libraries( readcam ${OpenCV_LIBS})
target_link_libraries( pos_estimation ${OpenCV_LIBS})
target_link_libraries( triangulation ${OpenCV_LIBS})
target_link_libraries( undistort ${OpenCV_LIBS})
