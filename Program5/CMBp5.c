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
    printTraversal(graph, iVertex, 0);
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
void printTraversal(Graph graph, int iCourseVertex, int iIndent)
{
    int i;

    //check if NULL
    if (iCourseVertex == -1)
        return;

    for(i=0; i<iIndent; i++){
        printf("\t");
    }
    printf("%s\n", graph->vertexM[iCourseVertex].szCourseName);

    //Print the successors recursively
    printTraversal(graph, graph->vertexM[iCourseVertex].successorList->iSuccVertex, iIndent+1);
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
void printOne(Graph graph, int iVertex)
{
    printf("%-4s%-3s%20s%-15s%-15s\n", "Vx","TE","Course Name","Prereqs","Successors");
    printf("%d %4d %20s\n",iVertex, 0, graph->vertexM[iVertex].szCourseName);
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