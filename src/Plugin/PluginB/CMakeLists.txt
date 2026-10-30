cmake_minimum_required(VERSION 3.15)
project(PluginB CXX)

add_library(PluginB SHARED PluginB.cc)

target_include_directories(PluginB PRIVATE ${CMAKE_SOURCE_DIR}/include/)

set_target_properties(PluginB PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/plugins"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/plugins"
)