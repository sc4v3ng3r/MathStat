set(GUIS_SOURCES_CPP FixDialog.cpp ParserGui.cpp)
set(GUIS_SOURCES_H FixDialog.h ParserGui.h)

add_library(guis SHARED ${GUIS_SOURCES_CPP} ${GUIS_SOURCES_H})
target_link_libraries(guis core) 
