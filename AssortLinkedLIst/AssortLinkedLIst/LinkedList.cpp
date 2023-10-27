#include "LinkedList.h"

void InitList(tLinkedList* _pList)
{
	_pList->pHeadNode = nullptr;
	_pList->iCount = 0;
}

void PushBack(tLinkedList* _pList, int _iData)
{
	tNode* pNode = (tNode*)malloc(sizeof(tNode));

	//이번 노드 스택 주소에 데이터에 데이터를 집어넣고 이번게 마지막 노드주소이기에 널포인터를 집어넣는다.
	pNode->iData = _iData;
	pNode->pNextNode = nullptr;

	//최초데이터인지 아닌지 판별
	if (0 == _pList->iCount)
	{
		//이번 데이터가 최초로 들어온 데이터라면 카운트가 0일것이다. 그러므로 처음주소는
		//힙노드로 지정해놓은 pNode <- 데이터를 저장한노드주소이다. 이번 pNode가 처음 헤더주소로 들어가게되며
		_pList->pHeadNode = pNode;
	}
	else
	{
		//만약 최초데이터가 아니라면 
		//pCurFinalNode에 헤더노드부터 시작하여 넣어놓는다.
		tNode* pCurFinalNode = _pList->pHeadNode;


		//이후 pCurFinalNode->NextNode가 nullptr(0) 이 아니라면 True이기에 FinalNode까지 계속 NextNode(주소)를 찾아들어간다.
		//주소가 없는값에 다다르면 이번 노드가 마지막이라는 소리이다.
		while (pCurFinalNode->pNextNode)
		{
			pCurFinalNode = pCurFinalNode->pNextNode;
		}

		//마지막노드에 다다르면 이번에 저장된 pNode데이터를 다음주소로 지정해준다.
		pCurFinalNode->pNextNode = pNode;
		
	}
	//모든 과정이끝나면 결국은 데이터가 들어왔다는 이야기이기에 Count 하나를 더한다.
	++_pList->iCount;
}

void PushFront(tLinkedList* _pList, int _iData)
{
	//1.푸쉬프론트는 노드헤더에서 시작하여 카운트가 점점 올라간다.
	//2.푸쉬백의 경우는 헤더노드 -> 다음생성 노드 -> 다음생성 노드 순이지만
	//3.푸쉬프론트는 헤더노드 -> 마지막생성노드 -> 마지막전 생성노드 순으로 거꾸로순이다.
	//4.그렇기에 헤더노드 다음으로는 다음으로 생성된 노드가 헤더노드를 가져야하며
	//5. 마지막생성된 노드는 그전에 생성된 노드의 주소값을 가져야한다.
	//ex) 푸쉬백 헤더 -> 1 -> 2 -> 3 -> 4 -> 5 무조건 뒤에 붙는다
	//헤더 , 3 , 2. 1

	tNode* pNode = (tNode*)malloc(sizeof(tNode));

	//이번 노드 스택 주소에 데이터에 데이터를 집어넣고 항상 마지막에 들어온 노드는 헤더주소 다음에 위치하여야 하기때문에
	//이번 노드는 헤더노드의 뒤를 잇는다.
	//수정. 바로 헤더노드를 넣어놓으면 다음에 들어올 노드가 헤더노드를 받아올때 본인을 바로 받아오기때문에
	//헤더노드는 뒤에 설정해야한다.
	pNode->iData = _iData;

	//최초데이터인지 아닌지 판별
	if (0 == _pList->iCount)
	{
		//또한 이번 노드가 처음 최초의 노드라면 다음 주소값은 없기때문에 널로 설정한다.
		//또한 이번 노드가 최초의 노드면 헤더노드는 이번 노드의 주소이다.
		_pList->pHeadNode = pNode;
		pNode->pNextNode = nullptr;
	}
	else
	{
		//만약 데이터가 하나가 아니라면 
		//pCurFinalNode에 헤더노드부터 시작하여 넣어놓는다.
		//
		//이번에 만들어진 노드는 그전에 헤더노드가 이미 존재했다는 상정하에 만들어져야한다.
		// 
		//그렇기에 이번노드가 헤더노드를 대체해야하며
		//그전 헤더노드는 그 뒤의 nextNode의 위치로 이동해야한다.
		tNode* pCurFinalNode = _pList->pHeadNode;
		//처음게 아니기때문에 이번노드의 다음노드는 그전에 만들어진 노드여야한다.
		pNode->pNextNode = pCurFinalNode;
		//또한 헤더노드는 교체되야한다.
		//이번에 생성된 노드여야한다.
		_pList->pHeadNode = pNode;

	}
	//모든 과정이끝나면 결국은 데이터가 들어왔다는 이야기이기에 Count 하나를 더한다.
	++_pList->iCount;
}

void PushFront2(tLinkedList* _pList, int _iData)
{
	tNode* pNode = (tNode*)malloc(sizeof(tNode));
	pNode->iData = _iData;
	pNode->pNextNode = _pList->pHeadNode;

	_pList->pHeadNode = pNode;
		
	++_pList->iCount;
}



void Release(tNode* _pNode)
{
	if (nullptr == _pNode)
	{
		return;
	}
	Release(_pNode->pNextNode);

	free(_pNode);
}

void ReleaseList(tLinkedList* _pList)
{
	//Release(_pList->pHeadNode);

	tNode* pDeleteNode = _pList->pHeadNode;

	while (pDeleteNode)
	{
		tNode* pNext = pDeleteNode->pNextNode;
		free(pDeleteNode);
		pDeleteNode = pNext;
	}
}
