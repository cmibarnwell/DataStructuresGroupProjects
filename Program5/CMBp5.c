/****************************************************************
 CMBp5.c by Caleb Barnwell

 Purpose:

 Input:


 Returns:

 Notes:

 ****************************************************************/

#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include "cs2123p5.h"



/******************** printSuccessors **************************************
void printSuccessors(Graph graph)
Purpose:

Parameters:
    I   Graph graph      graph

Returns:

Notes:

**************************************************************************/
void printSuccessors(Graph graph, int iVertex)
{
    int visitedM[graph->iNumVertices], i;
    EdgeNode * p;

    if(findCourse(graph, graph->vertexM[iVertex].szCourseId) == -1)
    {
        printf("Course %s not found.", graph->vertexM[iVertex].szCourseId);
        return;
    }

    // Initialize our Visited to false
    for(i=0;i<graph->iNumVertices;i++)
        visitedM[i]= FALSE;

    // Use DFT to find all successors
    printTraversal(graph, iVertex, 0, visitedM);
}

/******************** printTraversal **************************************
void printTraversal(Graph graph, int iCourseVertex, int indent)
Purpose:

Parameters:
    I   Graph graph      graph
    I   int iCourseVertex
    I   int indent

Returns:

Notes:

**************************************************************************/
void printTraversal(Graph graph, int iCourseVertex, int iIndent, int visitedM[])
{
    int i;
    EdgeNode * p;

    //check if NULL
    if (iCourseVertex == -1)
        return;


    for (i = 0; i < iIndent; i++) {
        printf("\t");
    }
    printf("%s %s\n",graph->vertexM[iCourseVertex].szCourseId, graph->vertexM[iCourseVertex].szCourseName);

    if (visitedM[iCourseVertex] == TRUE)
        return;

    visitedM[iCourseVertex]= TRUE;

    for (p = graph->vertexM[iCourseVertex].successorList; p != NULL; p = p->pNextEdge) {
        printTraversal(graph, p->iSuccVertex, iIndent + 1, visitedM);
    }
}

/******************** printSources **************************************
void printSources(Graph graph)
Purpose:

Parameters:
    I   Graph graph      graph

Returns:

Notes:

**************************************************************************/
void printSources(Graph graph)
{
    int i;
    int bFindEver = FALSE;

    printf("All Sources:\n");

    for(i = 0; i < graph->iNumVertices; i++)
    {
        if(graph->vertexM[i].prereqList->iPrereqVertex == -1) {
            printf("%s %s\n", graph->vertexM[i].szCourseId, graph->vertexM[i].szCourseName);
            bFindEver = TRUE;
        }
    }

    if(!bFindEver)
        printf("None\n");
}

/******************** printSinks **************************************
void printSinks(Graph graph)
Purpose:

Parameters:
    I   Graph graph      graph

Returns:

Notes:

**************************************************************************/
void printSinks(Graph graph)
{
    int i, j;
    int bFind = FALSE;
    int bFindEver = FALSE;

    printf("All Sinks:\n");

    for(i = 0; i < graph->iNumVertices; i++)
    {
        for(j = 0; j < graph->iNumVertices; j++)
        {
            if(graph->vertexM[j].prereqList->iPrereqVertex == i) {
                bFind = TRUE;
                bFindEver = TRUE;
            }
        }
        if(!bFind)
            printf("%s %s\n", graph->vertexM[i].szCourseId, graph->vertexM[i].szCourseName);
        bFind = FALSE;
    }

    if(!bFindEver)
        printf("None\n");
}

/******************** printAllInList **************************************
void printAllInList(Graph graph)
Purpose:

Parameters:
    I   Graph graph      graph

Returns:

Notes:

**************************************************************************/
void printAllInList(Graph graph)
{
    int i;
    EdgeNode * p;

    printf("%-3s %-3s %-21s%-7s                            %-7s\n"
         , "Vx","TE","Course Name","Prereqs","Successors");

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

Returns:

Notes:

**************************************************************************/
void printOne(Graph graph, int iVertex, int bPrintAll)
{
    EdgeNode * p;
    int iDots = 3;

    if(!bPrintAll)
        printf("%-3s %-3s %-21s%-7s                            %-7s\n", "Vx","TE","Course Name","Prereqs","Successors");

    printf("%-3d %-3d %-21s", iVertex + 1, 0, graph->vertexM[iVertex].szCourseName);


    if(graph->vertexM[iVertex].prereqList->iPrereqVertex == -1){
         printf("%-7s", "---");
    }
    else{
        for(p = graph->vertexM[iVertex].prereqList; p->pNextEdge != NULL; p = p->pNextEdge){
            printf("%s\t", graph->vertexM[p->iPrereqVertex].szCourseId);
            iDots--;
        }
        printf("%s ", graph->vertexM[p->iPrereqVertex].szCourseId);
        iDots--;
    }

    while(iDots > 1){
        printf("\t...");
        iDots--;
    }
    if(iDots == 1)
        printf("\t...\t");

    if(graph->vertexM[iVertex].successorList->iSuccVertex == -1){
        printf(" %-7s\n", "---");
    }
    else{
        for(p = graph->vertexM[iVertex].successorList; p->pNextEdge != NULL; p = p->pNextEdge){
            printf("%s\t", graph->vertexM[p->iSuccVertex].szCourseId);
        }
        printf("%s\n", graph->vertexM[p->iSuccVertex].szCourseId);
    }
}

/******************** doPlan **************************************
void doPlan(Graph graph, Plan plan)
Purpose:

Parameters:
    I   Graph graph      graph

Returns:

Notes:

**************************************************************************/
void doPlan(Graph graph, Plan plan)
{

}