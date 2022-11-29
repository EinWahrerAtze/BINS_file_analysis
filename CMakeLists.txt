cmake_minimum_required (VERSION 3.8)
set (CMAKE_CXX_STANDARD 20)
project ("BINS_files_analysis_3.0")
add_definitions ( -D_UNICODE )
remove_definitions ( -D_MBCS )
add_executable (BINS_files_analysis_3.0 "main.cpp"
										"interaction.h" "interaction.cpp"
										"file.h" "file.cpp"	    
										"math.cpp" "math.h"
										"menu.h" "menu.cpp")