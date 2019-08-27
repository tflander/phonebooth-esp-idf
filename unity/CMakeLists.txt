file(GLOB LIBRARY_SOURCE
        "*.c")

add_library(unity STATIC ${LIBRARY_SOURCE})