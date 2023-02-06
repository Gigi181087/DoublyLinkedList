#include "doubleChainedList.h"

struct knot {
    knot_t* prev;
    knot_t* next;
    void** data;
};

struct dcList {
    knot_t* socket;
    knot_t* curr;
    int len;
};

static int lastError;

int DCL_Init(dcList_t** list) {
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

int DCL_Destroy(dcList_t** list) {
    SetCursorToBegin(*list);
    while (DCL_Next(*list) != -1) {
        DCL_Remove(*list);
    }
    free(*list);
    return 0;
}

int DCL_Next(dcList_t* list) {
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

int DCL_Prev(dcList_t* list) {
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

int SetCursorToBegin(dcList_t* list) {
    if (DCLIsInitializedAndNotEmpty(list)) {
        return -1;
    }
    list->curr = list->socket->next;

    return 0;
}

int SetCursorToEnd(dcList_t* list) {
    if (!DCLIsInitializedAndNotEmpty(list)) {
        return -1;
    }
    list->curr = list->socket->prev;

    return 0;
}

int SetCursorToIndex(dcList_t* list, int index) {
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

int GetData(dcList_t* list, void** data) {
    if (!DCLIsInitialized(list)) {
        return -1;
    }
    *data = list->curr->data;
    
    return 0;
}

int GetDataFromIndex(dcList_t** list, void* data, int index) {
    knot_t* buff = (*list)->curr;
    if (!SetCursorToIndex(list, index)) {
        return -1;
    }
    data = (*list)->curr->data;
    (*list)->curr = buff;

    return 0;
}

int InsertAfter(dcList_t* list, void** data) {
    if (!DCLIsInitialized(list)) {
        lastError = LISTNOTINITIALIZED;
        return -1;
    }
    knot_t* newKnot = (knot_t*)malloc(sizeof(knot_t));
    if (newKnot == NULL) {
        lastError = ALLOCATINGFAILED;
        return -1;
    }
    newKnot->data = (*data);
    newKnot->prev = list->curr;
    newKnot->next = list->curr->next;
    list->curr->next->prev = newKnot;
    list->curr->next = newKnot;
    list->curr = newKnot;

    return 0;
}

int InsertBefore(dcList_t** list, void* data) {

    return 0;
}

int DCL_GetLastError(void) {
    int output = lastError;
    lastError = 0;

    return output;
}

const char* DCL_ErrorToString(int errorcode) {
    switch (errorcode) {
    case NOERROR:
        return ("No error! (%d)" , errorcode);
    case 1:
        return ("Provided index was out of range! (%d)", errorcode);
    case 2:
        return "List is empty! (2)";
    case 3: 
        return "Allocating failed! (3)";
    case SEM_WAIT_ABANDONED:
        return "The specified object is a mutex object that was not released by the thread that owned the mutex object before the owning thread terminated. Ownership of the mutex object is granted to the calling thread and the mutex state is set to nonsignaled. If the mutex was protecting persistent state information, you should check it for consistency. (20)";
    case WAIT_TIMEOUT:
        return "The time-out interval elapsed, and the object's state is nonsignaled. (22)";
    case SEM_WAIT_FAILED:
        return "The function has failed. To get extended error information, call GetLastError. (23)";
    default:
        return ("Unknown error! (%d)", errorcode);
    }
}

int DCLIsNotEmpty(dcList_t** list) {
    if ((*list)->socket->next == (*list)->socket) {
        return 0;
    } else {
        return 1;
    }
}

int DCLIsInitialized(dcList_t** list) {
    if ((*list)->curr == NULL) {
        return 0;
    }
    else {
        return 1;
    }
}

int DCLIsInitializedAndNotEmpty(dcList_t** list) {
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
}

DCL_GetLength(dcList_t* list) {
    if (DCLIsInitialized(list)) {
        return list->len;
    }
    else {
        lastError = LISTNOTINITIALIZED;
        return -1;
    }
}
