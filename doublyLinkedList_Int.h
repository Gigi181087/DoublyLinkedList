#define ASSERT_INITIALIZEDANDNOTEMPTY(list) do { if (!DCLIsInitializedAndNotEmpty(list)) { return -1; }} while(0)
#define ASSERT_INITIALIZED(list) do { if (!DCL_IsInitialized) {lastError = LISTNOTINITIALIZED; return -1; }} while(0)

typedef struct node node_t;

void DLList_Int_MoveBefore(node_t*);

