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
		//푸쉬백은 가장뒤에있는 노드에 붙어야한다. 그렇기에 테일노드의 순서만 바꾸면 된다. 헤더노드통해서 넥스트노드가 있으면
		//계속 들어가는 형식은 headerNode만 존재할때의 이야기다.
		//또한 이번노드가 뒤에붙었기에 그전 노드를 먼저 prev노드에 안착해야한다.
		//그전 노드(지금 꼬리가 그전 노드)는 지금 노드를 가리켜야한다.
		tailNode->nextNode = newNode;
		newNode->prevNode = tailNode;
		tailNode = newNode;
	}

	++count;
}

template<typename T>
void CList<T>::push_front(const T& _data)
{
	//무조건 헤더를 차지하기에 처음생성 되어도 다음에 생성된다하여도 문제없다.
	//이번 노드의 그 다음 노드는 헤더노드이다.
	Node<T>* newNode = new Node<T>(_data, nullptr, headerNode);

	if (nullptr == headerNode)
	{
		//이번노드가 첫 노드 생성일시
		tailNode = newNode;
	}
	else
	{
		headerNode->prevNode = newNode;
	}
	
	headerNode = newNode;

	++count;
}

