#include "LinkedList.h"

int main()
{
	tLinkedList list = {};

	InitList(&list);

	PushBack(&list, 100);
	PushFront(&list, 200);
	PushBack(&list, 300);
	PushFront(&list, 400);
	PushFront(&list, 500);

	ReleaseList(&list);

	return 0;
}