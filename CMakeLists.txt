# cmake version to be required
cmake_minimum_required( VERSION 3.0.0 )

# project name
project( barebones_listening_server )

# flags
# Tell compiler to use C++ 17 features
set(CMAKE_CXX_STANDARD 17)

# include dirs
include_directories( ./include )

# target
add_executable( server ./src/main.cpp ./src/CQuoteDay.cpp ./src/TcpListener.cpp )