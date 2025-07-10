cmake_minimum_required (VERSION 3.22)

project(ssh-picker
  LANGUAGES CXX
  VERSION 1.0.0
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_VISIBILITY_PRESET hidden)

include(FetchContent)

set(FETCHCONTENT_UPDATES_DISCONNECTED ON)
set(FETCHCONTENT_QUIET OFF)

FetchContent_Declare(ftxui
  GIT_REPOSITORY https://github.com/arthursonzogni/ftxui.git
  GIT_TAG        v6.1.9
  GIT_PROGRESS   TRUE
  GIT_SHALLOW    TRUE
  EXCLUDE_FROM_ALL
)
FetchContent_MakeAvailable(ftxui)

# Enable testing and add subdirectories if they exist
if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/tests")
    enable_testing()
    add_subdirectory(tests)
endif()

# Collect all source files
file(GLOB_RECURSE SSH_PICKER_SOURCES
    "ssh-picker/src/*.cpp"
    "ssh-picker/src/*.cc"
)

# Create executable
add_executable(ssh-picker ${SSH_PICKER_SOURCES})

# Set include directories
target_include_directories(ssh-picker
    PRIVATE ssh-picker/include
    PRIVATE ssh-picker/src
)

# Set compiler flags
target_compile_options(ssh-picker PRIVATE
    -Wall
    -Wextra
    -Wpedantic
    -Werror
)

target_link_libraries(ssh-picker
  PRIVATE ftxui::screen
  PRIVATE ftxui::dom
  PRIVATE ftxui::component
)
