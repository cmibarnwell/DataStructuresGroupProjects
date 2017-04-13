#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <ctype.h>
#include "cs2123p5.h"
//FINSHED FUNCTIONS
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

    //printf("Maxchains iVertex: %d\n", iVertex);

	if(graph->vertexM[iVertex].successorList == NULL || iVertex == -1)
		return 0;

  //printf("Maxchains iVertex: %d\n", iVertex);

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
	EdgeNode *p;

	//If successorList is pointing to nothing ie the list is empty
	if(graph->vertexM[iVertex].successorList == NULL
							|| graph->vertexM[iVertex].successorList->iSuccVertex == -1)
		{
   //   printf("Hit the NULL if statement\n");
      return;
    }


	//Loop throught successors
	for(p=graph->vertexM[iVertex].successorList; p!=NULL; p=p->pNextEdge)
	{
		printf("iLevel = %d  iLongLength = %d\n "
																,iLevel ,iLongLength);
		//set location 0 to current vertex
		if(iLevel == 0)
			pathM[0] = iVertex;
		//Set the vertex to the current level
		else
		{
      //printf("hit FOR LOOP ELSE STATEMENT\n");
			//store vertex number into pathM
			pathM[iLevel] = p->iSuccVertex;
			printf("iVertex #  = %d   iVertex Name = %s\n "
																	,p->iSuccVertex
																	,graph->vertexM[p->iSuccVertex].szCourseId);
		}
		//Increase iLevel
    if(!iLevel || iLevel)
    {
     // printf("Tripped IF Statement, iLevel = %d\n", iLevel);
		  iLevel = iLevel + 1;
      //printf("End IF Statement, iLevel = %d", iLevel);
    }

		//Recursively print the courses in the longest chain
		printLongChains(graph, p->iSuccVertex, pathM, iLevel, iLongLength);
	}

		//Print the vertex stored into pathM
		if(iLevel == iLongLength)
		{
			int index;
			for(index = 0; index < iLongLength; index++)
			{
				printf("%s	",graph->vertexM[pathM[index]].szCourseId);

			}
			printf(" \n");
		}


}
