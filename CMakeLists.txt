cmake_minimum_required(VERSION 3.21)
project(testkit LANGUAGES C VERSION 1.0)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/examples)

add_library(${PROJECT_NAME}_depend INTERFACE)
target_include_directories(${PROJECT_NAME}_depend INTERFACE ${CMAKE_SOURCE_DIR}/include)

add_subdirectory(${CMAKE_SOURCE_DIR}/src)

install(TARGETS testkit 
        LIBRARY DESTINATION lib)
install(FILES include/testkit.h DESTINATION include)
add_subdirectory(${CMAKE_SOURCE_DIR}/examples)