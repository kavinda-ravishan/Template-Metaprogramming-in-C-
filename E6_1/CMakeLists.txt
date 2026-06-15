cmake_minimum_required (VERSION 3.10)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(mpl)

# Include the FetchContent module
include(FetchContent)

# Declare GoogleTest dependency details
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest/
  GIT_TAG        v1.17.0 # Use a stable tag or a specific commit hash
)

# For Windows: Prevent overriding the parent project's compiler settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# Download and make the dependency available
FetchContent_MakeAvailable(googletest)

# Enable testing framework for CMake/CTest
enable_testing()

# Add your main library or executable
add_executable(${PROJECT_NAME} app.cpp)

# Add your test executable
add_executable(${PROJECT_NAME}_test mpl_tests.cpp)

# Use gtest_main to automatically include a main() entry point
target_link_libraries(${PROJECT_NAME}_test PRIVATE gtest_main)

# Discover and add the individual tests automatically
include(GoogleTest)
gtest_discover_tests(${PROJECT_NAME}_test)
