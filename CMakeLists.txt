cmake_minimum_required (VERSION 3.8)
set (CMAKE_CXX_STANDARD 17)
project ("BINS_file_analysis")
add_executable (BINS_file_analysis main.cpp
								   Interaction.h Interaction.cpp
								   File.h File.cpp
								   Math.h Math.cpp)