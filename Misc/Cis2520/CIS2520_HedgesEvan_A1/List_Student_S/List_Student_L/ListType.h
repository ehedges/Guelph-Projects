#include "StudentInterface.h"
typedef Student Item;

#define MAXLISTSIZE 4
typedef struct ListNodeTag {
	Item items;
	struct ListNodeTag *nextNode;
} ListNode;

typedef struct {

    int size;
    ListNode * first;

} List;