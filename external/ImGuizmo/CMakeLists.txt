cmake_minimum_required(VERSION 3.9)

project(ImGuizmo)
# add_definitions(-DIMGUI_DEFINE_MATH_OPERATORS)

file(GLOB SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
)

add_library(${PROJECT_NAME} OBJECT ${SOURCES})

set_target_properties(
    ${PROJECT_NAME} PROPERTIES
    POSITION_INDEPENDENT_CODE ON
    CXX_STANDARD 17
)

target_include_directories(
    ${PROJECT_NAME} PUBLIC
    "$<TARGET_PROPERTY:ImGui,INTERFACE_INCLUDE_DIRECTORIES>"
)

target_link_libraries(
    ${PROJECT_NAME} PUBLIC
    ImGui
)

