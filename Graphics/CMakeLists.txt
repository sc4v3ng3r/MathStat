project(MathStatHistogram)

set(HISTOGRAM_SOURCES_CPP Histogram.cpp)
set(HISTOGRAM_SOURCES_H Histogram.h)
set(QWTLIBS -lqwt)

add_library(histogram STATIC ${HISTOGRAM_SOURCES_CPP})

target_link_libraries(histogram ${QWTLIBS})
