#include "doublyLinkedList.h"

void DLList_MoveBefore(knot_t* knot) {
    knot->prev->next = knot->next;
    knot->next = knot->prev;
    knot->prev = knot->next->prev;
    knot->next->prev = knot;

    return;
}

void DLList_MoveAfter(knot_t* knot) {
    return;
}