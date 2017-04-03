#include "cs2123p5.h"
#include <string.h>


int causeCycle(Graph graph, int iPrereqVertex, int iVertex)
{
  //iVertex is the subscript needed to get the correct vertex
  //within the vertex array.
  Vertex v = graph->vertexM[iVertex];

  //this part is a bit contested, I either need the prereq list or 
  //the successor list.
  //Judging by the paper clark gave us, I'm assuming that its the successor
  //list.
  EdgeNode* e = v.successorList;
  //since this adjacency list is represented with a 
  //linked list, we can just iterate through the nodes.
  while(e)
  {
    //if the prereq vertex of the successor list
    //equals the prereq vertex given, then it woulc cause a cycle.
    if(e->iPrereqVertex == iPrereqVertex)
    {
      return TRUE;
    }
  }

  return FALSE;
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
