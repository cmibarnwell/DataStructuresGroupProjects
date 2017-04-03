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
void printSuccessors(Graph graph, EdgeNode * pEdge, int iIndent)
{
    int i;

    //check if NULL
    if (pEdge == NULL)
        return;

    //Print the successors recursively
    printSuccessors(graph, pEdge->pNextEdge, iIndent+1);

    for(i=0; i<iIndent; i++){
        printf("\t");
    }
    printf("%s\n", graph->vertexM[pEdge->iSuccVertex].szCourseName);
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
void printTraversal(Graph graph, int iCourseVertex, int indent)
{

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

Parameters:
    I   Graph graph      graph

Returns:

Notes:

**************************************************************************/
void printOne(Graph graph, int iVertex)
{

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