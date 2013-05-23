include_directories(${CMAKE_SOURCE_DIR}/Models)

set(VIEWS_SOURCES_CPP SampleSpaceView.cpp StatClassView.cpp
			StatisticsView.cpp)

add_library(views ${VIEWS_SOURCES_CPP})
target_link_libraries(views model)
