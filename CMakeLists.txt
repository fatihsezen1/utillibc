cmake_minimum_required(VERSION 3.5)
project(utillibc VERSION 0.1.0 LANGUAGES C)

# Kaynak dosyaların bulunduğu dizin
set(SOURCES
    src/vector.c
)

# Başlık dosyalarının bulunduğu dizin
set(HEADERS
    src/vector.h
)

include(CTest)
enable_testing()

add_library(utillibc utillibc.c)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
