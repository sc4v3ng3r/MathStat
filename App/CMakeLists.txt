
#include_directories($ENV{QWT_INCLUDE_DIR})

set(SOURCES_CPP main.cpp Sample.cpp MathStat.cpp)
set(SOURCES_H MathStat.h Sample.h )
	      
#QT4_WRAP_CPP(MOC_FILE ${SOURCES_H} OPTIONS -nw)
include_directories(${CMAKE_SOURCE_DIR}/Core)
include_directories(${CMAKE_SOURCE_DIR}/Models)
include_directories(${CMAKE_SOURCE_DIR}/Views)
include_directories(${CMAKE_SOURCE_DIR}/Guis)
include_directories(${CMAKE_SOURCE_DIR}/Graphics)

add_executable(mathstat ${SOURCES_CPP} ${SOURCES_H} )

target_link_libraries(mathstat ${QT_LIBRARIES} core models views guis graphics )
