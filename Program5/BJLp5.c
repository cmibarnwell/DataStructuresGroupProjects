#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <ctype.h>
#include "cs2123p5.h"

int insertCourse(Graph graph, char szCourseId[], char szCourseName[])
{
	Vertex *tempVertex = allocateVertex(szCourseName, szCourseId);
	int iFind;
	int i;
	iFind = findCourse(graph, szCourseId);
		//Check if course already exist
		if(iFind != -1)
		{
			ErrExit(ERR_BAD_COURSE,"Course Already Exist");
		}
		
		//Store the Course Id, Name, and Department
		strcpy(szCourseId,tempVertex->szCourseId);
		strcpy(szCourseName,tempVertex->szCourseName);
		
		char szTempCourseId[MAX_TOKEN], szToken[MAX_TOKEN], szDept[MAX_TOKEN]; //Temp Varibles for get token
		strcpy(szTempCourseId, szCourseId);			//Copy szCourseId into temp
		
		while(TRUE)
		{
			strcpy(szTempCourseId,getToken(szTempCourseId, szToken, 1));
			if(isalpha(szToken))
				strcat(szDept,szToken);
				
			else
				break;
		}

        strcpy(tempVertex->szDept, szDept);
		
		//Loop through the Graph
		for(i=0; i < graph->iNumVertices; i++)
		{
			
		}
		//Insert vertex into array
        graph->iNumVertices++;
        graph->vertexM[graph->iNumVertices] = *tempVertex;

    return 0;

}

int maxChain(Graph graph, int iVertex)
{
	
}


void printLongChains(Graph graph, int iVertex, int pathM[], int iLevel, int iLongLength)
{
	
}
