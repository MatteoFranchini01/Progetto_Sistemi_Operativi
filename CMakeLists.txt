cmake_minimum_required(VERSION 3.25)
project(Progetto_Sistemi_Operativi)

set(CMAKE_CXX_STANDARD 14)

add_executable(Progetto_Sistemi_Operativi
        main.cpp algoritmi.cpp algoritmi.h selection_sort.cpp selection_sort.h struct.h auxyliary_functions.cpp auxyliary_functions.h)

# Imposta il nome del sistema come Linux
set(CMAKE_SYSTEM_NAME Linux)

# Opzioni di compilazione specifiche per Linux
if(CMAKE_SYSTEM_NAME MATCHES "Linux")
    # Opzioni specifiche per Linux
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
endif()