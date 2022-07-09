cmake_minimum_required (VERSION 3.14)
project ("linear_algebra")

enable_testing()

add_subdirectory ("math")
add_subdirectory("tests")
include("cmake/Fetch_GoogleTest.cmake")