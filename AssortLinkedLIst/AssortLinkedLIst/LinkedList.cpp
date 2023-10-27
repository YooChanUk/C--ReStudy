#include "LinkedList.h"

void InitList(tLinkedList* _pList)
{
	_pList->pHeadNode = nullptr;
	_pList->iCount = 0;
}

void PushBack(tLinkedList* _pList, int _iData)
{
	tNode* pNode = (tNode*)malloc(sizeof(tNode));

	//�̹� ��� ���� �ּҿ� �����Ϳ� �����͸� ����ְ� �̹��� ������ ����ּ��̱⿡ �������͸� ����ִ´�.
	pNode->iData = _iData;
	pNode->pNextNode = nullptr;

	//���ʵ��������� �ƴ��� �Ǻ�
	if (0 == _pList->iCount)
	{
		//�̹� �����Ͱ� ���ʷ� ���� �����Ͷ�� ī��Ʈ�� 0�ϰ��̴�. �׷��Ƿ� ó���ּҴ�
		//������ �����س��� pNode <- �����͸� �����ѳ���ּ��̴�. �̹� pNode�� ó�� ����ּҷ� ���ԵǸ�
		_pList->pHeadNode = pNode;
	}
	else
	{
		//���� ���ʵ����Ͱ� �ƴ϶�� 
		//pCurFinalNode�� ��������� �����Ͽ� �־���´�.
		tNode* pCurFinalNode = _pList->pHeadNode;


		//���� pCurFinalNode->NextNode�� nullptr(0) �� �ƴ϶�� True�̱⿡ FinalNode���� ��� NextNode(�ּ�)�� ã�Ƶ���.
		//�ּҰ� ���°��� �ٴٸ��� �̹� ��尡 �������̶�� �Ҹ��̴�.
		while (pCurFinalNode->pNextNode)
		{
			pCurFinalNode = pCurFinalNode->pNextNode;
		}

		//��������忡 �ٴٸ��� �̹��� ����� pNode�����͸� �����ּҷ� �������ش�.
		pCurFinalNode->pNextNode = pNode;
		
	}
	//��� �����̳����� �ᱹ�� �����Ͱ� ���Դٴ� �̾߱��̱⿡ Count �ϳ��� ���Ѵ�.
	++_pList->iCount;
}

void PushFront(tLinkedList* _pList, int _iData)
{
	//1.Ǫ������Ʈ�� ���������� �����Ͽ� ī��Ʈ�� ���� �ö󰣴�.
	//2.Ǫ������ ���� ������ -> �������� ��� -> �������� ��� ��������
	//3.Ǫ������Ʈ�� ������ -> ������������� -> �������� ������� ������ �Ųٷμ��̴�.
	//4.�׷��⿡ ������ �������δ� �������� ������ ��尡 �����带 �������ϸ�
	//5. ������������ ���� ������ ������ ����� �ּҰ��� �������Ѵ�.
	//ex) Ǫ���� ��� -> 1 -> 2 -> 3 -> 4 -> 5 ������ �ڿ� �ٴ´�
	//��� , 3 , 2. 1

	tNode* pNode = (tNode*)malloc(sizeof(tNode));

	//�̹� ��� ���� �ּҿ� �����Ϳ� �����͸� ����ְ� �׻� �������� ���� ���� ����ּ� ������ ��ġ�Ͽ��� �ϱ⶧����
	//�̹� ���� �������� �ڸ� �մ´�.
	//����. �ٷ� �����带 �־������ ������ ���� ��尡 �����带 �޾ƿö� ������ �ٷ� �޾ƿ��⶧����
	//������� �ڿ� �����ؾ��Ѵ�.
	pNode->iData = _iData;

	//���ʵ��������� �ƴ��� �Ǻ�
	if (0 == _pList->iCount)
	{
		//���� �̹� ��尡 ó�� ������ ����� ���� �ּҰ��� ���⶧���� �η� �����Ѵ�.
		//���� �̹� ��尡 ������ ���� ������� �̹� ����� �ּ��̴�.
		_pList->pHeadNode = pNode;
		pNode->pNextNode = nullptr;
	}
	else
	{
		//���� �����Ͱ� �ϳ��� �ƴ϶�� 
		//pCurFinalNode�� ��������� �����Ͽ� �־���´�.
		//
		//�̹��� ������� ���� ������ �����尡 �̹� �����ߴٴ� �����Ͽ� ����������Ѵ�.
		// 
		//�׷��⿡ �̹���尡 �����带 ��ü�ؾ��ϸ�
		//���� ������� �� ���� nextNode�� ��ġ�� �̵��ؾ��Ѵ�.
		tNode* pCurFinalNode = _pList->pHeadNode;
		//ó���� �ƴϱ⶧���� �̹������ �������� ������ ������� ��忩���Ѵ�.
		pNode->pNextNode = pCurFinalNode;
		//���� ������� ��ü�Ǿ��Ѵ�.
		//�̹��� ������ ��忩���Ѵ�.
		_pList->pHeadNode = pNode;

	}
	//��� �����̳����� �ᱹ�� �����Ͱ� ���Դٴ� �̾߱��̱⿡ Count �ϳ��� ���Ѵ�.
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
