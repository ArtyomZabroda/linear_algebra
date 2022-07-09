add_library ("linear_algebra" INTERFACE)
set_property(TARGET "linear_algebra" PROPERTY CXX_STANDARD 20)
target_include_directories("linear_algebra" INTERFACE .)
