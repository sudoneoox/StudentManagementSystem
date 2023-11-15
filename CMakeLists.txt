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
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# include directory for header files
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include) 

# include directory for json Data
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/Data)

# Add all your source files 
file(GLOB SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/src/ClassDefinitions/*.cc  
${CMAKE_CURRENT_SOURCE_DIR}/src/FileHandling/*.cc
# ${CMAKE_CURRENT_SOURCE_DIR}/src/MenuFunctions/*.cc
${CMAKE_CURRENT_SOURCE_DIR}/src/main.cc
)

# define the executable target
add_executable(StudentManagementSystem ${SOURCES})
# add_executable(StudentManagementSystem main.cc class.cc assignment.cc people.cc student.cc teacher.cc filemanipulation.cc)


#specify the output directory for the executables (in the bin folder)
set_target_properties(StudentManagementSystem PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin
)

# Link the json library
target_link_libraries(StudentManagementSystem PRIVATE nlohmann_json::nlohmann_json)


