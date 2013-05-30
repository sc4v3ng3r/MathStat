project(MathStatHIstogram)

set(HISTOGRAM_SOURCES_CPP Histogram.cpp)
set(QWTLIBS -lqwt) # only here!

add_library(histogram STATIC ${HISTOGRAM_SOURCES_CPP})

target_link_libraries(histogram ${QWTLIBS})
