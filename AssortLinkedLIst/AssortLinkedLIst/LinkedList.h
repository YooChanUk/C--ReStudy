#include<iostream>

typedef struct _tagNode
{
	int iData;
	struct _tagNode* pNextNode;

}tNode;

typedef struct _tagList
{
	tNode* pHeadNode;
	int iCount;
}tLinkedList;

//연결리스트 초기화
void InitList(tLinkedList* _pList);

//리스트 데이터 추가
void PushBack(tLinkedList* _pList,int _iData);
void PushFront(tLinkedList* _pList, int _iData);

void ReleaseList(tLinkedList* _pList);