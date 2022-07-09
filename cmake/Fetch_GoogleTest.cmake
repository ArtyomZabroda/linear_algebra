include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        58d77fa8070e8cec2dc1ed015d66b454c8d78850 # release-1.12.1
)

FetchContent_MakeAvailable(googletest)

#By default, new Visual Studio projects link the C runtimes dynamically but GoogleTest links them statically.
#This will generate an error that looks something like the following:
# --> gtest.lib(gtest-all.obj) : error LNK2038: mismatch detected for ‘RuntimeLibrary’: value ‘MTd_StaticDebug’ doesn't match value ‘MDd_DynamicDebug’ in main.obj
#GoogleTest already has a CMake option for this: gtest_force_shared_crt
#Enabling this option will make gtest link the runtimes dynamically too, and match the project in which it is included.
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)