/****************************************************************
 cs2123p6Driver.c by Caleb Barnwell

 Purpose:
     The driver file for Program 6. Loops through the input file
     and calls necessary functions as designated by commands in
     the input file.

 Input:
    I File pFile (p6ExtraV1.txt)

 ****************************************************************/

#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include "cs2123p6.h"

 int main(int argc, char *argv[])
 {
     Graph graph = newGraph(); // Create our graph

     // Call our "backbone" function
     readData(graph);

     freeGraph(graph); // free our graph

     return 0; // classic vlasic
 }


/************************** readData ******************************************
void readData(Graph graph)

Purpose:
    Reads in p5Input.txt. Uses getToken and sscanf to read in commands and
    calls appropriate functions. This function is the backbone of Program 6.

Parameters:
    I   Graph graph      graph

**************************************************************************/
void readData(Graph graph)
{
    // Necessary declarations
    char szInputBuffer[MAX_LINE_SIZE], szType[MAX_TOKEN], szCourseId[MAX_TOKEN], szLastId[MAX_TOKEN], szCourseName[23], szComment[MAX_LINE_SIZE];
    char * pszRemainingBuffer = NULL;
    int iScanfCnt, iMax;
    int pathM[MAX_VERTICES];
    Plan plan = newPlan();

    // Open our command file
    FILE * pFile = fopen("p6ExtraV1.txt", "r");
    // Check if it is found
    if(pFile == NULL)
        ErrExit(ERR_COMMAND_LINE, "Please have the file p5Input.txt in the same directory as the program. p5Input.txt not found.");

    // Begin Looping through the file
    while(fgets(szInputBuffer, MAX_LINE_SIZE-1, pFile))
    {
        // Gather our first command
        pszRemainingBuffer = getToken(szInputBuffer, szType, MAX_TOKEN-1);

        /***********
         * COURSE
         *********** */
        if(strcmp(szType,"COURSE")==0) {
            // Gather course id and name
            iScanfCnt = sscanf(pszRemainingBuffer, "%7s %20[^\n]\n", szCourseId, szCourseName);
            if(iScanfCnt < 2)
                ErrExit(ERR_COMMAND_LINE, "Not Enough Arguments for COURSE");

            // Print given command
            printf(">> COURSE %s %s\n", szCourseId, szCourseName);

            //insert course
            insertCourse(graph, szCourseId, szCourseName);
            strcpy(szLastId, szCourseId); // Remember our course in case the next command is for a prereq
        }

        /***********
         * PREREQ
         *********** */
        else if(strcmp(szType,"PREREQ")==0) {
            // Gather our course id
            pszRemainingBuffer = getToken(pszRemainingBuffer, szCourseId, MAX_TOKEN-1);

            // Print given command
            printf(">> PREREQ %s\n", szCourseId);

            // Check to see if it exists
            if(findCourse(graph, szCourseId)==-1)
            {
              printf("Course %s not found. Inserting with name TBD...\n", szCourseId);
              insertCourse(graph, szCourseId, "TBD");
            }

            // Add given course as a prereq to the last added course
            newPreEdgeNode(graph, graph->vertexM[findCourse(graph, szLastId)].prereqList, findCourse(graph, szCourseId), findCourse(graph, szLastId));
            // Add last added course as a successor to given course
            newSuccEdgeNode(graph, graph->vertexM[findCourse(graph, szCourseId)].successorList, findCourse(graph, szCourseId), findCourse(graph, szLastId));
        }

        /***********
         * PRTONE
         *********** */
        else if(strcmp(szType, "PRTONE")==0){
            pszRemainingBuffer = getToken(pszRemainingBuffer, szCourseId, MAX_TOKEN-1); // gather course id

            // Print command
            printf(">> PRTONE %s\n", szCourseId);
            printOne(graph, findCourse(graph, szCourseId), FALSE); // Call printOne
        }

        /***********
         * PRTSUCC
         *********** */
        else if(strcmp(szType, "PRTSUCC")==0){
            pszRemainingBuffer = getToken(pszRemainingBuffer, szCourseId, MAX_TOKEN-1); // gather course id

            // Print command
            printf(">> PRTSUCC %s\n", szCourseId);
            printSuccessors(graph,findCourse(graph, szCourseId));
        }

        /***********
         * PRTALL
         *********** */
        else if(strcmp(szType, "PRTALL")==0){
            printf(">> PRTALL\n"); // Print command
            printAllInList(graph);
        }

        /***********
         * MAXCHAIN
         *********** */
        else if(strcmp(szType, "MAXCHAIN")==0){
            pszRemainingBuffer = getToken(pszRemainingBuffer, szCourseId, MAX_TOKEN-1); // gather course id
            printf(">> MAXCHAIN %s\n", szCourseId); // Print command

            iMax = maxChain(graph, findCourse(graph, szCourseId)); // call maxchain and find value
            printf("Maximum chain for %s contains %d courses.\n", szCourseId, iMax); // Print out result
        }

        /***********
         * PRTLONGS
         *********** */
        else if(strcmp(szType, "PRTLONGS")==0){
            pszRemainingBuffer = getToken(pszRemainingBuffer, szCourseId, MAX_TOKEN-1); // gather course id
            printf(">> PRTLONGS %s\n", szCourseId); // Print command
            int iLongLength = maxChain(graph, findCourse(graph,szCourseId));
            printf("Longest chain for %s contains:\n" , graph->vertexM[findCourse(graph,szCourseId)].szCourseId);
            printLongChains(graph,findCourse(graph,szCourseId),pathM,0,iLongLength);
        }

        /***********
         * PRTSINKS
         *********** */
        else if(strcmp(szType, "PRTSINKS")==0){
            printf(">> PRTSINKS\n"); // Print command
            printSinks(graph);
        }

        /***********
         * PRTSOURCES
         *********** */
        else if(strcmp(szType, "PRTSOURCES")==0){
            printf(">> PRTSOURCES\n"); // Print command
            printSources(graph);
        }

        /***********
         * PLAN
         *********** */
        else if(strcmp(szType, "PLAN")==0){
            iScanfCnt = sscanf(pszRemainingBuffer, "%7s\n", szCourseId);
            if(iScanfCnt < 1)
                ErrExit(ERR_COMMAND_LINE, "Not Enough Arguments for PLAN");

            printf(">> PLAN %s\n", szCourseId); // Print command
            plan->bIncludeM[findCourse(graph, szCourseId)] = TRUE;
        }

        /***********
         * DOPLAN
         *********** */
        else if(strcmp(szType, "DOPLAN")==0){
            printf(">> DOPLAN\n"); // Print command
            doPlan(graph, plan);
        }

        /***********
         * PRTHASH
         *********** */
        else if(strcmp(szType, "PRTHASH")==0){
            printf(">> PRTHASH\n"); // Print command
            //printtHash(graph);
        }

        /***********
         * DELETE
         *********** */
        else if(strcmp(szType, "DELETE")==0){
            iScanfCnt = sscanf(pszRemainingBuffer, "%7[^\n]\n", szCourseId);
            if(iScanfCnt < 1)
                ErrExit(ERR_COMMAND_LINE, "Not Enough Arguments for DELETE");
            printf(">> DELETE %s\n", szCourseId); // Print command

            deleteCourse(graph, findCourse(graph, szCourseId));
        }

        /***********
         * HALT
         *********** */
        else if(strcmp(szType, "HALT")==0){
            // I have no clue what this is supposed to do...
        }

        /***********
         * COMMENTS
         *********** */
        else if(strcmp(szType, "*")==0){
            sscanf(szInputBuffer, "%[^\n]\n", szComment);

            // Print out comment
            printf(">> %s\n", szComment);
        }

        /***********
         * Blanks
         *********** */
        else if(strcmp(szType, "")==0){
            //Just move on
            continue;
        }

        // Unknown command given
        else{
            ErrExit(ERR_COMMAND_LINE, "Delegated command %s unknown.", szType);
        }
    }

    freePlan(plan);

    //Close our file
    fclose(pFile);
}

/**************************
Start Plan Funcs
**************************/

/************************** newPlan ******************************************
Graph newPlan()

Purpose:
    Allocates and returns a plan

Returns:
    Plan plan

**************************************************************************/
Plan newPlan()
{
    int i, j;
    Plan plan;

    plan = (Plan)malloc(sizeof(PlanImp)); // Allocate memory for our graph

    // Check if no space available
    if(plan == NULL)
        ErrExit(ERR_ALGORITHM, "No available memory for plan");

    // Initialize plan values to FALSE
    for(i = 0; i < MAX_VERTICES; i++){
        plan->bIncludeM[i] = FALSE;
    }

    // Initialize plan values to FALSE
    for(i = 0; i < MAX_VERTICES; i++){
        for(j = 0; j < 5; j++) {
            plan->semesterM[j][i] = -1;
        }
    }

    return plan;
}

/************************** freePlan ******************************************
void freePlan()

Purpose:
    frees a plan's memory

Parameters:
    I Plan plan

**************************************************************************/
void freePlan(Plan plan)
{
    free(plan);
}

/**************************
End Plan Funcs
**************************/

/**************************
Start Graph Funcs
**************************/

/************************** newGraph ******************************************
Graph newGraph()

Purpose:
    Allocates and returns a graph

Returns:
    Graph graph

**************************************************************************/
Graph newGraph()
{
    Graph graph;

    graph = (Graph)malloc(sizeof(GraphImp)); // Allocate memory for our graph

    // Check if no space available
    if(graph == NULL)
        ErrExit(ERR_ALGORITHM, "No available memory for Graph");

    // Initialize graph values
    graph->iNumVertices = 0;

    return graph;
}

/************************** freeGraph ******************************************
void freeGraph()

Purpose:
    frees a graph's memory

Parameters:
    I Graph graph

**************************************************************************/
void freeGraph(Graph graph)
{
    free(graph);
}

/************************** newVertex ******************************************
Vertex * newVertex(char szCourseName[], char szCourseID[])

Purpose:
    Assigns vertex values, allocates its lists, and returns a vertex.

Parameters:
    I   char szCourseName[]
    I   char szCourseId[]

Returns:
    Vertex vertex

**************************************************************************/
Vertex newVertex(char szCourseName[], char szCourseId[])
{
    Vertex vertex; // Declaration

    //Initialize values
    strcpy(vertex.szCourseId, szCourseId);
    strcpy(vertex.szCourseName, szCourseName);
    strcpy(vertex.szDept, "");
    vertex.prereqList = allocateEdgeNode(); // Allocate prereqList
    vertex.successorList = allocateEdgeNode(); // Allocate succList
    vertex.iSemesterLevel = -1;
    vertex.iHashChainNext = -1;
    vertex.iDistSource = -1;
    vertex.bExists = TRUE;

    return vertex;
}

/************************** allocateEdgeNode ******************************************
Vertex * allocateEdgeNode(char szCourseName[], char szCourseID[])

Purpose:
    Allocates, initializes, and returns an edgeNode

Parameters:
    I   char szCourseName[]
    I   char szCourseId[]

Returns:
    EdgeNode pEdge

Notes:
    Initializes iPrereqVertex and iSuccVertex to -1 (Nonexistent)
**************************************************************************/
EdgeNode * allocateEdgeNode()
{
    // Allocate memory
    EdgeNode *pEdge = (EdgeNode *)malloc(sizeof(EdgeNode));
    if(pEdge == NULL) // Check if NULL
        ErrExit(ERR_ALGORITHM, "No available memory for Edge Node");

    // Initialize edge values
    pEdge->iPrereqVertex = -1;
    pEdge->iSuccVertex = -1;
    pEdge->pNextEdge = NULL;

    return pEdge;
}

/******************** newPreEdgeNode ****************************
EdgeNode * newPreEdgeNode(Graph graph, EdgeNode * list, int iPrereqVertex, int iSuccVertex)

 Purpose:
    Used for creation of a Prereq, specifically the prereqList portion.
    Creates a newEdgeNode if it doesn't
    cause a Cycle. Initializes to given values.

 Parameters:
    I Graph graph
    I EdgeNode * list       list node of a vector
    I int iPrereqVertex
    I int iSuccVertex
 Returns:
    EdgeNode * pNew or EdgeNode * list
 *****************************************************************/
EdgeNode * newPreEdgeNode(Graph graph, EdgeNode * list, int iPrereqVertex, int iSuccVertex)
{
    // Declarations
    EdgeNode *p, *pPrecedes, *pNew;

    // Ensure it will not cause a cycle
    if(causesCycle(graph, iPrereqVertex, iSuccVertex)) {
        printf("Error: Prereq would cause a cycle\n");
        return NULL;
    }

    // Check if we are at the head of a list
    if(list->iPrereqVertex == -1 || list->iSuccVertex == -1)
    {
        list->iPrereqVertex = iPrereqVertex;
        list->iSuccVertex = iSuccVertex;
        return list;
    }

    // Initialize pPrecedes
    pPrecedes = NULL;

    // Go to the end of our list
    for(p = list; p!=NULL; p=p->pNextEdge)
    {
        pPrecedes = p;
    }

    // Allocate our new edge and initialize values
    pNew = allocateEdgeNode();
    pNew->iPrereqVertex = iPrereqVertex;
    pNew->iSuccVertex = iSuccVertex;
    if(pPrecedes != NULL)
        pPrecedes->pNextEdge = pNew;

    return pNew;
}

/******************** newSuccEdgeNode ****************************
EdgeNode * newSuccEdgeNode(Graph graph, EdgeNode * list, int iPrereqVertex, int iSuccVertex)

 Purpose:
    Used for creation of a Prereq, specifically the successorList portion.
    Creates a newEdgeNode if it doesn't
    cause a Cycle. Initializes to given values.

 Parameters:
    I Graph graph
    I EdgeNode * list       list node of a vector
    I int iPrereqVertex
    I int iSuccVertex
 Returns:
    EdgeNode * pNew or EdgeNode * list
 *****************************************************************/
EdgeNode * newSuccEdgeNode(Graph graph, EdgeNode * list, int iPrereqVertex, int iSuccVertex)
{
    // Declarations
    EdgeNode *pNew = allocateEdgeNode();
    EdgeNode *p;

    // Ensure it will not cause a cycle
    if(causesCycle(graph, iPrereqVertex, iSuccVertex)) {
        printf("Error: Prereq would cause a cycle\n");
        return NULL;
    }

    // Initializing the new edges to the passed in values
    pNew->iPrereqVertex = iPrereqVertex;
    pNew->iSuccVertex = iSuccVertex;

    // Update the successorList of the prereq vertex
    p = graph->vertexM[iPrereqVertex].successorList;
    graph->vertexM[iPrereqVertex].successorList = pNew;
    pNew->pNextEdge = p;

    return list;
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
