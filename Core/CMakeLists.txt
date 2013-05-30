add_subdirectory(Parser)

set(CORE_SOURCES_CPP CoreData.cpp
  Number.cpp
  Separatrices.cpp
  StatClass.cpp)
  
add_library(core STATIC ${CORE_SOURCES_CPP})
add_dependencies(core parser)
target_link_libraries(core parser)
