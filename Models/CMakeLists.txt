include_directories(${CMAKE_SOURCE_DIR}/Core)
set(MODEL_SOURCES_CPP SampleSpaceModel.cpp StatClassModel.cpp
			StatisticsModel.cpp)

set(MODEL_SOURCES_H SampleSpaceModel.h StatClassModel.h StatisticsModel.h)

add_library(model SHARED ${SOURCES_CPP} ${MODELS_SOURCES_H})

target_link_libraries(model core)
