cmake_minimum_required(VERSION 3.0.0)
project(unixql VERSION 0.1.0)

# Add antlr/runtime/Cpp/cmake to our cmake path
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/ext/antlr/cmake)

# Set C++ standard. Cpp20 becuz we cool around here
set (CMAKE_CXX_STANDARD 20)

# Set antlr definitions
add_definitions(-DANTLR4CPP_STATIC)
set(ANTLR4_WITH_STATIC_CRT OFF)
set(ANTLR_EXECUTABLE ${CMAKE_CURRENT_SOURCE_DIR}/ext/antlr/bin/antlr-4.9.2-complete.jar)

# Include antlr runtime
include(ExternalAntlr4Cpp)
find_package(ANTLR REQUIRED)

# JSON For C++
add_subdirectory(ext/json)

# Have antlr auto generate our CXX files from antl
antlr_target(UnixqlGrammarParser Unixql.g4 OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/libs/)

# Copy json files into build directory
configure_file(commands.json commands.json COPYONLY)

include(CTest)
enable_testing()

# Add our executable

add_executable(unixql 
    src/main.cpp
    src/unixql_visitor.cpp
    src/executor.cpp
    src/interceptor.cpp
    ${ANTLR_UnixqlGrammarParser_CXX_OUTPUTS}
)

# Add any include directories
target_include_directories(unixql PRIVATE ${ANTLR4_INCLUDE_DIRS})
target_include_directories(unixql PRIVATE include)
target_include_directories(unixql PRIVATE libs)

# Add any libraries we need
target_link_libraries(unixql antlr4_static nlohmann_json::nlohmann_json ${SYSTEM_LIBS})

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
