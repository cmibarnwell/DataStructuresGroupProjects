#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <ctype.h>
#include "cs2123p5.h"

int insertCourse(Graph graph, char szCourseId[], char szCourseName[])
{
	int iFind;
	int i;
	//If inserting will cause cycle return -1
	//if(causesCycle)
	//	return -1;

	iFind = findCourse(graph, szCourseId);


     //Create Vertex in vertexM[]
     if(iFind == -1)
     {
		Vertex tempVertex = allocateVertex(szCourseName, szCourseId);

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

		//Store new vertex and increase iNumVertices
		graph->vertexM[graph->iNumVertices] = tempVertex;
        ++graph->iNumVertices;
	 }
	 //Course already exist so update szCourseName
	 else
	 {
		 strcpy(graph->vertexM[iFind].szCourseName, szCourseName);
	 }
	 return 0;
}












int maxChain(Graph graph, int iVertex)
{
	int iMax = 0;
	int iValue = 0;
	EdgeNode *p;

    printf("Maxchains iVertex: %d\n", iVertex);

	if(graph->vertexM[iVertex].successorList == NULL || iVertex == -1)
		return 0;

	for(p = graph->vertexM[iVertex].successorList; p != NULL; p = p->pNextEdge)
	{
		iValue = 1 + maxChain(graph, p->iSuccVertex);
		if(iValue > iMax)
			iMax = iValue;
	}
	return iMax;

}











void printLongChains(Graph graph, int iVertex, int pathM[], int iLevel, int iLongLength)
{
	iLongLength = maxChain(graph, iVertex);
	EdgeNode *p = allocateEdgeNode();
	if(iLongLength == 0)
		return;

	printLongChains(graph, p->iSuccVertex, pathM, iLevel, iLongLength);
	//Loop through SuccessorList
	for(p = graph->vertexM[iVertex].successorList; p != NULL; p = p->pNextEdge)
	{
		if(maxChain(graph, p->iSuccVertex) == iLongLength - 1)
		{
			pathM[iLevel] = p->iSuccVertex;
			iLevel = iLevel + 1;
		}
	}
	//Check if iLevel = iLongLength and print
	if(iLevel == iLongLength)
	{
		int i;
		//print title
		printf("Longest chain beginning with %s\n. /t%s "
					,graph->vertexM[iVertex].szCourseId
					,graph->vertexM[pathM[0]].szCourseId);
		for(i = 0; i < iLongLength; i++)
		{
			//print the courses after the main course
			printf("%s  ", graph->vertexM[pathM[i]].szCourseId);

		}
	}
}
