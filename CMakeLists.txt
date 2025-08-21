cmake_minimum_required(VERSION 3.10)
project(Trb_Grafos CXX)
set(CMAKE_CXX_STANDARD 23)

# Diretórios
set(SRC_DIR ${CMAKE_SOURCE_DIR}/src)
set(BUILD_DIR ${CMAKE_SOURCE_DIR}/build)

# Cria build/ se não existir
file(MAKE_DIRECTORY ${BUILD_DIR})

# Coleta todos os .cpp
file(GLOB ALL_SRC_FILES "${SRC_DIR}/*.cpp")

# Separa main.cpp dos demais
set(NON_MAIN_SRCS "")
foreach(file ${ALL_SRC_FILES})
    if(file MATCHES ".*/main\\.cpp$")
        set(MAIN_SRC ${file})
    else()
        list(APPEND NON_MAIN_SRCS ${file})
    endif()
endforeach()

# Se não encontrou main.cpp, dá erro claro
if(NOT MAIN_SRC)
    message(FATAL_ERROR "main.cpp não encontrado na pasta src/")
endif()

# Biblioteca de objetos com os outros .cpp
add_library(objlib OBJECT ${NON_MAIN_SRCS})

# Executável main, linkando objetos
add_executable(main ${MAIN_SRC} $<TARGET_OBJECTS:objlib>)

# Define saída do executável na pasta src/
set_target_properties(main PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${SRC_DIR}
)
