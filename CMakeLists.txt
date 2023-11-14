cmake_minimum_required(VERSION 3.14)
project(StudentManagementSystem)

# Include FetchContent for downloading dependencies
include(FetchContent)
FetchContent_Declare(
  json
  GIT_REPOSITORY https://github.com/nlohmann/json.git
  GIT_TAG v3.10.5  # Specify the version you need
)
FetchContent_MakeAvailable(json)



# Specify the C++ standard
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add all your source files
add_executable(StudentManagementSystem main.cc class.cc assignment.cc people.cc student.cc teacher.cc filemanipulation.cc)

# Specify your headers directory
target_include_directories(StudentManagementSystem PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/H)

# Link the json library
target_link_libraries(StudentManagementSystem PRIVATE nlohmann_json::nlohmann_json)

# Set the output directory for the executable after the target is defined
set_target_properties(StudentManagementSystem PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)