include_directories(${CMAKE_SOURCE_DIR}/Core)

set(MODEL_SOURCES_CPP SampleSpaceModel.cpp
  StatClassModel.cpp
  StatisticsModel.cpp)

add_library(model STATIC ${MODEL_SOURCES_CPP})

target_link_libraries(model core)