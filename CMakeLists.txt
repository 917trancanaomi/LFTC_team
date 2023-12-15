cmake_minimum_required(VERSION 3.21)
project(LFTC_team)

set(CMAKE_CXX_STANDARD 14)

add_executable(LFTC_team main.cpp
        Grammar.cpp
        Grammar.h
        Production.cpp
        Production.h
        Utils.cpp
        Utils.h
        LR0.cpp
        LR0.h
        CanonicalCollection.cpp
        CanonicalCollection.h
        State.cpp
        ParsingTable.cpp
        Item.cpp
        Item.h
)
