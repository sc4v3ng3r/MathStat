project(MathStatParser)

set(PARSER_SOURCES_CPP Parser.cpp)

add_library(parser STATIC ${PARSER_SOURCES_CPP})
