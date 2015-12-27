cmake_minimum_required(VERSION 2.8)
project( ArucoTest )
find_package( OpenCV REQUIRED PATHS /usr/local/share/OpenCV NO_DEFAULT_PATH)
add_executable( detect_markers detect_markers.cpp )
target_link_libraries( detect_markers ${OpenCV_LIBS} )

