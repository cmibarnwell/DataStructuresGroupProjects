//--Internal Note (accelerate): I replaced the header file
//with this one since it is the one that Prof. Clark provided for us
//and has all of the necessary prototypes

/**********************************************************************
cs2123p5.h
Purpose:
   Defines constants: 
       max constants 
       error constants
       warning constants
       boolean constants
   Defines typedef for 
       EdgeNode  - graph edge containing preq and successor vertex
       Vertex    - contains course information (course number, name), existence boolean,
                   successor list first node pointer, predecessor list first node pointer
       GraphImp  - array of vertices and a count of them
       Graph     - pointer to an allocated GraphImp
       PlanImp   - tbd       
   Defines function prototypes for functions used in pgm5 (recursive and non-recursive)
   Defines function prototypes for functions used in pgm6 
   Defines WARNING macro
Notes:
   
**********************************************************************/
/*** constants ***/
#define MAX_TOKEN 50               // Maximum number of actual characters for a token
#define MAX_LINE_SIZE 100          // Maximum number of character per input line
#define MAX_VERTICES 70
// Error constants (program exit values)
#define ERR_COMMAND_LINE    900    // invalid command line argument
#define ERR_ALGORITHM      903     // Unexpected error in algorithm

#define ERR_TOO_MANY_COURSE 1      // Too many courses
#define ERR_BAD_COURSE 3           // Bad Course Data
#define ERR_BAD_PREREQ 4           // Bad Prereq Data
#define ERR_MISSING_SWITCH         "missing switch"
#define ERR_EXPECTED_SWITCH        "expected switch, found"
#define ERR_MISSING_ARGUMENT       "missing argument for"

// exitUsage control 
#define USAGE_ONLY          0      // user only requested usage information
#define USAGE_ERR           -1     // usage error, show message and usage information

// boolean constants
#define FALSE 0
#define TRUE 1

// EdgeNode represents one edge in a graph
typedef struct EdgeNode
{
    int iPrereqVertex;              // prereq
    int iSuccVertex;                // successor
    struct EdgeNode *pNextEdge;     // points to next  edge
} EdgeNode;

typedef struct Vertex
{
    char szCourseId[8];             // Course Identifier
    char szCourseName[21];          // Course Full Name
    char szDept[4];                 // Department (e.g., CS, MAT)
    int iLevel;                     // Specifies location within graph (For use with EdgeNode)
    int bExists;                    // pgm6 DELETE command causes this to be set to TRUE
                                    // TRUE - this vertex exists, FALSE - deleted
    EdgeNode * prereqList;
    EdgeNode * successorList;
    int iSemesterLevel;
    int iHashChainNext;             // pgm 6 extra credit
    int iDistSource;
} Vertex;

// GraphImp of a double adjacency list graph
typedef struct
{
    int iNumVertices;
    Vertex vertexM[MAX_VERTICES];
} GraphImp;

typedef GraphImp *Graph;

// Degree Plan

typedef struct
{
    int semesterM[5][MAX_VERTICES];
    int bIncludeM[MAX_VERTICES];
} PlanImp;
typedef PlanImp * Plan;

typedef struct
{
    int iPrimayMax ;            // Max subscript in the primary portion
                                // Any subscript higher is in overflow
} HashTable;

// Prototypes

/********** Brandon L. Funcs **************/

void printLongChains(Graph graph, int iVertex, int pathM[], int iLevel, int iLongLength);
void deleteCourse(Graph graph, int iVertex); //for program 6
int maxChain(Graph graph, int iVertex);
int insertCourse(Graph graph, char szCourseId[], char szCourseName[]);

/********** Caleb B. Funcs ****************/

void printSuccessors(Graph graph, EdgeNode * pEdge, int iIndent);
void printTraversal(Graph graph, int iCourseVertex, int indent);
void printSources(Graph graph);
void printSinks(Graph graph);
void doPlan(Graph graph, Plan plan); //for program 6
void printAllInList(Graph graph);
void printOne(Graph graph, int iVertex);
Vertex * allocateVertex(char szCourseName[], char szCourseId[]);
Graph newGraph();
EdgeNode * newEdgeNode(EdgeNode * list, int iPrereqVertex, int iSuccVertex);
Graph newGraph();
EdgeNode * allocateEdgeNode();
void printOne(Graph graph, int iVertex);
void readData(Graph graph);
void freeGraph(Graph graph);

/********** Brandon B. Funcs ***************/
int causesCycle(Graph graph, int iPrereqVertex, int iVertex);
int findCourse(Graph graph, char szCourseId[]);
void setLevel(Graph g, Plan plan, int iVertex, int iLev); //for program 6

//NOTE(accelerator): Put hash table functions here
//HashTable* createHashTable(int); //program 6

/****************Program 6 Functions and generic Functions below **********************/
//void insertCourse(Graph graph, int iCourseVertex);
//int maxChain(Graph graph, int iVertex); 
//void printTraversal(Graph graph, int iCourseVertex, int indent);
//void printLongChains(Graph graph, int iVertex, int pathM[], int iLevel, int iLongLength);
//int causesCycle(Graph graph, int iPrereqVertex, int iVertex);
//int findCourse(Graph graph, char szCourseId[]);
//void insertPrereq(Graph graph, int iPrereqVertex, int iCourseVertex);
//void printAllInList(Graph graph);
//void printSources(Graph graph);
//void deleteCourse (Graph graph, int iVertex);
//void doPlan(Graph graph, Plan plan);
//void setLevel(Graph g, Plan plan, int iVertex, int iLev);
Plan newPlan();

void insert(Graph, Vertex);

// functions in most programs, but require modifications
void processCommandSwitches(int argc, char *argv[], char **ppszCommandFileName);
void exitUsage(int iArg, char *pszMessage, char *pszDiagnosticInfo);

// Utility routines provided by Larry
void ErrExit(int iexitRC, char szFmt[], ...);
char * getToken(char *pszInputTxt, char szToken[], int iTokenSize);

/* 
  WARNING macro 
  Parameters:
     I szFmt - a printf format
     I ...   - a variable number of parameters corresponding to szFmt's
               format codes.
  Results:
     Prints "WARNING" and the value(s) specified by the szFmt.
  Notes:
     Since this generates multiple C statements, we surround them
     with a dummy do while(0) which only executes once.  Notice that the
     dummy do while isn't ended with a ";" since the user of 
     the macro naturally specifies a ";".  Example:
         if (x != 0)
             WARNING("X must be blah blah");
         else
         {   // normal processing
            ....
         } 
     If we used {} in the macro definition instead of the dummy do while(0),
     the generated code would have a bad ";":
         if (x != 0)
         {
             printf("\tWARNING: "); 
             printf("X must be blah blah");
             printf("\n");
         } ;  // yuck, bad ";" causing the compiler to not understand the else
         else
         {   // normal processing
            ....
         } 
*/
#define WARNING(szFmt, ...) do {    \
    printf("\tWARNING: ");          \
    printf(szFmt, __VA_ARGS__);     \
    printf("\n");                   \
    } while (0)
