# Sets esp32 specific variables
set(COMPONENT_SRCS phonebooth.c)
set(COMPONENT_ADD_INCLUDEDIRS ".")

# Tells the esp32 build system to use the contents of this folder
# in the final program that will be written to the esp32 microcontroller.
register_component()
