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
			printf("Course Already Exist %s\n", szCourseId);
            return -1;
		}
		
		//Store the Course Id, Name, and Department
		strcpy(szCourseId,tempVertex->szCourseId);
		strcpy(szCourseName,tempVertex->szCourseName);
		
		char szDept[4];
        int j;

		for(j = 0; j < strlen(szCourseId)-1; j++) {
            if (isalpha(szCourseId[j])) {
                szDept[j] = szCourseId[j];
            } else {
                break;
            }
        }

        strcpy(tempVertex->szDept, szDept);
		
        graph->vertexM[graph->iNumVertices] = *tempVertex;
        ++graph->iNumVertices;

    return 0;

}

int maxChain(Graph graph, int iVertex)
{
	
}


void printLongChains(Graph graph, int iVertex, int pathM[], int iLevel, int iLongLength)
{
	
}
