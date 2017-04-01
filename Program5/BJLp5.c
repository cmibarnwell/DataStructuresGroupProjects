#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include "cs2123p5.h"

void insertCourse(Graph graph, char* szCourseId[], char* szCourseName[])
{
	Vertex *tempVertex = allocateVertex(szCourseName, szCourseId);
	int iFind;
	int i;
	iFind = findCourse(graph, szCourseId);
		//Check if course already exist
		if(iFind == -1)
		{
			ErrExit(ERR_BAD_COURSE,"Course Already Exist")
		}
		
		//Store the Course Id, Name, and Departmentm
		strcpy(tempVertex->szDept, szDept);
		strcpy(szCourseId,tempVertex->szCourseId);
		strcpy(szCourseName,tempVertex->szCourseName);
		
		char szTempCourseId[], szToken[], szDept[]; //Temp Varibles for get token
		strcpy(szTempCourseId, szCourseId);			//Copy szCourseId into temp
		
		while(TRUE)
		{
			szTempCourseId = getToken(szTempCourseId, szToken, 1);
			if(!isdigit(szToken))
				strcat(szDept,szToken);
				
			else
				break
		}
		
		//Loop through the Graph
		for(i=0; i < graph->iNumVertices; i++)
		{
			
		}
		//Insert vertex into array
		graph.vertexM[iNumVertices] = tempVertex;
		iNumVertices++
				
	}
}




















/*******TO DO LIST*********/

/*********************************************************************** 
--TEST


--Insertion






--MAXCHAIN   szCourseId
Prints the count of the number of successors in the longest chain 
that begins with the specified vertex. If the course doesn't exist, 
show a warning.

RECURSIVE 
int maxChainLength(Graph graph, int iVertex)
Returns the a count of the number of vertices in the longest chain that
begins with the specified vertex.

Depth First or Breadth first

****successor list
check if pNext edge is null
compare successor nodes to find greatest
move to that vertex increase count
repeat









RECURSIVE
--void printLongChains(Graph graph, int iVertex, int pathM[], int iLevel, int iLongLength) 

Prints each chain that is the the longest chain of courses and 
prerequisites beginning at the specified course.


Parameters:
iVertex - begins with a starting vertex from which we want to print its 
longest chains.  On subsequent calls, this is a successor vertex.

pathM[] - an array representing the path from the original starting
vertex to the current vertex

iLevel - on each recursive call of printLongChains, this increases.  
It is used as the subscript into pathM[].  It is also used to test 
whether we reached iMaxLength.


iLongLength - known longest chain length







--deleteCourse()










***********************************************************************/ 
