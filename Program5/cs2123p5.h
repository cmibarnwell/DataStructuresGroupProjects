/**********************************************************************
cs2123p5.h by Caleb Barnwell, Brandon Lwowski, and Brandon Bell
Purpose:
    Defines constants:
        max constants
        error constants
        boolean constants

    Defines typedef for
        For Linked List
            NodeLL
            LinkedListImp
            LinkedList
        For Graph
            Vertex
            GraphImp
            Graph

 Protypes
        
Notes:

**********************************************************************/

/*** constants ***/
// Maximum constants
#define LINE_SIZE 50 //May need to change this value! -Caleb

// Error constants (program exit values)
#define ERR_COMMAND_LINE    900    // invalid command line argument
#define ERR_ALGORITHM       903    // Error in algorithm - almost anything else
#define ERR_BAD_INPUT       503    // Bad input

// boolean constants
#define FALSE 0
#define TRUE 1

// exitUsage control 
#define USAGE_ONLY          0      // user only requested usage information
#define USAGE_ERR           -1     // usage error, show message and usage information

// boolean constants
#define FALSE 0
#define TRUE 1

/* EOF */
#define REACHED_EOF 1

/*** typedef ***/
// typedefs for the Linked Lists, THE BELOW WILL BE NEEDING UPDATING AND MAY BE UNNECESSARY, I WILL FIX THIS SOON -Caleb
typedef struct
{
    //SOME DATA, FILL THIS SPOT LATER!!! -Caleb
    struct Node *pNext;
} NodeLL;
typedef struct
{
    NodeLL *pHead;
} LinkedListImp;

typedef LinkedListImp * LinkedList;

// typedefs for the Graphs
typedef struct
{
    int iVertex
    struct * EdgeNode *pNextEdge;
} EdgeNode;
typedef struct
{
    EdgeNode * predecessorList;
    char szLabel[LABEL_SIZE+1];
    EdgeNode * successorList;
} Vertex;


/********Utility Functions***********/
char * getToken(char *pszInputTxt, char szToken[], int iTokenSize);


/********Brandon B. Functions********/


/********Brandon L. Functions********/

/***********Caleb Functions**********/




