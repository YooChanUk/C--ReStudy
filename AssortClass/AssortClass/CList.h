#pragma once
#include<iostream>
#include<assert.h>

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
	int size()
	{
		return count;
	}

public:
	class iterator;
	iterator begin();
	iterator end();
	iterator erase(iterator& _iter);
	iterator insert(const iterator& _iter,const T& _data);


public:
	CList();
	~CList();

	class iterator
	{
	private:
		CList<T>* m_pList;
		Node<T>* m_pNode;
		bool m_bVaild;

	public:
		T& operator *()
		{
			return m_pNode->data;
		}

		iterator& operator ++()
		{
			if (m_pNode == nullptr || !m_bVaild)
			{
				assert(nullptr);
			}

			m_pNode = m_pNode->nextNode;

			return *this;
		}

		iterator operator ++(int)
		{
			iterator copyiter(*this);

			++(*this);

			return copyiter;
		}

		iterator& operator --()
		{
			if (m_pNode == nullptr || !m_bVaild)
			{
				assert(nullptr);
			}

			m_pNode = m_pNode->prevNode;

			return *this;
		}

		iterator operator --(int)
		{
			iterator copyiter(*this);

			--(*this);

			return copyiter;
		}

		bool operator ==(const iterator& _otheriter)
		{
			if (m_pList == _otheriter.m_pList && m_pNode == _otheriter.m_pNode)
			{
				return true;
			}
			return false;
		}

		bool operator !=(const iterator& _otheriter)
		{
			return !(*this == _otheriter);
		}


	public:
		iterator()
			:m_pList(nullptr)
			,m_pNode(nullptr)
			,m_bVaild(false)
		{
		
		}

		iterator(CList<T>* _pList,Node<T>* _pNode)
			:m_pList(_pList)
			, m_pNode(_pNode)
			, m_bVaild(false)
		{
			if (nullptr != _pList && nullptr != _pNode)
			{
				m_bVaild = true;
			}
			
		}

		~iterator()
		{
			
		}

		friend class CList;
	};

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

template<typename T>
typename CList<T>::iterator CList<T>::begin()
{
	return iterator(this,headerNode);
}

template<typename T>
typename CList<T>::iterator CList<T>::end()
{
	return iterator(this,nullptr);
}

template<typename T>
typename CList<T>::iterator CList<T>::erase(iterator& _iter)
{
	//배열의 경우는 덮어씌우는 형식으로 삭제가 가능했다.
	//덮어씌우고 카운트를 낮추면 그 뒤에서부터 넣고싶은 데이터를 덮어씌우면 됐지만
	//리스트의 경우는 중간에 넣고 뺄수 있는것이기에 덮어씌우는형식은 안된다.
	//특히나 리스트는 힙메모리를 쓰기때문에 그 부분의 노드를 delete해주어야 한다.
	//고로 삭제하려는 이터레이터가 가리키는 노드의 prev와 next를 서로 이어주고
	//본인은 삭제되어야한다.
	//예외상황은 삭제할때 그 노드가
	//1.헤더노드인경우 - 삭제했을때 그 다음 노드를 리턴
	//2.테일노드인경우(1,2모두 카운트 낮추기) - 삭제했을때 그 전 노드를 리턴
	//3.찾아간 노드의 주소가 맞지 않는 경우(assert처리)
	//4.이터레이터가 엔드를 가리키는 경우
	//삭제후 다음 노드 리턴 및 m_bVaild false로 변환(갱신해줘야지 true로 변경되게끔)

	if (this != _iter.m_pList || end() == _iter || false == _iter.m_bVaild)
	{
		assert(nullptr);
	}

	iterator nextIter;

	if (_iter.m_pNode == headerNode)
	{
		headerNode = _iter.m_pNode->nextNode;

		nextIter = iterator(this, headerNode);
	}
	else if (_iter.m_pNode == tailNode)
	{
		tailNode = _iter.m_pNode->prevNode;
		tailNode->nextNode = nullptr;

		nextIter = end();
	}
	else
	{
		_iter.m_pNode->prevNode->nextNode = _iter.m_pNode->nextNode;
		//이터가 가리키는 노드의 그전 노드의 다음노드는 이터가 가리키는 다음노드
		_iter.m_pNode->nextNode->prevNode = _iter.m_pNode->prevNode;
		//이터가 가리키는 노드의 다음 노드의 그전 노드는 이터가 가리키는 이전 노드

		nextIter = iterator(this,_iter.m_pNode->nextNode);
	}

	delete(_iter.m_pNode);
	--count;
	_iter.m_bVaild = false;

	return nextIter;
}

template<typename T>
typename CList<T>::iterator CList<T>::insert(const iterator& _iter,const T& _data)
{
	if (end() == _iter)
	{
		assert(nullptr);
	}

	//리스트에 추가되는 데이터를 저장 및 node생성
	Node<T>* pNode = new Node<T>(_data, nullptr, nullptr);

	//iterator가 헤더노드를 가리키는경우
	if (_iter.m_pNode == headerNode)
	{
		_iter.m_pNode->prevNode = pNode;
		pNode->nextNode = _iter.m_pNode;

		headerNode = pNode;
	}
	else
	{
		_iter.m_pNode->prevNode->nextNode = pNode;
		pNode->prevNode = _iter.m_pNode->prevNode;

		_iter.m_pNode->prevNode = pNode;
		pNode->nextNode = _iter.m_pNode;
	}



	++count;

	return iterator(this,pNode);
}

