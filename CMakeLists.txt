project(mathstat)
cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

find_package(Qt4 REQUIRED)
include(${QT_USE_FILE})
add_definitions(${QT_DEFINITIONS})
link_directories(${QT_LIBRARY_DIR} )

set(CMAKE_AUTOMOC TRUE)

add_subdirectory(Core)
add_subdirectory(Models)
add_subdirectory(Views)
add_subdirectory(Guis)
add_subdirectory(Graphics)
add_subdirectory(App)