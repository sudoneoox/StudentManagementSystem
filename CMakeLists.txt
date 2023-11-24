cmake_minimum_required(VERSION 3.14)
project(StudentManagementSystem)

# Include FetchContent for downloading dependencies json library for json manipulation
include(FetchContent)
FetchContent_Declare(
  json
  GIT_REPOSITORY https://github.com/nlohmann/json.git
  GIT_TAG v3.10.5  
)
FetchContent_MakeAvailable(json)



# Specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Find the GCC compiler
find_program(GCC_FOUND gcc)


# Find the G++ compiler
find_program(GPP_FOUND g++)


# If GCC was found, set it as the C compiler
if(GCC_FOUND)
  set(CMAKE_C_COMPILER gcc)
endif()

# If G++ was found, set it as the C++ compiler
if(GPP_FOUND)
  set(CMAKE_CXX_COMPILER g++)
endif()

find_program(CLANG_FOUND clang)

# If Clang was found, set it as the C and C++ compiler
if(CLANG_FOUND)
  set(CMAKE_C_COMPILER clang)
  set(CMAKE_CXX_COMPILER clang++)
endif()


# include directory for header files
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include) 


# include directory for json Data
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/Data)

# all the source files
file(GLOB SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/src/ClassDefinitions/*.cc  
${CMAKE_CURRENT_SOURCE_DIR}/src/FileHandling/*.cc
${CMAKE_CURRENT_SOURCE_DIR}/src/MenuFunctions/*.cc
${CMAKE_CURRENT_SOURCE_DIR}/src/main.cc
)

# define the executable target
add_executable(StudentManagementSystem ${SOURCES})

# output directory path for .exe file /bin
set_target_properties(StudentManagementSystem PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin
)

# link the json library
target_link_libraries(StudentManagementSystem PRIVATE nlohmann_json::nlohmann_json)


