include_directories(${CMAKE_SOURCE_DIR}/Models)

set(VIEWS_SOURCES_CPP SampleSpaceView.cpp StatClassView.cpp
			StatisticsView.cpp)

set(VIEWS_SOURCES_H SampleSpaceView.h StatClassView.h
			StatisticsView.h)

add_library(views ${VIEWS_SOURCES_CPP} ${VIEWS_SOURCES_H})
target_link_libraries(views models) 
