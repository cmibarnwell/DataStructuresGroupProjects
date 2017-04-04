/****************************************************************
 cs2123p5Driver.c by Caleb Barnwell
 
 Purpose:
     The driver file for Program 5
 Input:
    

 Returns:
     
 Notes:
     
 ****************************************************************/

#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include "cs2123p5.h"

 int main(int argc, char *argv[])
 {
     Graph graph = newGraph();
     readData(graph);

     freeGraph(graph);
 }


/************************** readData ******************************************
void readData(Graph graph)
Purpose:

Parameters:
    I   Graph graph      graph

Returns:

Notes:

**************************************************************************/
void readData(Graph graph)
{
    char szInputBuffer[MAX_LINE_SIZE], szType[MAX_TOKEN], szCourseId[MAX_TOKEN], szLastId[MAX_TOKEN];
    char * pszRemainingBuffer = NULL;
    int iLevel, iPrevLevel;
    FILE * pFile = fopen("p5Input.txt", "r");

    //Below is WIP!!!!!
    while(fgets(szInputBuffer, MAX_LINE_SIZE-1, pFile))
    {
        pszRemainingBuffer = getToken(szInputBuffer, szType, MAX_TOKEN-1);
        if(strcmp(szType,"COURSE")==0) {
            pszRemainingBuffer = getToken(pszRemainingBuffer, szCourseId, MAX_TOKEN-1);

            // Remove the trailing new line
            strtok(pszRemainingBuffer, "\n");


            printf(">> COURSE %s %s\n", szCourseId, pszRemainingBuffer);
            insertCourse(graph, szCourseId, pszRemainingBuffer);
            strcpy(szLastId, szCourseId);
        }
        else if(strcmp(szType,"PREREQ")==0) {
            pszRemainingBuffer = getToken(pszRemainingBuffer, szCourseId, MAX_TOKEN-1);
            printf(">> PREREQ %s\n", szCourseId);
            if(findCourse(graph, szCourseId)==-1)
                insertCourse(graph, szCourseId, "TBD");
            newEdgeNode(graph->vertexM[findCourse(graph, szLastId)].prereqList, findCourse(graph, szCourseId), findCourse(graph, szLastId));
            newEdgeNode(graph->vertexM[findCourse(graph, szCourseId)].successorList, findCourse(graph, szCourseId), findCourse(graph, szLastId));
        }
        else if(strcmp(szType, "PRTONE")==0){
            pszRemainingBuffer = getToken(pszRemainingBuffer, szCourseId, MAX_TOKEN-1);
            printf(">> PRTONE %s\n", szCourseId);
            printOne(graph, findCourse(graph, szCourseId));
        }
        else if(strcmp(szType, "PRTSUCC")==0){
            pszRemainingBuffer = getToken(pszRemainingBuffer, szCourseId, MAX_TOKEN-1);
            printf(">> PRTSUCC %s\n", szCourseId);
            printSuccessors(graph,findCourse(graph, szCourseId));
        }
        else if(strcmp(szType, "PRTALL")==0){
            printf(">> PRTALL\n");
            printAllInList(graph);
        }
        else if(strcmp(szType, "MAXCHAIN")==0){
            pszRemainingBuffer = getToken(pszRemainingBuffer, szCourseId, MAX_TOKEN-1);
            printf(">> MAXCHAIN %s\n", szCourseId);
            //maxChain(graph, findCourse(graph, szCourseId));
        }
        else if(strcmp(szType, "PRTLONGS")==0){
            pszRemainingBuffer = getToken(pszRemainingBuffer, szCourseId, MAX_TOKEN-1);
            printf(">> PRTLONGS %s\n", szCourseId);
            //printLongChains(graph,findCourse(graph,szCourseId),);
        }
        else if(strcmp(szType, "PRTSINKS")==0){
            printSinks(graph);
        }
        else if(strcmp(szType, "PRTSOURCES")==0){
            printSources(graph);
        }
        else if(strcmp(szType, "*")==0){
            fgets(szInputBuffer, MAX_LINE_SIZE-1, pFile);
            strtok(szInputBuffer, "\n");
            printf(">> *\n>> %s\n>> *\n", szInputBuffer);
            fgets(szInputBuffer, MAX_LINE_SIZE-1, pFile);
            continue;
        }
        else{
            ErrExit(ERR_COMMAND_LINE, "Delegated command %s unknown.", szType);
        }
    }

    fclose(pFile);
}




/**************************
Start Graph Funcs
**************************/

//The dft is not yet functional, and may be unnecessary. However I'm putting it here in case we need it - Caleb
/************************** dft ******************************************
void dft(Graph g, int v, int visitedM[])
Purpose:

Parameters:
    I   Graph graph      graph
    I   int v
    I   int visitedM[]

Returns:

Notes:

**************************************************************************
void dft(Graph g, int v, int visitedM[])
{
    EdgeNode *e;
    if (visitedM[v])
        return;
    visitedM[v] = TRUE;
    //visit vertex, perform necessary operations

    for (e = g->vertexM[v].successorList; e != NULL; e = e->pNextEdge) {
        //visit edge, perform necessary operations


        dft(g, e->iVertex, visitedM)
    }
}*/

/************************** newGraph ******************************************
Graph newGraph()
Purpose:

Parameters:

Returns:

Notes:

**************************************************************************/
Graph newGraph()
{
    Graph graph;

    graph = (Graph)malloc(sizeof(GraphImp));
    if(graph == NULL)
        ErrExit(ERR_ALGORITHM, "No available memory for Graph");
    graph->iNumVertices = 0;

    return graph;
}

/************************** freeGraph ******************************************
void freeGraph()
Purpose:

Parameters:

Returns:

Notes:

**************************************************************************/
void freeGraph(Graph graph)
{
    free(graph);
}

/************************** allocateVertex ******************************************
Vertex * allocateVertex(char szCourseName[], char szCourseID[])
Purpose:

Parameters:
    I   char szCourseName[]
    I   char szCourseId[]

Returns:

Notes:

**************************************************************************/
Vertex allocateVertex(char szCourseName[], char szCourseId[])
{
    Vertex vertex;
    strcpy(vertex.szCourseId, szCourseId);
    strcpy(vertex.szCourseName, szCourseName);
    strcpy(vertex.szDept, "");
    vertex.prereqList = allocateEdgeNode();
    vertex.successorList = allocateEdgeNode();

    return vertex;
}

/************************** allocateEdgeNode ******************************************
Vertex * allocateVertex(char szCourseName[], char szCourseID[])
Purpose:

Parameters:
    I   char szCourseName[]
    I   char szCourseId[]

Returns:

Notes:

**************************************************************************/
EdgeNode * allocateEdgeNode()
{
    EdgeNode *pEdge = (EdgeNode *)malloc(sizeof(EdgeNode));
    if(pEdge == NULL)
        ErrExit(ERR_ALGORITHM, "No available memory for Edge Node");
    pEdge->iPrereqVertex = -1;
    pEdge->iSuccVertex = -1;
    pEdge->pNextEdge = NULL;

    return pEdge;
}

/******************** newEdgeNode ****************************
EdgeNode * newEdgeNode(EdgeNode * list, int iPrereqVertex, int iSuccVertex)
 Purpose:

 Parameters:

 Returns:

 *****************************************************************/
EdgeNode * newEdgeNode(EdgeNode * list, int iPrereqVertex, int iSuccVertex)
{
    EdgeNode *p, *pPrecedes, *pNew;


    if(list->iPrereqVertex == -1 || list->iSuccVertex == -1)
    {
        list->iPrereqVertex = iPrereqVertex;
        list->iSuccVertex = iSuccVertex;
        return list;
    }

    pPrecedes = NULL;

    for(p = list; p!=NULL; p=p->pNextEdge)
    {
        pPrecedes = p;
    }

    pNew = allocateEdgeNode();
    pNew->iPrereqVertex = iPrereqVertex;
    pNew->iSuccVertex = iSuccVertex;
    if(pPrecedes != NULL)
        pPrecedes->pNextEdge = pNew;
    return pNew;
}

/**************************
End Graph Funcs
**************************/



/**************************
Utility Functions
**************************/

/******************** getToken **************************************
char * getToken (char *pszInputTxt, char szToken[], int iTokenSize)
Purpose:
    Examines the input text to return the next token.  It also
    returns the position in the text after that token.  This function
    does not skip over white space, but it assumes the input uses
    spaces to separate tokens.
Parameters:
    I   char *pszInputTxt       input buffer to be parsed
    O   char szToken[]          Returned token.
    I   int iTokenSize          The size of the token variable.  This is used
                                to prevent overwriting memory.  The size
                                should be the memory size minus 1 (for
                                the zero byte).
Returns:
    Functionally:
        Pointer to the next character following the delimiter after the token.
        NULL - no token found.
    szToken parm - the returned token.  If not found, it will be an
        empty string.
Notes:
    - If the token is larger than iTokenSize, we return a truncated value.
    - If a token isn't found, szToken is set to an empty string
    - This function does not skip over white space occurring prior to the token.
**************************************************************************/
char * getToken(char *pszInputTxt, char szToken[], int iTokenSize)
{
    int iDelimPos;                      // found position of delim
    int iCopy;                          // number of characters to copy
    char szDelims[20] = " \n\r";        // delimiters
    szToken[0] = '\0';

    // check for NULL pointer 
    if (pszInputTxt == NULL)
        ErrExit(ERR_ALGORITHM
        , "getToken passed a NULL pointer");

    // Check for no token if at zero byte
    if (*pszInputTxt == '\0')
        return NULL;

    // get the position of the first delim
    iDelimPos = strcspn(pszInputTxt, szDelims);

    // if the delim position is at the first character, return no token.
    if (iDelimPos == 0)
        return NULL;

    // see if we have more characters than target token, if so, trunc
    if (iDelimPos > iTokenSize)
        iCopy = iTokenSize;             // truncated size
    else
        iCopy = iDelimPos;

    // copy the token into the target token variable
    memcpy(szToken, pszInputTxt, iCopy);
    szToken[iCopy] = '\0';              // null terminate

    // advance the position
    pszInputTxt += iDelimPos;
    if (*pszInputTxt == '\0')
        return pszInputTxt;
    else
        return pszInputTxt + 1;
}

/******************** ErrExit **************************************
  void ErrExit(int iexitRC, char szFmt[], ... )
Purpose:
    Prints an error message defined by the printf-like szFmt and the
    corresponding arguments to that function.  The number of
    arguments after szFmt varies dependent on the format codes in
    szFmt.
    It also exits the program with the specified exit return code.
Parameters:
    I   int iexitRC             Exit return code for the program
    I   char szFmt[]            This contains the message to be printed
                                and format codes (just like printf) for
                                values that we want to print.
    I   ...                     A variable-number of additional arguments
                                which correspond to what is needed
                                by the format codes in szFmt.
Returns:
    Returns a program exit return code:  the value of iexitRC.
Notes:
    - Prints "ERROR: " followed by the formatted error message specified
      in szFmt.
    - Prints the file path and file name of the program having the error.
      This is the file that contains this routine.
    - Requires including <stdarg.h>
**************************************************************************/
void ErrExit(int iexitRC, char szFmt[], ... )
{
    va_list args;               // This is the standard C variable argument list type
    va_start(args, szFmt);      // This tells the compiler where the variable arguments
    // begins.  They begin after szFmt.
    printf("ERROR: ");
    vprintf(szFmt, args);       // vprintf receives a printf format string and  a
    // va_list argument
    va_end(args);               // let the C environment know we are finished with the
    // va_list argument
    printf("\n\tEncountered in file %s\n", __FILE__);  // this 2nd arg is filled in by
    // the pre-compiler
    exit(iexitRC);
}
/******************** exitUsage *****************************
    void exitUsage(int iArg, char *pszMessage, char *pszDiagnosticInfo)
Purpose:
    In general, this routine optionally prints error messages and diagnostics.
    It also prints usage information.

    If this is an argument error (iArg >= 0), it prints a formatted message
    showing which argument was in error, the specified message, and
    supplemental diagnostic information.  It also shows the usage. It exits
    with ERR_COMMAND_LINE.

    If this is a usage error (but not specific to the argument), it prints
    the specific message and its supplemental diagnostic information.  It
    also shows the usage and exist with ERR_COMMAND_LINE.

    If this is just asking for usage (iArg will be -1), the usage is shown.
    It exits with USAGE_ONLY.
Parameters:
    I int iArg                      command argument subscript or control:
                                    > 0 - command argument subscript
                                    0 - USAGE_ONLY - show usage only
                                    -1 - USAGE_ERR - show message and usage
    I char *pszMessage              error message to print
    I char *pszDiagnosticInfo       supplemental diagnostic information
Notes:
    This routine causes the program to exit.
**************************************************************************/
void exitUsage(int iArg, char *pszMessage, char *pszDiagnosticInfo)
{
    switch (iArg)
    {
        case USAGE_ERR:
            fprintf(stderr, "Error: %s %s\n"
                    , pszMessage
                    , pszDiagnosticInfo);
            break;
        case USAGE_ONLY:
            break;
        default:
            fprintf(stderr, "Error: bad argument #%d.  %s %s\n"
                    , iArg
                    , pszMessage
                    , pszDiagnosticInfo);
    }
    // print the usage information for any type of command line error
    fprintf(stderr, "p2 -c courseFileName -q queryFileName\n");
    if (iArg == USAGE_ONLY)
        exit(USAGE_ONLY);
    else
        exit(ERR_COMMAND_LINE);
}
