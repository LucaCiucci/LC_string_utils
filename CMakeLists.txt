

cmake_minimum_required(VERSION 3.20)

project(LC_string_utils)

add_library(LC_string_utils)

target_include_directories(LC_string_utils PUBLIC include)
target_sources(
	LC_string_utils
	PRIVATE
		src/common.cpp
)

# C++20
set_target_properties(
	LC_string_utils
	PROPERTIES
		CXX_STANDARD 20
		CXX_STANDARD_REQUIRED ON
		CXX_EXTENSIONS OFF
)
