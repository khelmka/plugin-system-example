cmake_minimum_required(VERSION 3.15)
project(PluginA CXX)

add_library(PluginA SHARED PluginA.cc)

target_include_directories(PluginA PRIVATE ${CMAKE_SOURCE_DIR}/include/)

set_target_properties(PluginA PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/plugins"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/plugins"
)