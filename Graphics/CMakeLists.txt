
set(HISTOGRAM_SOURCES_CPP Histogram.cpp)
set(HISTOGRAM_SOURCES_H Histogram.h)
set(QWTLIBS "/usr/lib64/libqwt.so.6.0.1") # only here!

add_library(histogram SHARED ${HISTOGRAM_SOURCES_CPP} 
			     ${HISTOGRAM_SOURCES_H})

target_link_libraries(histogram ${QWTLIBS})
