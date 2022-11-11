set(srcs "main.c")

set(requires "TFT_eSPI" "graphics" "freetype")

list(APPEND srcs "arduino_main.cpp")
list(APPEND requires "arduino")

idf_component_register(SRCS "${srcs}"
                    INCLUDE_DIRS "."
                    REQUIRES "${requires}")
