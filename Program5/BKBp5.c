#include "cs2123p5.h"
#include <string.h>


int causeCycle(Graph graph, int iPrereqVertex, int iVertex)
{
	
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
