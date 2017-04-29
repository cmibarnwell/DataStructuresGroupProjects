#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <ctype.h>
#include "cs2123p6.h"
/************************** insertCourse ******************************************
int insertCourse(Graph graph, char szCourseId[], char szCourseName[])

Purpose:
    	Searches the graph for the courseID passed in. If the vertx does not exist
			create a new vertex and store the CourseID, SzDept, and CourseName. Once
			vertex is created insert the vertex into the graph

Parameters:
		I 	Graph graph
    I   char szCourseName[]
    I   char szCourseId[]

Returns:
    0 if course was inserted

**************************************************************************/
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
		Vertex tempVertex = newVertex(szCourseName, szCourseId);

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

		int HashValue = hash(graph, szCourseId);
		//Store new vertex and increase iNumVertices
		if(graph->vertexM[HashValue].bExists)
		{
			i = HashValue;
			while (graph->vertexM[i].iHashChainNext != -1) {
				i = graph->vertexM[i].iHashChainNext;
			}
	  		graph->vertexM[i].iHashChainNext = graph->iFreeHead;
		  	graph->vertexM[graph->iFreeHead] = tempVertex;
		  	++graph->iFreeHead;
		}

		else
		{
		  	graph->vertexM[HashValue] = tempVertex;
		}
	 }
	 //Course already exist so update szCourseName
	 else
	 {
		 strcpy(graph->vertexM[iFind].szCourseName, szCourseName);
		 return 1;
	 }
	 return 0;
}
/************************** maxChain ******************************************
int maxChain(Graph graph, int iVertex)

Purpose:
    	Takes in a graph and vertex through the parameter list. Counts the longest
			course chain starting with the vertex given. Then returns the count of
			the max chain recursively

Parameters:
		I 	Graph graph
    I   int iVertex

Returns:
  iMax the value of the longest chain

**************************************************************************/
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
/************************** printLongChains ******************************************
void printLongChains(Graph graph, int iVertex, int pathM[], int iLevel, int iLongLength)

Purpose:
    	Uses maxChain to count the distance of the longest chain starting from the
			given vertex. Using that interger it prints all courses that start with
			the given vertex with the same chain length as max chain. Recursive.

Parameters:
		I 	Graph graph
		I		int iVertex
		I 	int pathM[]
		I		int iLevel
		I		int iLongLength


Returns:
    Void, prints the courses equal to the max chain.

**************************************************************************/
void printLongChains(Graph graph, int iVertex, int pathM[], int iLevel, int iLongLength)
{
	EdgeNode *p;

	//If successorList is pointing to nothing ie the list is empty
	if(graph->vertexM[iVertex].successorList == NULL
							|| iVertex == -1)
		{
      return;
    }

		if(iLevel == 0)
		{
			pathM[0] = iVertex; //set vertex to location 0
			iLevel = iLevel + 1;
		}


	//Loop throught successors
	for(p=graph->vertexM[iVertex].successorList; p!=NULL; p=p->pNextEdge)
	{
		int i = p->iSuccVertex;
		pathM[iLevel] = i;//store vertex number into pathM
		//Print the vertex stored into pathM
		if(iLevel == iLongLength-1 && i !=-1)
		{
			int index;
			for(index = 0; index < iLongLength; index++)
			{
				printf("%s	",graph->vertexM[pathM[index]].szCourseId);

			}
			printf(" \n");
		}
		//Recursively print the courses in the longest chain
		printLongChains(graph, i, pathM, iLevel+1, iLongLength);
	}

}


/************************** deleteCourse ******************************************
void deleteCourse(Graph graph, int iVertex)


Purpose:
    	Given a vertex and a graph, deleteCourse will remove that vertex from all
			prereqList and successorList. It will then set bExists to false so doPlan
			and other functions know not to include it

Parameters:
		I 	Graph graph
    I   int iVertex				vertex/course to be removed

Returns:
    void

**************************************************************************/
void deleteCourse(Graph graph, int iVertex)
{
	int i;
	int iTemp;
	EdgeNode *pRemove;
	EdgeNode *p;
	EdgeNode *pPrecedes = NULL;

	// Remove from Hash
	iTemp = OVERFLOW_BEGIN;
	for (i = OVERFLOW_BEGIN; i != -1; i = graph->vertexM[i].iHashChainNext)
	{
		printf("iVertex: %d, i is: %d, iTemp is: %d\n", iVertex, i, iTemp);
		if(i == iVertex){
			if(graph->vertexM[iVertex].iHashChainNext != -1){
				graph->vertexM[iTemp].iHashChainNext = graph->vertexM[iVertex].iHashChainNext;
			}
			else{
				graph->vertexM[iTemp].iHashChainNext = -1;
			}
			break;
		}
		iTemp = i;
	}

	//Remove the iVertex from the successorList
	for(i = 0; i < graph->iNumVertices; i++)//loop through the graph
	{
		if(i == iVertex)//Remove the vertex from the graph
			graph->vertexM[i].bExists = FALSE;

		for(p = graph->vertexM[i].successorList; p != NULL; p = p->pNextEdge)//loop through successorList
		{
			pRemove = p;
			if( p == NULL)//if the successorList is empty
					break;
			if(p->iSuccVertex == iVertex)//Vertex is in the successorList
			{
				if(pPrecedes == NULL)//iVertex is the first edgeNode
				{
					if(p->pNextEdge == NULL)//Removing would make list empty
					{
						p = NULL;
					}
					else//make p next edge the start of the successorList
					{
						p = p->pNextEdge;
					}
				}
				else//iVertex is in the middle or the end of the list
				{
					pPrecedes->pNextEdge = p->pNextEdge;
				}

			}
			pPrecedes = p;
		}
		for(p = graph->vertexM[i].prereqList; p != NULL; p = p->pNextEdge)//loop through successorList
		{
			pRemove = p;
			if( p == NULL)//if the prereqList is empty
					break;
			if(p->iPrereqVertex== iVertex)//Vertex is in the successorList
			{
				if(pPrecedes == NULL)//iVertex is the first edgeNode
				{
					if(p->pNextEdge == NULL)//Removing would make list empty
					{
						p = NULL;
					}
					else//make p next edge the start of the prereqList
					{
						p = p->pNextEdge;
					}
				}
				else//iVertex is in the middle or the end of the list
				{
					pPrecedes->pNextEdge = p->pNextEdge;
				}

			}
			pPrecedes = p;

		}

	}
}
