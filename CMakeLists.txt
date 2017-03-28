cmake_minimum_required(VERSION 3.6)
project(DataStructuresGroupProjects)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        Program5/BJLp5.c
        Program5/BKBp5.c
        Program5/CMBp5.c
        Program5/cs2123p5.h
        Program5/cs2123p5Driver.c
        Program5/Makefile
        Program5/p5Input.txt
        Program6/p6Input.txt
        GradeSheet.docx
        "Hwk 5.1 TeamAndRoles.docx"
        "Hwk 6.1 GroupProcessEvaluation.docx"
        "Hwk 6.1 PeerEval.docx"
        "Hwk 6.1WhatIdid.docx"
        program5DegreePlan.docx
        README.md
        Schedule.docx)

add_executable(DataStructuresGroupProjects ${SOURCE_FILES})