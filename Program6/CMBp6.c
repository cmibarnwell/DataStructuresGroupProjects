/****************************************************************
 CMBp6.c by Caleb Barnwell

 Purpose:
    Handles multiple types of output printing for the program.
    Also, lays out a plan using doPlan.

 Input:
    Received from cs2123p5Driver.c

 ****************************************************************/

#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include "cs2123p6.h"



/******************** printSuccessors **************************************
void printSuccessors(Graph graph)
Purpose:
    Checks if a course exists and acts as a helper function for printTraversal.

Parameters:
    I   Graph graph      graph
    I   int iVertex      vertex index

**************************************************************************/
void printSuccessors(Graph graph, int iVertex)
{
    // Declarations
    int visitedM[graph->iNumVertices], i;
    EdgeNode * p;

    // See if Course exists
    if(findCourse(graph, graph->vertexM[iVertex].szCourseId) == -1)
    {
        printf("Course %s not found.", graph->vertexM[iVertex].szCourseId);
        return;
    }

    // Initialize our Visited to false
    for(i=0;i<graph->iNumVertices;i++)
        visitedM[i]= FALSE;

    // Use DFT to find all successors
    printTraversal(graph, iVertex, 0);
}

/******************** printTraversal **************************************
void printTraversal(Graph graph, int iCourseVertex, int indent)
Purpose:
    Recursively prints the successors of a given vertex.

Parameters:
    I   Graph graph      graph
    I   int iCourseVertex       Vertex index
    I   int indent          indentation for print statement

**************************************************************************/
void printTraversal(Graph graph, int iCourseVertex, int iIndent)
{
    // Declarations
    int i;
    EdgeNode * p;

    // check if NULL
    if (iCourseVertex == -1)
        return;

    // Print out the course with necessary indentation
    for (i = 0; i < iIndent; i++) {
        printf("\t");
    }
    printf("%s %s\n",graph->vertexM[iCourseVertex].szCourseId, graph->vertexM[iCourseVertex].szCourseName);

    // Move down the graph recursively
    for (p = graph->vertexM[iCourseVertex].successorList; p != NULL; p = p->pNextEdge) {
        printTraversal(graph, p->iSuccVertex, iIndent + 1);
    }
}

/******************** printSources **************************************
void printSources(Graph graph)
Purpose:
    Prints out all courses that have no prerequisite.

Parameters:
    I   Graph graph      graph

**************************************************************************/
void printSources(Graph graph)
{
    // Declarations
    int i;
    int bFindEver = FALSE;

    // Print Header
    printf("All Sources:\n");

    // Loop through graph and find sources
    for(i = 0; i < graph->iNumVertices; i++)
    {
        if(graph->vertexM[i].prereqList->iPrereqVertex == -1) {
            printf("\t%s %s\n", graph->vertexM[i].szCourseId, graph->vertexM[i].szCourseName);
            bFindEver = TRUE;
        }
    }

    // If we never found any, print None
    if(!bFindEver)
        printf("None\n");
}

/******************** printSinks **************************************
void printSinks(Graph graph)
Purpose:
    Prints out all courses that do not act as a prerequisite.

Parameters:
    I   Graph graph      graph

**************************************************************************/
void printSinks(Graph graph)
{
    // Declarations
    int i, j;
    int bFind = FALSE;
    int bFindEver = FALSE;
    EdgeNode * p;

    // Print Header
    printf("All Sinks:\n");

    // Loop through graph and find sinks
    for(i = 0; i < graph->iNumVertices; i++)
    {
        for(j = 0; j < graph->iNumVertices; j++)
        {
            for(p = graph->vertexM[j].prereqList; p != NULL; p = p->pNextEdge){
                if(p->iPrereqVertex == i) {
                    bFind = TRUE;
                    bFindEver = TRUE;
                }
            }
        }
        if(!bFind)
            printf("\t%s %s\n", graph->vertexM[i].szCourseId, graph->vertexM[i].szCourseName);
        bFind = FALSE;
    }

    // If we never found a sink, print None
    if(!bFindEver)
        printf("None\n");
}

/******************** printAllInList **************************************
void printAllInList(Graph graph)
Purpose:
    Uses printOne to print out all courses within the graph.

Parameters:
    I   Graph graph      graph

**************************************************************************/
void printAllInList(Graph graph)
{
    // Declarations
    int i;
    EdgeNode * p;

    // Print a header
    printf("%-3s %-3s %-8s %-21s%-7s                           %-7s\n", "Vx","TE","Course","Name","Prereqs","Successors");

    // Call printOne for every course
    for(i = 0; i < graph->iNumVertices; i++)
    {
        printOne(graph, i, TRUE);
    }
}

/******************** printOne **************************************
void printOne(Graph graph, int iVertex)
Purpose:
    Print the vertex subscript, max dist from source (this isn't
    set until the DOPLAN command is executed in Pgm #6, from now use 0),
    course ID, course name, prereqs (max of 4), and successors.
    If the course doesn't exist, show a warning.
Parameters:
    I   Graph graph      graph
    I   int iVertex     vertex number
    I   int bPrintAll   true if printAll called this function

**************************************************************************/
void printOne(Graph graph, int iVertex, int bPrintAll)
{
    // Declarations
    EdgeNode * p;
    int iDots = 3;

    // Make sure course exists
    if((findCourse(graph, graph->vertexM[iVertex].szCourseId) == -1 || !graph->vertexM[iVertex].bExists) && !bPrintAll){
        printf("Course does %s not exist.\n", graph->vertexM[iVertex].szCourseId);
        return;
    }
    if(!graph->vertexM[iVertex].bExists)
        return;

    // See if printAll called this. If not, print a header.
    if(!bPrintAll)
        printf("%-3s %-3s %-8s %-21s%-7s                           %-7s\n", "Vx","TE","Course","Name","Prereqs","Successors");

    // Print vertex index and Vertex Name
    printf("%-3d %-3d %-8s %-21s", iVertex + 1, 0, graph->vertexM[iVertex].szCourseId,graph->vertexM[iVertex].szCourseName);

    // if Nonexistent
    if(graph->vertexM[iVertex].prereqList->iPrereqVertex == -1){
        printf("%s\t", "---");
    }
        // Print all prereqs
    else{
        for(p = graph->vertexM[iVertex].prereqList; p->pNextEdge != NULL; p = p->pNextEdge){
            printf("%s\t", graph->vertexM[p->iPrereqVertex].szCourseId);
            iDots--;
        }
        printf("%s\t", graph->vertexM[p->iPrereqVertex].szCourseId);
    }

    //Print dots for nonexistent prereqs
    while(iDots > 1){
        printf("...\t");
        iDots--;
    }
    if(iDots == 1)
        printf("...\t");

    // If no successor
    if(graph->vertexM[iVertex].successorList->iSuccVertex == -1){
        printf(" %-7s\n", "---");
    }
        // Print all Successors
    else{
        for(p = graph->vertexM[iVertex].successorList; p->pNextEdge->pNextEdge != NULL; p = p->pNextEdge){
            printf("%s\t", graph->vertexM[p->iSuccVertex].szCourseId);
        }
        printf("%s\n", graph->vertexM[p->iSuccVertex].szCourseId);
    }
}

/******************** doPlan **************************************
void doPlan(Graph graph, Plan plan)
Purpose:
    Sets each semester in the plan.  Although a course could have
    originally occurred in an earlier semester, only five courses
    are allowed per semester.  If a course is pushed back, all of its
    successors have to be pushed back.
Parameters:
    I   Graph graph      graph

Returns:

Notes:

**************************************************************************/
void doPlan(Graph graph, Plan plan)
{
    int i, j, iSem, iDist;
    int iTotSem = 0;
    int bChange = FALSE;

    // Call SetLevel
    for(i=0; i < graph->iNumVertices; i++){
        if (plan->bIncludeM[i]) {
            iDist = distanceFromSource(graph, plan, i, 0);
            setLevel(graph, plan, i, iDist);
        }
    }

    // Fill the semesters
    for(i=0; i < graph->iNumVertices; i++) {
        iSem = graph->vertexM[i].iSemesterLevel;
        if (plan->bIncludeM[i]) {
            if(iSem == -1 ) {
                continue;
            }
            while (!bChange) {
                for (j = 0; j < 5; j++) {
                    if (plan->semesterM[j][iSem] == -1 && !bChange) {
                        plan->semesterM[j][iSem] = i;
                        bChange = TRUE;
                    }
                }
                if(iSem > iTotSem)
                    iTotSem = iSem;
                iSem++;
            }
            bChange = FALSE;
        }
    }

    //Here print the semesters
    printf("Semester Plan\n");
    for(i=0; i <= iTotSem; i++) {
        printf("Semester #%d\n", i+1);
        for (j = 0; j < 5; j++) {
            if(plan->semesterM[j][i] != -1)
                printf("\t%s %s\n",graph->vertexM[plan->semesterM[j][i]].szCourseId, graph->vertexM[plan->semesterM[j][i]].szCourseName);
        }
    }
}

/******************** distanceFromSource **************************************
void distanceFromSource(Graph graph, Plan plan, iVertex, iSource)
Purpose:

Parameters:
    I   Graph graph      graph

Returns:

Notes:

**************************************************************************/
int distanceFromSource(Graph graph, Plan plan, int iVertex, int iDist)
{
    EdgeNode * p;
    int iMax = 0;
    int iCheck;

    if(iVertex == -1 || !plan->bIncludeM[iVertex])
        return iDist;

    for(p = graph->vertexM[iVertex].prereqList; p != NULL; p = p->pNextEdge) {
        iCheck = distanceFromSource(graph, plan, p->iPrereqVertex, iDist+1);
        if(iCheck > iMax)
            iMax = iCheck;
    }

    return iMax;
}