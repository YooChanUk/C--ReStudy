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
	return iterator();
}

template<typename T>
typename CList<T>::iterator CList<T>::insert(const iterator& _iter,const T& _data)
{
	if (end() == _iter)
	{
		assert(nullptr);
	}

	//����Ʈ�� �߰��Ǵ� �����͸� ���� �� node����
	Node<T>* pNode = new Node<T>(_data, nullptr, nullptr);

	//iterator�� �����带 ����Ű�°��
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

