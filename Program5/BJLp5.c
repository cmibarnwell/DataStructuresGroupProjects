#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include "cs2123p5.h"


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
