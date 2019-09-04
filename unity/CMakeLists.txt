
# Collects all of the unity source files and assign that
# list to the variable LIBRARY_SOURCE
file(GLOB LIBRARY_SOURCE
        "*.c")

# Compile everything in LIBRARY_SOURCE into a static library
# named 'unity.'  The final library will probably be called
# libunity.a, following the convention for static libraries 
# in the C world.
add_library(${LIB_UNITY} STATIC ${LIBRARY_SOURCE})