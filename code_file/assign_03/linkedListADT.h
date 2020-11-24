#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

//List ADT Type Definitions
typedef struct node{
    void* dataPtr;
    struct node* link;
}NODE;

typedef struct{
    int count;
    NODE* pos;
    NODE* head;
    NODE* rear;
    int (*compare) (void* argu1, void* argu2);
}LIST;

//Prototype Declarations
LIST* createList (int (*compare) (void* argu1, void* argu2));
LIST* destroyList (LIST* list);

int addNode (LIST* pList, void* dataInPtr);
bool removeNode (LIST* pList, void* keyPtr, void** pDataOut);
bool searchList (LIST* pList, void* pArgu, void** pDataOut);
static bool retrieveNode(LIST* pList, void* pArgu, void** dataOutPtr);
bool traverse (LIST* pList, int fromWhere, void** dataOutPtr);
int listCount (LIST* pList);
bool emptyList (LIST* pList);
bool fullList (LIST* pList);

static bool _insert (LIST* pList, NODE* pPre, void* dataInPtr);
static void _delete (LIST* pList, NODE* pPre, NODE* pLoc, void* dataOutPtr);
static bool _search (LIST* pList, NODE** pPre, NODE** pLoc, void* pArgu);
//End of List ADT Definitions

//Create List
LIST* createList (int (*compare) (void* argu1, void* argu2)){
    //Local Definitions
    LIST* list;

    //Statements
    list=(LIST*) malloc (sizeof(LIST));
    if(list){
        list -> head = NULL;
        list -> pos = NULL;
        list -> rear = NULL;
        list -> count = 0;
        list -> compare = compare;
    }
    return list;
}

//Add Node
int addNode(LIST* pList, void* dataInPtr){
    //Local Definitions
    bool found, success;
    NODE* pPre;
    NODE* pLoc;

    //Statements
    found=_search(pList, &pPre, &pLoc, dataInPtr);
    if(found) return (+1);

    success=_insert(pList, pPre, dataInPtr);
    if(!success) return (-1);//Overflow
    return (0);
    }


//Internal Insert Function
static bool _insert (LIST* pList, NODE* pPre, void* dataInPtr){
    NODE* pNew;

    if(!(pNew=(NODE*) malloc (sizeof(NODE)))) return false;

    pNew -> dataPtr = dataInPtr;
    pNew -> link = NULL;

    if(pPre == NULL){
        pNew -> link = pList -> head;
        pList -> head = pNew;
        if(pList -> count == 0) pList -> rear = pNew;
    }
    else{
        pNew -> link = pPre -> link;
        pPre -> link = pNew;
        if(pNew -> link == NULL) pList -> rear = pNew;
    }
    (pList -> count)++;
    return true;
}

//Remove Node
bool removeNode (LIST* pList, void* keyPtr, void** dataOutPtr){

//Local Definitions bool found;
NODE* pPre; 
NODE* pLoc;
bool found;

//Statements
found = _search (pList, &pPre, &pLoc, keyPtr); 
if(found) _delete(pList, pPre, pLoc, dataOutPtr); 

return found;
} // removeNode


//Delete Function
void _delete(LIST* pList, NODE* pPre, NODE* pLoc, void** dataOutPtr){ 
//Statements
*dataOutPtr = pLoc->dataPtr; 
// Deleting first node
if (pPre == NULL) pList->head = pLoc->link;
// Deleting any other node
else pPre->link = pLoc->link;
// Test for deleting last node 
if (pLoc->link == NULL) pList->rear = pPre;

(pList->count)--; 
free (pLoc);
return; 
} // _delete

//searchList
bool searchList (LIST* pList, void* pArgu, void** pDataOut){
//Local Definitions bool found;
NODE* pPre; 
NODE* pLoc;
bool found;

//Statements
found = _search (pList, &pPre, &pLoc, pArgu); 
if (found) *pDataOut = pLoc->dataPtr; 
else *pDataOut = NULL;
return found; 
} // searchList


//search Function
bool _search (LIST* pList, NODE** pPre, NODE** pLoc, void* pArgu){
//Macro Definition 
#define COMPARE_LAST \
( ((* pList->compare) (pArgu, (*pLoc)->dataPtr)) )

//Local Definitions 
int result;
//Statements 
*pPre = NULL; 
*pLoc = pList->head; 
if (pList->count == 0) return false;

// Test for argument > last node in list 
if ( COMPARE_LAST > 0) {
    *pPre = pList->rear; 
    *pLoc = NULL; 
    return false; 
    } // if

while ( (result = COMPARE_LAST) > 0 ) {
// Have not found search argument location 
    *pPre = *pLoc;
    *pLoc = (*pLoc)->link; 
    } // while

if (result == 0)
// argument found--success 
    return true;
else return false; 
} // _search


//Retrieve Node
static bool retrieveNode(LIST* pList, void* pArgu, void** dataOutPtr){
//Local Definitions 
bool found;
NODE* pPre; 
NODE* pLoc;

//Statements
found = _search (pList, &pPre, &pLoc, pArgu); 
if (found) {
    *dataOutPtr = pLoc->dataPtr; 
    return true; 
    } // if
    
*dataOutPtr = NULL; 
return false;
} // retrieveNode


//Empty List
bool emptyList (LIST* pList) {
//Statements
return (pList->count == 0); 
} // emptyList


//Full List
bool fullList (LIST* pList) {
//Local Definitions 
NODE* temp;
//Statements
if ((temp = (NODE*)malloc(sizeof(*(pList->head))))) {
    free (temp); 
    return false; 
    } // if

// Dynamic memory full 
return true;
} // fullList


//List Count
int listCount(LIST* pList) {
//Statements 
return pList->count; 
} // listCount

//Traverse List
bool traverse (LIST* pList, int fromWhere, void** dataPtrOut){
//Statements
if (pList->count == 0) return false;
if (fromWhere == 0) {
// Start from first node 
    pList->pos = pList->head; 
    *dataPtrOut = pList->pos->dataPtr; 
    return true;
} // if fromwhere

else {
// Start from current position 
    if (pList->pos->link == NULL) return false;
    else {
        pList->pos = pList->pos->link; 
        *dataPtrOut = pList->pos->dataPtr;
        return true; 
        } // if else
    } // if fromwhere else 
} // traverse


//Destroy List
LIST* destroyList (LIST* pList) 
{//Local Definitions 
NODE* deletePtr;
//Statements 
if (pList) {
    while (pList->count > 0) {
        // First delete data 
        free (pList->head->dataPtr);
        // Now delete node 
        deletePtr = pList->head;
        pList->head = pList->head->link; 
        pList->count--; 
        free (deletePtr);
        } // while 
    free (pList); 
    } // if
return NULL; 
} // destroyList
