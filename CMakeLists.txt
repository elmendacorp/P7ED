cmake_minimum_required(VERSION 3.6)
project(P7ED)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp THashCerrada.h Commit.h Gitcode.cpp Gitcode.h Fichero.h Lista.h fecha.cpp fecha.h vDinamico.h)
add_executable(P7ED ${SOURCE_FILES})