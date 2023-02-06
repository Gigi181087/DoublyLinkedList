#ifndef _DOUBLYLINKEDLIST_H
#define _DOUBLYLINKEDLIST_H

// Errorcodes
#define DLLIST_NOERROR                 0
#define DLLIST_INDEXOUTOFRANGE         1
#define DLLIST_LISTISEMPTY             2
#define DLLIST_ALLOCATINGFAILED        3
#define DLLIST_LISTNOTINITIALIZED      4
#define DLLIST_LISTALREADYINITIALIZED  5
#define DLLIST_UNSPECIFIED             INT_MAX

#include <stdio.h>
#include <malloc.h>
#include <Windows.h>

typedef struct dlList dlList_t;

// Konstruktor
/// <summary>
/// Initializes a double chained list
/// </summary>
/// <param name="list">List to be initialized</param>
/// <returns>0 if initialized successfully, otherwise use DCLGetLastError() to retreive Errorcode</returns>
int DLList_Init(dcList_t**);

// Destruktor
/// <summary>
/// frees the allocated space of the list and all contained elements
/// </summary>
/// <param name="list">List to be destroyed</param>
/// <returns>0 if initialized successfully, otherwise use DCLGetLastError() to retreive Errorcode</returns>
int DLList_Destroy(dcList**);

/// <summary>
/// Counts the elements contained in a list
/// </summary>
/// <param name="list"></param>
/// <returns></returns>
int DLList_Count(dlList_t*);
int DLList_GetLength(dlList_t*);

// Cursor Operations to move through the list
/// <summary>
/// Set the cursor to the previous element of the list
/// </summary>
/// <param name="list">List on which the operations should be performed</param>
/// <returns>0 if cursor was moved successfully, otherwise use DCLGetLastError() to retreive Errorcode</returns>
int DLList_Prev(dlList_t*);
/// <summary>
/// Set the cursor to the next element of the list
/// </summary>
/// <param name="list">List on which the operations should be performed</param>
/// <returns>0 if cursor was moved successfully, otherwise use DCLGetLastError() to retreive Errorcode</returns>
int DLList_Next(dlList_t*);
/// <summary>
/// Set the cursor to the first element of the list
/// </summary>
/// <param name="list">List on which the operations should be performed</param>
/// <returns>0 if cursor was moved successfully, otherwise use DCLGetLastError() to retreive Errorcode</returns>
int DLList_SetCursorToBegin(dlList_t*);
/// <summary>
/// Set the cursor to the last element of the list
/// </summary>
/// <param name="list">List on which the operations should be performed</param>
/// <returns>0 if cursor was moved successfully, otherwise use DCLGetLastError() to retreive Errorcode</returns>
int DLList_SetCursorToEnd(dlList_t*);

int DLList_SetCursorToPosition(dlList_t*, int);


int GetData(dcList_t*, void**);
int DCL_GetDataFromIndex(dcList_t**, void*, int);
int DCL_InsertBefore(dcList_t*, void**);
int DCL_InsertAfter(dcList_t*, void**);
int DCL_GetLength(dcList_t*);

// Error Handling
int DCL_GetLastError(void);

/// <summary>
/// Transforms an errorcode of a dc-list to a human readable format
/// </summary>
/// <param errorcode="errorcode"></param>
/// <returns>String representation of errorcode</returns>
const char* DCLErrorToString(int errorCode);

int DLList_Concat(dlList_t*, dlList_t*);

int DLList_Split(dlList_t*, dlList_t*, int);

#endif // _DOUBLYLINKEDLIST_H
