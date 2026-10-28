cmake_minimum_required(VERSION 3.15)
project(PluginC CXX)

add_library(PluginC SHARED PluginC.cc)

target_include_directories(PluginC PRIVATE ${CMAKE_SOURCE_DIR}/include/)

set_target_properties(PluginC PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/plugins"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/plugins"
)