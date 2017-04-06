#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <ctype.h>
#include "cs2123p5.h"

int insertCourse(Graph graph, char szCourseId[], char szCourseName[])
{
	Vertex tempVertex = allocateVertex(szCourseName, szCourseId);
	int iFind;
	int i;
	iFind = findCourse(graph, szCourseId);
	//Copy SzDept into Vertex		
	char szDept[4];
    int j;
    //Store the letters of szDept into temp variable
	for(j = 0; j < strlen(szCourseId)-1; j++)
	{
		if (isalpha(szCourseId[j])) 
			szDept[j] = szCourseId[j]; 
        else 
			break;
            
     }
	 //copy szDept into the vertez
     strcpy(tempVertex.szDept, szDept);
      
     //Create Vertex in vertexM[]
     if(iFind == -1)
     {
		graph->vertexM[graph->iNumVertices] = tempVertex;
        ++graph->iNumVertices;
	 }
	 //Course already exist so update szCourseName
	 else
	 {
		 strcpy(graph->vertexM[iFind].szCourseName, tempVertex.szCourseName);
	 }
	 return 0;
}
	
	
	
	
	







int maxChain(Graph graph, int iVertex)
{
	int iMax = 0;
	EdgeNode *p = allocateEdgeNode();
	
	if(graph->vertexM[iVertex].successorList->pNextEdge == NULL)
		return 1;
	
	for(p = graph->vertexM[iVertex].successorList; p != NULL; p = p->pNextEdge)
	{
		int iValue = 0;
		iValue += maxChain(graph, p->iSuccVertex);
		if(iValue > iMax)
			iMax = iValue;
	}
	return iMax;
	
}


void printLongChains(Graph graph, int iVertex, int pathM[], int iLevel, int iLongLength)
{
	
}
