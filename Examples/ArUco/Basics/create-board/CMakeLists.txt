cmake_minimum_required(VERSION 2.8)
project( ArucoTest )
find_package( OpenCV REQUIRED PATHS /usr/local/share/OpenCV NO_DEFAULT_PATH)
add_executable( create_board create_board.cpp )
target_link_libraries( create_board ${OpenCV_LIBS} )

