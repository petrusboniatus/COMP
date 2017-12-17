project(compiler)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        HashMap.c
        HashMap.h
        InputSystem.h
        LexicalAnalyzer.h
        main.c
        InputSystem.c ErrorLog.c ErrorLog.h goDefinitions.h goDefinitions.c resources/PerfectHash.c resources/PerfectHash.h LexicalAnalyzer.c test/IntegrationTest.h)

add_executable(compiler ${SOURCE_FILES})
