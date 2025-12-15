cmake_minimum_required(VERSION 3.10)
project(typing_service)

set(CMAKE_CXX_STANDARD 17)

find_package(PkgConfig REQUIRED)
pkg_check_modules(HTTPLIB REQUIRED cpp-httplib)

add_executable(server backend/server.cpp)

target_include_directories(server PRIVATE ${HTTPLIB_INCLUDE_DIRS})
target_link_libraries(server ${HTTPLIB_LIBRARIES})

target_link_directories(server PRIVATE ${HTTPLIB_LIBRARY_DIRS})
