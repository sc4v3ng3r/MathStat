add_subdirectory(Parser)


set(CORE_SOURCES_CPP CoreData.cpp Number.cpp
		     Separatrices.cpp StatClass.cpp)

set(CORE_SOURCES_H CoreData.h Number.h
		   Separatrices.h StatClass.h)

add_library(core SHARED ${CORE_SOURCES_CPP} ${CORE_SOURCES_H})
target_link_libraries(core parser)
