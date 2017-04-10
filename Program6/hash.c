// If compiling using visual studio, tell the compiler not to give its warnings
// about the safety of scanf and printf
#define _CRT_SECURE_NO_WARNINGS 1
#include <string.h>
#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>
#include "cs2123p6.h"
/******************** hash **************************************
  int hash(Graph g, char szCourseId[])
Purpose:
    Hashes a course ID to return a number between 0 and g->iOverflowBegin.
Parameters:
    I   Graph g          Graph represented as a double adjacency list
    I   char szCourseId  course ID to be hashed
Returns:
    Returns a hash value into the primary area.  This value is between 0
    and g->iOverflowBegin.
Notes:
    - Primary area of the hash table has subscripts from 0 to 
      g->iOverflowBegin -1.
    - Overflow area begins with g->iOverflowBegin.
    - The hash function is better than average at spreading the values. 
    - The hash uses the first three numeric digits of the course ID.  It
      sums the first digit * 32, second digit * 8, and the
      third digit. 
**************************************************************************/
int hash(Graph g, char szCourseId[])
{
    int iHash = 0;
    // Hash using the first three numeric values of the course ID
    // For CS courses, it begins in position 2.
    // For MAT courses, it begins in position 3.
    if (szCourseId[0] == 'C')
        iHash = ((szCourseId[2] - '0')<<5) + ((szCourseId[3] - '0')<<3) + szCourseId[4] - '0';
    else
        iHash = ((szCourseId[3] - '0')<<5) + ((szCourseId[4] - '0')<<3) + szCourseId[5] - '0';
    iHash = iHash % g->iOverflowBegin; // restrict it to the primary area
    return iHash;
}
/******************** printHash **************************************
  void printHash(Graph g)
Purpose:
    Prints the hash table in a format that helps show the primary area 
    and overflow area.  For each entry in the primary area, it prints 
    the entry (if present) and prints corresponding synonyms.
Parameters:
    I   Graph g          Graph represented as a double adjacency list
Returns:
    n/a
Notes:
    - Primary area of the hash table has subscripts from 0 to 
      g->iOverflowBegin -1.
    - Overflow area begins with g->iOverflowBegin. 
**************************************************************************/
void printHash(Graph g)
{
    int i;
    // Print the heading for both types of output (primary area and collisions
    printf("    %2s %-7s %-20s %s\n", "Vx", "Crse Id", "Course Name", "Chain");
    printf("\t%-9s %2s %-7s %-20s %s\n", "Collision", "Vx", "Crse Id", "Course Name", "Chain");
    
    // Iterate over each entry in the primary area
    for (i = 0; i < g->iOverflowBegin; i++)
    {
        // If it contains a vertex, print it
        if (g->vertexM[i].bExists)
        {   // vertex exists
            printf("    %2d %-7s %-20s %4d\n", i, g->vertexM[i].szCourseId
                , g->vertexM[i].szCourseName
                , g->vertexM[i].iHashChainNext);
            // print its collisions (if there are any)
            if (g->vertexM[i].iHashChainNext != -1)
                printChain(g, g->vertexM[i].iHashChainNext);
        }
        else if (g->vertexM[i].iHashChainNext != -1)
        {   // It doesn't have a vertex, but it has a chain
            printf("    %2d %-7s %-20s %4d\n", i, "-", " "
                , g->vertexM[i].iHashChainNext);
            printChain(g, g->vertexM[i].iHashChainNext);
        }
    }
    // Print the overflow free list
    printf("\tOverflow free list\n    ");
    for (i = g->iFreeHead; i != -1; i = g->vertexM[i].iHashChainNext)
    {
        printf("%2d ", i);
         
    }
    printf("\n");
}
/******************** printChain **************************************
  void printChain(Graph g, int iVertex)
Purpose:
    Prints vertices on a collision chain.  
Parameters:
    I   Graph g          Graph represented as a double adjacency list
    I   int iVertex      First collision in the overflow area for the 
                         current chain.
Returns:
    n/a
Notes:
    - Primary area of the hash table has subscripts from 0 to 
      g->iOverflowBegin -1.
    - Overflow area begins with g->iOverflowBegin. 
**************************************************************************/
void printChain(Graph g, int iVertex)
{
    int i;
    // Traverse the collision chain
    for (i = iVertex; i != -1; i = g->vertexM[i].iHashChainNext)
    {
        printf("\t%-9s %2d %-7s %-20s %2d\n", " ", i, g->vertexM[i].szCourseId
            , g->vertexM[i].szCourseName
            , g->vertexM[i].iHashChainNext);
    }
}