#pragma once
#include<iostream>
#include<map>
#include<assert.h>
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

	bool IsRoot()
	{
		if (nullptr == arrNode[(int)NODE_TYPE::PARENT])
			return true;

		return false;
	}


	bool IsLeftChild()//내가 부모로부터 왼쪽 자식인지 묻는 함수
	{
		if (this == arrNode[(int)NODE_TYPE::PARENT]->arrNode[(int)NODE_TYPE::LCHILD])
			return true;

		return false;
	}

	bool IsRightChild()
	{
		if (this == arrNode[(int)NODE_TYPE::PARENT]->arrNode[(int)NODE_TYPE::RCHILD])
			return true;

		return false;
	}

	bool IsLeaf()
	{
		if (nullptr == arrNode[(int)NODE_TYPE::LCHILD] && nullptr == arrNode[(int)NODE_TYPE::RCHILD])
		{
			return true;
		}

		return false;
	}

	bool IsFull()
	{
		if (arrNode[(int)NODE_TYPE::LCHILD] && arrNode[(int)NODE_TYPE::RCHILD])
		{
			return true;
		}

		return false;
	}

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
	tBSTNode<T1, T2>* GetInOrderSuccessor(tBSTNode<T1, T2>* _pNode);//중위후속
	tBSTNode<T1, T2>* GetInOrderPredecessor(tBSTNode<T1, T2>* _pNode);//중위선행

public:
	class iterator;
	iterator begin();
	iterator end();
	iterator find(const T1& _find);
	iterator erase(const iterator& _iter);

private:
	tBSTNode<T1, T2>* DeleteNode(tBSTNode<T1,T2>* _pTargetNode);

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
		bool operator ==(const iterator& _other)
		{
			if (m_pBST == _other.m_pBST && m_pNode == _other.m_pNode)
			{
				return true;
			}
			
			return false;
		}

		bool operator !=(const iterator& _other)
		{
			return !(*this == _other);
		}

		const tPair<T1, T2>& operator *()
		{
			assert(m_pNode);

			return m_pNode->pair;
		}

		const tPair<T1, T2>* operator ->()
		{
			assert(m_pNode);

			return &m_pNode->pair;
		}

		iterator& operator ++()
		{
			m_pNode = m_pBST->GetInOrderSuccessor(m_pNode);
			return *this;
		}

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

		friend class CBST<T1, T2>;

	};

};

template<typename T1, typename T2>
typename bool CBST<T1, T2>::insert(const tPair<T1,T2>& _pair)
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
typename tBSTNode<T1, T2>* CBST<T1, T2>::GetInOrderSuccessor(tBSTNode<T1, T2>* _pNode)
{
	tBSTNode<T1, T2>* pSuccessor = _pNode;

	//중위후속자의 다음을 얻는 방법
	//1.오른쪽 자식이 있고 오른쪽 자식이 자손이 없는 경우
	if (nullptr != _pNode->arrNode[(int)NODE_TYPE::RCHILD])
	{
		//오른쪽에 자식이 있으니 중위후속자 일지도 모르니 임시지정
		pSuccessor = _pNode->arrNode[(int)NODE_TYPE::RCHILD];

		//2.오른쪽 자식의 왼쪽 자손이 있는 경우(왼쪽을 쭉 파고들어가서 마지막 왼쪽을 알아내야한다.)
		while (pSuccessor->arrNode[(int)NODE_TYPE::LCHILD])
		{
			//오른쪽 자식의 왼쪽 자손이 있으니 왼쪽 자손이 null이 나올때까지 무한반복하고 찾으면 리턴
			pSuccessor = pSuccessor->arrNode[(int)NODE_TYPE::LCHILD];
		}
	}
	//3.자신의 자식이 없고 자신이 왼쪽 자손인 경우 자신의 부모가 중위후속자
	else
	{
		//4.자신의 부모가 있는지 검사한다.없는경우 자연스레 end 이터레이터
		while (true)
		{
			//루트로 넘어간뒤면 오른쪽 자식이 있으니 여기에 걸리지 않는다.
			//걸리는 구간은 오로지 맨 끝노드에 다다랐을때
			if (pSuccessor->IsRoot())
			{
				return nullptr;
			}

			if (pSuccessor->IsLeftChild())
			{
				pSuccessor = pSuccessor->arrNode[(int)NODE_TYPE::PARENT];
				break;
			}
			else
			{
				pSuccessor = pSuccessor->arrNode[(int)NODE_TYPE::PARENT];
			}

		}
	}


	return pSuccessor;
}

template<typename T1, typename T2>
typename tBSTNode<T1, T2>* CBST<T1, T2>::GetInOrderPredecessor(tBSTNode<T1, T2>* _pNode)
{
	return nullptr;
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

template<typename T1, typename T2>
typename CBST<T1,T2>::iterator CBST<T1, T2>::erase(const iterator& _iter)
{
	assert(this == _iter.m_pBST);

	tBSTNode<T1,T2>* pSuccessor = DeleteNode(_iter.m_pNode);

	return iterator(this, pSuccessor);


}

template<typename T1, typename T2>
typename tBSTNode<T1, T2>* CBST<T1, T2>::DeleteNode(tBSTNode<T1, T2>* _pTargetNode)
{	
	tBSTNode<T1, T2>* pSuccessor = GetInOrderSuccessor(_pTargetNode);;


	//1.자식이 하나도 없는경우
	if (_pTargetNode->IsLeaf())
	{
		//삭제시킬 노드의 후속자 노드를 찾아둔다.

		//삭제시킬 노드가 자식이 없는 루트노드인 경우
		if (_pTargetNode == m_pRoot)
		{
			m_pRoot = nullptr;

		}
		else
		{
			//부모노드로 접근, 삭제될 노드인 자식을 가리키는 포인터를 nullptr로 정의
			if (_pTargetNode->IsLeftChild())
			{
				_pTargetNode->arrNode[(int)NODE_TYPE::PARENT]->arrNode[(int)NODE_TYPE::LCHILD] = nullptr;
			}
			else
			{
				_pTargetNode->arrNode[(int)NODE_TYPE::PARENT]->arrNode[(int)NODE_TYPE::RCHILD] = nullptr;
			}
		}

		delete _pTargetNode;

		--m_iCount;
	}
	//자식이 2개인경우
	else if (_pTargetNode->IsFull())
	{
		//삭제 될 자리에 중위 후속자의 값을 복사시킨다.
		_pTargetNode->pair = pSuccessor->pair;
		//이후 중위 후속자를 삭제 한다.
		DeleteNode(pSuccessor);

		pSuccessor = _pTargetNode;
	}
	//자식이 1개인경우
	else
	{

		//자식이 오른쪽 자식인지 왼쪽 자식인지 
		NODE_TYPE eChildType = NODE_TYPE::LCHILD;
		if (_pTargetNode->arrNode[(int)NODE_TYPE::RCHILD])
		{
			eChildType = NODE_TYPE::RCHILD;
		}
			
		//삭제될 노드와 자식과 부모를 연결해준다.
		//삭제될 노드가 자식이 한개있는 루트 노드인 경우 자식을 루트 노드로 승급시킨다.
		if (_pTargetNode == m_pRoot)
		{
			m_pRoot = _pTargetNode->arrNode[(int)eChildType];
			_pTargetNode->arrNode[(int)eChildType]->arrNode[(int)NODE_TYPE::PARENT] = nullptr;
		}
		else
		{
			if (_pTargetNode->IsLeftChild())
			{
				_pTargetNode->arrNode[(int)NODE_TYPE::PARENT]->arrNode[(int)NODE_TYPE::LCHILD] = _pTargetNode->arrNode[(int)eChildType];
			}
			else
			{
				_pTargetNode->arrNode[(int)NODE_TYPE::PARENT]->arrNode[(int)NODE_TYPE::RCHILD] = _pTargetNode->arrNode[(int)eChildType];
			}

			_pTargetNode->arrNode[(int)eChildType]->arrNode[(int)NODE_TYPE::PARENT] = _pTargetNode->arrNode[(int)NODE_TYPE::PARENT];
		}

		delete _pTargetNode;

		--m_iCount;
	}



	return pSuccessor;
}
