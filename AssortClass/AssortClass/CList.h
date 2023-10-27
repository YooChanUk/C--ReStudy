#pragma once
#include<iostream>

template<typename T>
struct Node
{
	T	  data;
	Node<T>* prevNode;
	Node<T>* nextNode;

	Node()
		:data()
		,prevNode(nullptr)
		,nextNode(nullptr)
	{

	}
	Node(const T& _data, Node<T>* _prev, Node<T>* _next)
		:data(_data)
		,prevNode(_prev)
		,nextNode(_next)
	{
	
	}
};

template<typename T>
class CList
{
private:
	Node<T>* headerNode;
	Node<T>* tailNode;
	int	  count;

public:
	void push_back(const T& _data);
	void push_front(const T& _data);



public:
	CList();
	~CList();


};

template<typename T>
CList<T>::CList()
	:headerNode(nullptr)
	,tailNode(nullptr)
	,count(0)
{

}

template<typename T>
CList<T>::~CList()
{
	Node<T>* deleteNode = headerNode;

	while (deleteNode)
	{
		Node<T>* next = deleteNode->nextNode;
		delete(deleteNode);
		deleteNode = next;
	}
}

template<typename T>
void CList<T>::push_back(const T& _data)
{
	Node<T>* newNode = new Node<T>(_data,nullptr,nullptr);
	
	if (nullptr == headerNode)
	{
		headerNode = newNode;
		tailNode = newNode;
	}
	else
	{
		//Ǫ������ ����ڿ��ִ� ��忡 �پ���Ѵ�. �׷��⿡ ���ϳ���� ������ �ٲٸ� �ȴ�. ���������ؼ� �ؽ�Ʈ��尡 ������
		//��� ���� ������ headerNode�� �����Ҷ��� �̾߱��.
		//���� �̹���尡 �ڿ��پ��⿡ ���� ��带 ���� prev��忡 �����ؾ��Ѵ�.
		//���� ���(���� ������ ���� ���)�� ���� ��带 �����Ѿ��Ѵ�.
		tailNode->nextNode = newNode;
		newNode->prevNode = tailNode;
		tailNode = newNode;
	}

	++count;
}

template<typename T>
void CList<T>::push_front(const T& _data)
{
	//������ ����� �����ϱ⿡ ó������ �Ǿ ������ �����ȴ��Ͽ��� ��������.
	//�̹� ����� �� ���� ���� �������̴�.
	Node<T>* newNode = new Node<T>(_data, nullptr, headerNode);

	if (nullptr == headerNode)
	{
		//�̹���尡 ù ��� �����Ͻ�
		tailNode = newNode;
	}
	else
	{
		headerNode->prevNode = newNode;
	}
	
	headerNode = newNode;

	++count;
}

