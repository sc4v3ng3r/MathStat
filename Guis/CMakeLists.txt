project(MathStatGui)

set(GUIS_SOURCES_CPP FixDialog.cpp ParserGui.cpp)

add_library(guis STATIC ${GUIS_SOURCES_CPP})
add_dependencies(guis core)

target_link_libraries(guis core parser)
