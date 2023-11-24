#pragma once
#include<iostream>
#include<map>
using std::wcout;
using std::endl;

using std::wstring;

enum class NODE_TYPE 
{
	PARENT,//0
	LCHILD,//1
	RCHILD,//2
	END,//3
};

template<typename T1,typename T2>
struct tPair
{
	T1 first;
	T2 second;
};

template<typename T1,typename T2>
tPair<T1, T2> make_bstpair(const T1& _first, const T2& _second)
{
	return tPair<T1, T2>{_first, _second};
}

template<typename T1,typename T2>
struct tBSTNode
{
	//필요한것
	//실제데이터 파트
	tPair<T1,T2>			pair;

	////자신의 부모노드
	//tBSTNode*		pParent;

	////두개의 자식 노드
	//tBSTNode*		pLeftChild;
	//tBSTNode*		pRightChild;

	tBSTNode* arrNode[(int)NODE_TYPE::END];

	tBSTNode()
		:pair()
		, arrNode{}
	{

	}

	tBSTNode(const tPair<T1,T2>& _pair, tBSTNode* _pParent, tBSTNode* _pLChild, tBSTNode* _pRChild)
		:pair(_pair)
		,arrNode{_pParent,_pLChild,_pRChild}
	{

	}
};


template<typename T1,typename T2>
class CBST
{
private:
	tBSTNode<T1,T2>* m_pRoot;//루트노드주소
	int m_iCount;//이진탐색트리의 데이터 갯수

public:
	bool insert(const tPair<T1,T2>& _pair);

public:
	class iterator;
	iterator begin();
	iterator end();
	iterator find(const T1& _find);

public:
	CBST()
		:m_pRoot(nullptr)
		,m_iCount(0)
	{

	}

	~CBST()
	{

	}

	//iterator
	class iterator 
	{
	private:
		CBST<T1, T2>* m_pBST;
		tBSTNode<T1, T2>* m_pNode; // null포인터인 경우 end iterator
	public:
		iterator()
			: m_pBST(nullptr)
			, m_pNode(nullptr)
		{

		}

		iterator(CBST<T1, T2>* _pBST, tBSTNode<T1, T2>* _pNode)
			:m_pBST(_pBST)
			,m_pNode(_pNode)
		{

		}

		~iterator()
		{

		}

	};

};

template<typename T1, typename T2>
inline bool CBST<T1, T2>::insert(const tPair<T1,T2>& _pair)
{
	tBSTNode<T1,T2>* pNewNode = new tBSTNode<T1, T2>(_pair,nullptr, nullptr, nullptr);

	//최초의 insert일시
	if (nullptr == m_pRoot)
	{
		m_pRoot = pNewNode;
	}
	else
	{
		tBSTNode<T1, T2>* pNode = m_pRoot;
		NODE_TYPE node_type = NODE_TYPE::END;


		while (true)
		{
			if (pNode->pair.first < pNewNode->pair.first)
			{
				node_type = NODE_TYPE::RCHILD;
			}
			else if (pNode->pair.first > pNewNode->pair.first)
			{
				node_type = NODE_TYPE::LCHILD;
			}
			else
			{
				return false;
			}

			if (nullptr == pNode->arrNode[(int)node_type])
			{
				pNode->arrNode[(int)node_type] = pNewNode;
				pNewNode->arrNode[(int)NODE_TYPE::PARENT] = pNode;
				break;
			}
			else
			{
				pNode = pNode->arrNode[(int)node_type];
			}			
		}	
	}

	++m_iCount;

	return true;
}

template<typename T1, typename T2>
typename CBST<T1,T2>::iterator CBST<T1, T2>::begin()
{
	tBSTNode<T1, T2>* pNode = m_pRoot;

	while (pNode->arrNode[(int)NODE_TYPE::LCHILD])
	{
		pNode = pNode->arrNode[(int)NODE_TYPE::LCHILD];
	}

	return iterator(this,pNode);
}

template<typename T1, typename T2>
typename CBST<T1,T2>::iterator CBST<T1, T2>::end()
{
	return iterator(this,nullptr);
}

template<typename T1, typename T2>
typename CBST<T1,T2>::iterator CBST<T1, T2>::find(const T1& _find)
{
	tBSTNode<T1, T2>* pNode = m_pRoot;
	NODE_TYPE node_type = NODE_TYPE::END;

	while (true)
	{
		if (pNode->pair.first < _find)
		{
			node_type = NODE_TYPE::RCHILD;
		}
		else if (pNode->pair.first > _find)
		{
			node_type = NODE_TYPE::LCHILD;
		}
		else
		{
			//찾았다.
			break;
		}

		if (nullptr == pNode->arrNode[(int)node_type])
		{
			//못찾음
			pNode = nullptr;
			break;
		}
		else
		{
			pNode = pNode->arrNode[(int)node_type];
		}
	}

	return iterator(this, pNode);
}
