cmake_minimum_required(VERSION 3.9)

project(IDKEditorUI)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/external/imgui-docking/)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/external/ImGuizmo/)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/external/imnodes-0.5)


file(GLOB SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/menubar/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/tabs/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/common/*.cpp
)

add_library(${PROJECT_NAME} SHARED ${SOURCES})

set_target_properties(
    ${PROJECT_NAME} PROPERTIES
    POSITION_INDEPENDENT_CODE ON
    CXX_STANDARD 17
)

target_include_directories(
    ${PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/external/include/
)

target_link_libraries(
    ${PROJECT_NAME} PUBLIC

    libidk
    IDKRenderEngine
    IDKGameEngine

    ImGui
    ImGuizmo
    ImNodes
)

