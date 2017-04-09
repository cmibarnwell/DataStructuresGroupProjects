#include "cs2123p5.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>


void dfs(Graph, int, int*, int, int*);

void dfs(Graph graph, int iVertex, int* visited, int iPrereqVertex, int* isCyclic)
{
  //printf("iVertex = %d, iPrereqVertex = %d\n", iVertex, iPrereqVertex);
 
  if(iVertex < 0 && iPrereqVertex < 0)
  {
    *isCyclic = FALSE;
    return;
  }
  
  if(visited[iVertex])
  {
//    printf("hit a visited vertex, iVertex = %d iPrereqVertex = %d\n", iVertex, iPrereqVertex);
    *isCyclic = TRUE;
    return;
  }

  else
  {
    visited[iVertex] = TRUE;
    EdgeNode* e;
    for(e = graph->vertexM[iVertex].successorList; e; e = e->pNextEdge)
    {
      if(e->iSuccVertex == iPrereqVertex)
      {
  //      printf("hit similar vertex?\n");
        *isCyclic = TRUE;
        return;
      }

      if(e->iSuccVertex != -1)
      {
        dfs(graph, e->iSuccVertex, visited, iPrereqVertex, isCyclic);
      }
    }
  }
}
int causeCycle(Graph graph, int iPrereqVertex, int iVertex)
{
  //iVertex is the subscript needed to get the correct vertex
  //within the vertex array.
  //

  if((iPrereqVertex >= graph->iNumVertices || iVertex >= graph->iNumVertices) || (iPrereqVertex < 0 || iVertex < 0))
  {
    printf("Attempted to index invalid memory. Used Vertex %d and Prereq Vertex%d\n", iVertex, iPrereqVertex);
    exit(1);
    return 0;
  }
  int iVertCount = graph->iNumVertices;
  int visited[iVertCount];
  int seenVerticies[iVertCount];
  int i;
  int isCyclic = FALSE;
  for(i = 0; i < iVertCount; i++)
  {
    visited[i] = FALSE;
   seenVerticies[i] = FALSE;
  }

  dfs(graph, iVertex, visited, iPrereqVertex, &isCyclic);
  return isCyclic;
}

int findCourse(Graph graph, char szCourseId[])
{
  int i;

  for(i = 0; i < graph->iNumVertices; ++i)
  {
    if(!strcmp(szCourseId, graph->vertexM[i].szCourseId))
    {
      return i;
    }
  }

  return -1; //not found
}

void setLevel(Graph g, Plan plan, int iVertex, int iLev)
{

}
