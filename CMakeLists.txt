cmake_minimum_required( VERSION 2.6 )

find_package( OpenCV REQUIRED )
include_directories( "include" )

add_executable( cur_ex src/main.cpp )

target_link_libraries( cur_ex ${OpenCV_LIBS} )
