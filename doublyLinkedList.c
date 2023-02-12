#include "doubleChainedList.h"

struct knot {
    knot_t* prev;
    knot_t* next;
    void** data;
};

struct dlList {
    knot_t* socket;
    knot_t* curr;
    int len;
};

typedef struct knot knot_t;

static int lastError;

// Konstruktor
int DLList_Init(dlList_t** list)      {
    if ((*list)->curr != NULL) {
        lastError = DLLIST_LISTALREADYINITIALIZED;
        return -1;
    }

    *list = (dcList_t*)malloc(sizeof(dcList_t));
    if (*list == NULL) {
        lastError = ALLOCATINGFAILED;
        return -1;
    }

    (*list)->socket = (knot_t*)malloc(sizeof(knot_t));
    if ((*list)->socket == NULL) {
        free(*list);
        lastError = ALLOCATINGFAILED;
        return -1;
    }

    (*list)->socket->prev = (*list)->socket;
    (*list)->socket->next = (*list)->socket;
    (*list)->socket->data = NULL;

    (*list)->curr = (*list)->socket;
    (*list)->len = 0;

    return 0;
}

// Destruktor
int DLList_Destroy(dcList_t** list) {
    SetCursorToBegin(*list);
    while (DLList_Next(*list) != -1) {
        DLList_Remove(*list);
    }
    free(*list);

    return 0;
}

// Cursor Operations to move through the list
int DLList_SetCursorToNext(dlList_t* list) {
    if (!DCL_IsInitialized) {
        lastError = LISTNOTINITIALIZED;
        return -1;
    }
    if (list->curr->next == list->socket) {
        lastError = INDEXOUTOFRANGE;
        return -1;
    }
    list->curr = list->curr->next;

    return 0;           
}

int DLList_SetCursorToPrev(dlList_t* list) {
    if (!DCL_IsInitialized) {
        lastError = LISTNOTINITIALIZED;
        return -1;
    }
    if (list->curr->prev == list->socket) {
        lastError = INDEXOUTOFRANGE;
        return -1;
    }
    list->curr = list->curr->prev;
    return 0;
}

int DLList_SetCursorToFirst(dlList_t* list) {
    if (DCLIsInitializedAndNotEmpty(list)) {
        return -1;
    }
    list->curr = list->socket->next;

    return 0;
}

int DLList_SetCursorToLast(dlList_t* list) {
    if (!DCLIsInitializedAndNotEmpty(list)) {
        return -1;
    }
    SetCursorToLast(list);

    return 0;
}

int DLList_SetCursorToIndex(dlList_t* list, int index) {
    if (!DCLIsInitializedAndNotEmpty(list)) {
        return -1;
    }
    knot_t* buff = list->socket;
    if (index < 0) {
        for (int i = 0; i > index; i--) {
            if (buff->prev == list->socket) {
                lastError = INDEXOUTOFRANGE;
                return -1;
            }
            else {
                buff = buff->prev;
            }
        }
    }
    else {
        for (int i = -1; i < index; i++) {
            if (buff->next == list->socket) {
                lastError = INDEXOUTOFRANGE;
                return -1;
            }
            else {
                buff = buff->next;
            }
        }
    }
    list->curr = buff;

    return 0;
}

int GetData(dlList_t* list, void** data) {
    if (!DCLIsInitialized(list)) {
        return -1;
    }
    *data = list->curr->data;
    
    return 0;
}

int GetDataFromIndex(dlList_t** list, void* data, int index) {
    knot_t* buff = (*list)->curr;
    if (!SetCursorToIndex(list, index)) {
        return -1;
    }
    data = (*list)->curr->data;
    (*list)->curr = buff;

    return 0;
}

// Insert data into list
int DLList_Add(dlList_t* list, void** data) {
    if (!DCLIsInitializedAndNotEmpty(list)) {
        return -1;
    }
    return DLList_Internal_InsertAfter(list->socket->prev, data);

}

int DLList_InsertAfter(dlList_t* list, void** data) {
    if (!DCLIsInitialized(list)) {
        lastError = LISTNOTINITIALIZED;
        return -1;
    }
    return DLList_Internal_InsertAfter(list->curr, data);
    /*knot_t* newKnot = (knot_t*)malloc(sizeof(knot_t));
    if (newKnot == NULL) {
        lastError = ALLOCATINGFAILED;
        return -1;
    }
    newKnot->data = *data;
    newKnot->prev = list->curr;
    newKnot->next = list->curr->next;
    list->curr->next->prev = newKnot;
    list->curr->next = newKnot;
    list->curr = newKnot;

    return 0;*/
}

int InsertBefore(dlList_t* list, void** data) {
    if (!DCLIsInitialized(list)) {
        lastError = LISTNOTINITIALIZED;
        return -1;
    }
    return DLList_Internal_InsertAfter(list->curr->prev, data);
}


int DLList_GetLength(dlList_t* list) {
    if (DCLIsInitialized(list)) {
        return list->len;
    }
    else {
        lastError = LISTNOTINITIALIZED;
        return -1;
    }
}

// Error handling
int DLList_GetLastError(void) {
    int output = lastError;
    lastError = 0;

    return output;
}

const char* DLList_ErrorToString(int errorcode) {
    switch (errorcode) {
    case NOERROR:
        return ("No error! (%d)" , errorcode);
    case 1:
        return ("Provided index was out of range! (%d)", errorcode);
    case 2:
        return "List is empty! (2)";
    case 3: 
        return "Allocating failed! (3)";
    default:
        return ("Unknown error! (%d)", errorcode);
    }
}


//  For internal use only
int DLList_IsNotEmpty(dcList_t* list) {
    if ((*list)->socket->next == (*list)->socket) {
        return 0;
    } else {
        return 1;
    }
}

int DLList_IsInitialized(dcList_t* list) {
    if ((*list)->curr == NULL) {
        return 0;
    }
    else {
        return 1;
    }
}

int DLList_IsInitializedAndNotEmpty(dcList_t* list) {
    if (!DCLIsInitialized(list)) {
        lastError = LISTNOTINITIALIZED;
        return -1;
    }
    if (!DCLIsNotEmpty(list)) {
        lastError = LISTISEMPTY;
        return -1;
    }

    return 0;
}
 /*
void DCL_SetSemError(DWORD error) {
    switch (error) {
    case WAIT_ABANDONED:
        lastError = SEM_WAIT_ABANDONED;
        break;
    case WAIT_TIMEOUT:
        lastError = SEM_WAIT_TIMEOUT;
        break;
    case WAIT_FAILED:
        lastError = SEM_WAIT_FAILED;
        break;
    default:
        lastError = UNSPECIFIED;
    }

    return;
}*/

// not needed?
int DCL_Count(dcList_t* list) {
    if ((*list)->curr == NULL) {
        lastError = LISTNOTINITIALIZED;

        return -1;
    }
    else {
        knot_t* buff = (*list)->socket;
        int counter = 0;
        while (buff->next != (*list)->socket) {
            buff = buff->next;
            counter++;
        }

        return counter;
    }
}

void SetCursorToLast(dlList_t* list) {
    list->curr = list->socket->prev;

    return;
}

void DLList_Internal_SetCursorToNext(dlList_t* list) {
    list->curr = list->curr->next;

    return;
}

int DLList_Internal_InsertAfter(knot_t* knot, void** data) {
    knot_t* newKnot = (knot_t*)malloc(sizeof(knot_t);
    if (newKnot == NULL) {
        lastError = DLLIST_ALLOCATINGFAILED;
        return -1;
    }

    newKnot->data = *data;
    newKnot->next = knot->next;
    newKnot->prev = knot;

    knot->next = newKnot;

    return 0;
}

