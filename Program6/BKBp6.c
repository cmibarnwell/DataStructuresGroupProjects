#include "cs2123p6.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

//utility funciton used by causeCycle
void dfs(Graph, int, int*, int, int*);
void getPotentialPrereq(Graph, int, int*, int);
int getPrereqChain(Graph, int, int);
int reverseMaxChain(Graph, int);

int reverseMaxChain(Graph graph, int iVertex)
{
  //printf("IN LOOP HIT DFSCHAIN %d\n", iVertex);
  if(iVertex == -1 || graph->vertexM[iVertex].prereqList == NULL || !graph->vertexM[iVertex].bExists)
  {
    return 0;
  }

  int max = 0, value = 0;

  EdgeNode* list = NULL;
  for(list = graph->vertexM[iVertex].prereqList; list != NULL; list = list->pNextEdge)
  {
    //printf("IN LOOP HIT RECURSIVE CYCLE\n");
    //printf("IN LOOP VALUE IS %d\n", list->iSuccVertex);
    value = 1 + reverseMaxChain(graph, list->iPrereqVertex);
    if(value > max)
    {
      max = value;
    }
  }
  //printf("IN LOOP WITH COUNT %d\n",max);
  return max;

}


int getPrereqChain(Graph graph, int iVertex, int iLevel)
{
  int count = 0, temp = 0;
  //printf("Begin getPrereqChain\n");
  count = reverseMaxChain(graph, iVertex);
  //printf("Exit getPrereqChain\n");
  return count;
}


void getPotentialPrereq(Graph graph, int iVertex, int* iPrereqVertex, int iLevel)
{
  if(iVertex < 0 || iVertex >= graph->iNumVertices)
  {
    //printf("Attempted to index invalid memory, to obtain potential prereq. iVertex = %d\n.", iVertex);
    //printf("Skipping...\n");
    //exit(1);
    return;
  }

  //printf("Begin PrereqVertex\n");

  EdgeNode* list = NULL;
  int temp = 0, max = 0, actualvert = 0;
    for(list= graph->vertexM[iVertex].prereqList; list != NULL; list = list->pNextEdge)
    {
    //printf("IN LOOP %s\n", graph->vertexM[list->iSuccVertex].szCourseName);

      temp = reverseMaxChain(graph, list->iSuccVertex);
      //printf("IN LOOP with TEMP %d\n", temp);
      if(temp > max)
      {
        max = temp;
        actualvert = list->iSuccVertex;
      }
    }
    //printf("Exit getPotentialPrereq\n");
  *iPrereqVertex = actualvert;
}

/**************** dfs ****************
 * void dfs(Graph graph, int iVertex, int* visited, int iPrereqVertex, int* isCyclic)
 *
 * Purpose:
 *  This function searches the graph to see if there would be a cycle
 *  if the eddge would be inserted.
 *
 * Paremeters:
 * I    Graph graph           the graph to search
 * I    int   iVertex         the vertex index
 * I/O  int*  visitedM        the array used to keep track of whether or not a vertex was visited
 * I    int   iPrereqVertex   the prereq vertex index
 * O    int*  bIsCyclic       the variable used to determine if there was a cycle of not
 *
 * Return Value:
 *    return value is true if there is a cycle, false otherwise, via the paremeter list.
 *
 *
 * Notes:
 *  Used by causeCycle to delegate all of the heavy lifting of searching
 *  for a prereq cycle.
 *
 **************************************/
void dfs(Graph graph, int iVertex, int* visited, int iPrereqVertex, int* bIsCyclic)
{
 // printf("iVertex = %d, iPrereqVertex = %d\n", iVertex, iPrereqVertex);
 
  //check if the verticies are not -1
  if(iVertex < 0 && iPrereqVertex < 0)
  {
    *bIsCyclic = FALSE;
    return;
  }
  
  //if weve hit the vertex, we have hit a cycle
  if(visited[iVertex])
  {
   // printf("hit a visited vertex, iVertex = %d iPrereqVertex = %d\n", iVertex, iPrereqVertex);
    *bIsCyclic = TRUE;
    return;
  }

  //otherwise, recurse to the next vertex
  else
  {
    //mark the vertex as visited
    visited[iVertex] = TRUE;
    EdgeNode* e;
    for(e = graph->vertexM[iVertex].successorList; e; e = e->pNextEdge)
    {
      //if the successor vertex is the prereq vertex, we have hit a cycle
      if(e->iSuccVertex == iPrereqVertex)
      {
        
        *bIsCyclic = TRUE;
        return;
      }
        
      //if the successor vertex is not invalid, then search the next vertex
      if(e->iSuccVertex != -1)
      {
        dfs(graph, e->iSuccVertex, visited, iPrereqVertex, bIsCyclic);
      }
    }
  }
}

/********************* causeCycle *********************
 *
 *Purpose:
 *  To be a nice wrapper that determines if the insertion of an edge
 *  would cause a cycle.
 *
 *Parameters:
 *   I Graph  graph            the graph used to search the verticies
 *   I int    iPrereqVertex    the prereq vertex index
 *   I int    iVertex          the vertex index
 *
 *
 *Return value:
 *  Returns true if there would be a cycle, false otherwise.
 *
 *
 *
 ******************************************************/
int causesCycle(Graph graph, int iPrereqVertex, int iVertex)
{
  //if either the vertex indexes are greater than the number of verticies in the
  //graph, or either or them are -1
  //exit immediately
  if((iPrereqVertex >= graph->iNumVertices || iVertex >= graph->iNumVertices) || (iPrereqVertex < 0 || iVertex < 0))
  {
    printf("Attempted to index invalid memory. Used Vertex %d and Prereq Vertex%d\n", iVertex, iPrereqVertex);
    exit(1);
    return 0;
  }
  //set up the necessary variables to check if there is a cycle
  int iVertCount = graph->iNumVertices;
  int visited[iVertCount];
  int i;
  //like the legal system, we assume there will not be a cycle unless proven 
  //otherwise
  int bIsCyclic = FALSE;
  //make all the elements int the visited verticies array false since
  //none of the verticies have been visited
  for(i = 0; i < iVertCount; i++)
  {
    visited[i] = FALSE;
  }

  //call the function that does the real heavy lifting, then return whether or not
  //it is cyclic
  dfs(graph, iVertex, visited, iPrereqVertex, &bIsCyclic);
  return bIsCyclic;
}


/******************* findCourse *****************
 * int findCourse(Graph graph, char szCourseId[])
 *
 * Purpose:
 *    This function searches the graph for a particular course.
 *
 * Parameters:
 *  I Graph  graph            the graph to search
 *  I char   szCourseId[]     the course id
 *
 * Return Value:
 * if found, returns the index of the course, -1 otherwise.
 *
 ************************************************/
int findCourse(Graph graph, char szCourseId[])
{
  int i; //iterator
 

  //search through the graph
  for(i = 0; i < graph->iNumVertices; ++i)
  {
    //if found, return index
    if(!strcmp(szCourseId, graph->vertexM[i].szCourseId))
    {
      return i;
    }
  }

  //othweise, return -1 since its not found
  return -1;
}



/******************* setLevel **********************
 * void setLevel(Graph graph, Plan plan, int iVertex, int iLev)*
 * Purpose:
 *  This function sets the level of a given vertex.
 *
 *
 * Parameters:
 * I Graph graph    the graph used to get the vertex
 * I Plan  plan     the plan used to determine the level
 * I int   iVertex  the vertex index
 * I int   iLev     the level to set the vertex to
 *
 ***************************************************/
void setLevel(Graph g, Plan plan, int iVertex, int iLev)
{

  if(iVertex < 0 || iVertex >= g->iNumVertices)
  {
    printf("Attemted to set level with invalid vertex, iVertex = %d\n", iVertex);
    exit(1);
  }

 //printf("iLevel = %d\n", iLev);

 int tempreq = 0;
 int temp = 0;
 int semesterLevel = 0;
// printf("semesterLevel = %d\n", semesterLevel);
 //is it in the plan?
  if(plan->bIncludeM[iVertex])
  {
   //its in the plan,
   //so check for its prereqs
   getPotentialPrereq(g, iVertex, &tempreq, iLev);
   temp = tempreq;
   if(temp > 0)
   {
     while(plan->bIncludeM[temp] && iLev - 1 > 0)
     {
	--iLev;
	//printf("iLevel is now %d\n", iLev);
        ++semesterLevel;
	//printf("semesterLevel is now %d\n", semesterLevel);
     	getPotentialPrereq(g, temp, &tempreq, iLev);
     	temp = tempreq;
     }
   }
   
  }
  //printf("Returning %d\n", semesterLevel);
  g->vertexM[iVertex].iSemesterLevel = semesterLevel;
  //printf("Possible return value %d\n", semesterLevel + 1);

 }
