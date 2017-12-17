cmake_minimum_required(VERSION 3.8)
project(practica03)

set(CMAKE_CXX_STANDARD 11)

add_executable(practica03
        HashMap.c
        HashMap.h
        SymbolTable.c
        SymbolTable.h
        lex.yy.c
        syntax.tab.c
        Logger.c)

target_link_libraries(practica03 m)