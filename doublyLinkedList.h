#ifndef _DOUBLYLINKEDLIST_H
#define _DOUBLYLINKEDLIST_H

// Errorcodes
#define NOERROR                 0
#define INDEXOUTOFRANGE         1
#define LISTISEMPTY             2
#define ALLOCATINGFAILED        3
#define LISTNOTINITIALIZED      4
#define LISTALREADYINITIALIZED  5
#define UNSPECIFIED             INT_MAX

#include <stdio.h>
#include <malloc.h>
#include <Windows.h>

typedef struct knot knot_t;
typedef struct dcList dcList_t;

/// <summary>
/// Initializes a double chained list
/// </summary>
/// <param name="list">List to be initialized</param>
/// <returns>0 if initialized successfully, otherwise use DCLGetLastError() to retreive Errorcode</returns>
int DCLInit(dcList_t**);

/// <summary>
/// Counts the elements contained in a list
/// </summary>
/// <param name=""></param>
/// <returns></returns>
int Count(dcList_t**, int*);
int SetCursorToBegin(dcList_t**);
int SetCursorToEnd(dcList_t**);
int GetData(dcList_t*, void**);
int DCL_GetDataFromIndex(dcList_t**, void*, int);
int DCL_InsertBefore(dcList_t*, void**);
int DCL_InsertAfter(dcList_t*, void**);
int DCL_GetLength(dcList_t*);

int DCL_GetLastError(void);

/// <summary>
/// Transforms an errorcode of a dc-list to a human readable format
/// </summary>
/// <param errorcode="errorcode"></param>
/// <returns>String representation of errorcode</returns>
const char* DCLErrorToString(int errorCode);

#endif // _DOUBLYLINKEDLIST_H
