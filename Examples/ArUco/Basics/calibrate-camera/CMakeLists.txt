cmake_minimum_required(VERSION 2.8)
project( ArucoTest )
find_package( OpenCV REQUIRED PATHS /usr/local/share/OpenCV NO_DEFAULT_PATH)
add_executable( camera_calibration camera_calibration.cpp )
target_link_libraries( camera_calibration ${OpenCV_LIBS} )

