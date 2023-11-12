#pragma once
#include<iostream>
#include<assert.h>

template<typename T>
class CArr
{
private:
	T* m_pData;
	int m_iCount;
	int m_iMaxCount;

public:
	void push_back(const T& _idata);
	void resize(int _iResizeCount);
	void check();
	int size()
	{
		return m_iCount;
	}
	
	T& operator[] (int idx);

	class iterator;//�Ʒ� �ν��ϱ����� ���ͷ����Ͱ� ����
	iterator begin();
	iterator end();
	iterator erase(iterator& _iter);

	void clear()
	{
		m_iCount = 0;
	}

public:
	CArr();
	~CArr();

	class iterator
	{
	private:
		CArr* m_pArr; //iterator�� ����ų �����͸� �����ϴ� �����迭 �ּ�
		T* m_pData; // �����͵��� ���� �ּ�
		int m_iIdx; // ����Ű�� �������� �ε���
		bool m_bVaild;

	public:
		T& operator *()
		{
			//iterator�� �˰��ִ� �ּҰ� �޶����ų� iterator�� end�� ����Ű�� �ִ� ���
			if (m_pArr->m_pData != m_pData || -1 == m_iIdx || !m_bVaild)
			{
				//m_pData = m_pArr->m_pData;
				assert(nullptr);
			}

			return m_pData[m_iIdx];
		}

		iterator& operator ++()
		{
			//iterator�� ������ �����͸� ����Ű�� ���� end iterator�� ���
			//�׸��� �ּҰ� ����Ȱ��
			if (m_pArr->m_pData != m_pData || -1 == m_iIdx)
			{
				assert(nullptr);
			}

			//�����������͸� ����Ű�� ��쿡 �ش��ϴ°��̴�. count�� ���� �ٲٴ°Ծƴ�
			//�����������ʹ� -1�� ���ڰ� ���Ƿ� ���߱⿡ m_iIdx�� -1�̵ȴ�.
			//���� �ε�����ȣ�� 0���� ���������� �����迭�� ���ڰ� ����
			//�츮�� 1���� ���ڸ� ���⿡ ī��Ʈ�� -1�� �Ͽ� �ε�����ȣ�� ���ڰ� ��ġ���� Ȯ�� 
			if (m_pArr->m_iCount-1 == m_iIdx)
			{
				m_iIdx = -1;
			}
			else
			{
				++m_iIdx;
			}

			return *this;
		}

		//���������ڴ� ȣ������� �����ϴ�.
		//�Ķ���Ϳ� �̸����� �ڷ����� ������ ���� �����ڷ� �����Ѵ�.
		iterator operator ++(int)
		{
			iterator copy_iter = *this;

			++(*this);

			return copy_iter;
		}

		iterator& operator --()
		{
			if (m_iIdx == -1) //���� ���κ��̰ų� �����Ͱ� ������ -1�̱� ������ m_iCount-1�����ָ� �ȴ�.
				//�����Ͱ� ������� m_iCount�� 0�̱⿡ -1�� �ϸ� -1�� �ȴ�.
			{
				m_iIdx = m_pArr->m_iCount-1;
			}

			if (m_iIdx <= 0)
			{
				//�ε����� �׻� 0���� �����Ѵ�.
				//��� 0���� �۾����� ���� �����
				m_iIdx = 0;
			}
			else
			{
				--m_iIdx;
			}

			return *this;
		}

		//�񱳿�����

		bool operator ==(const iterator& _otheriter)
		{
			if (m_pData == _otheriter.m_pData && m_iIdx == _otheriter.m_iIdx)
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
			:m_pArr(nullptr)
			, m_pData(nullptr)
			, m_iIdx(-1)
			, m_bVaild(false)
		{

		}

		iterator(CArr* _pArr,T* _pData,int _iIdx)
			:m_pArr(_pArr)
			,m_pData(_pData)
			,m_iIdx(_iIdx)
			, m_bVaild(false)
		{
			if (nullptr != _pArr && 0 <= _iIdx)
			{
				m_bVaild = true;
			}
		}


		~iterator()
		{

		}

		friend class CArr;
	};
};

template<typename T>
CArr<T>::CArr()
	:m_pData(nullptr)
	,m_iCount(0)
	,m_iMaxCount(2)
{
	m_pData = new T[2];
}

template<typename T>
CArr<T>::~CArr()
{
	delete[] m_pData;
}

template<typename T>
void CArr<T>::push_back(const T& _iData)
{
	if (m_iMaxCount <= m_iCount)
	{
		resize(m_iMaxCount * 2);
	}

	m_pData[m_iCount++] = _iData;
}

template<typename T>
void CArr<T>::resize(int _iResizeCount)
{
	if (m_iMaxCount >= _iResizeCount)
	{
		assert(nullptr);
	}

	T* pNew = new T[_iResizeCount];

	for (int i = 0; i < m_iCount; ++i)
	{
		pNew[i] = m_pData[i];
	}

	delete[] m_pData;

	m_pData = pNew;

	m_iMaxCount = _iResizeCount;
}

template<typename T>
void CArr<T>::check()
{
	std::cout << m_pData[0] << "/" << m_pData[1] << "/" << m_pData[2];
}

template<typename T>
T& CArr<T>::operator[](int idx)
{
	return m_pData[idx];
}

template<typename T>
typename CArr<T>::iterator CArr<T>::begin()
{

	//������ ����Ű�� ���ͷ����͸� ����� ��ȯ
	if (0 == m_iCount)
	{
		return iterator(this, m_pData, -1);
	}
	else
	{
		return iterator(this, m_pData, 0);
	}
}

template<typename T>
typename CArr<T>::iterator CArr<T>::end()
{
	//���� ������ ����Ű�� ���ͷ����͸� ����� ��ȯ
	return iterator(this, m_pData, -1);

}

template<typename T>
typename CArr<T>::iterator CArr<T>::erase(iterator& _iter)
{
	//iteraotr�� �ٸ� ��Ҹ� ����Ű�ų� end�� ����Ų ��� �����Ұ�
	if (_iter.m_pArr != this || end() == _iter || _iter.m_iIdx >= m_iCount)
	{
		assert(nullptr);
	}

	//������ ���� ����ÿ� �ڿ��ִ� �����͸� ������ �Űܿ;��ϱ� ������
	//��������� ������ ���ƾ��ϴ°� ���� 5���� �����Ͱ� �ְ� �ε��� 1��° �����͸� ����ٰ��ϸ�
	//�츮�� ������ 10�����ڿ��� 2��°�� �����͸� �����.
	// 1 [2] 3 4 5 (������) 
 	// 0 [1] 2 3 4 (�ε���)
	// 1 [3] 4 5
	// 0 [1] 2 3
	//�츮�� �����͸� 3�� �ű���̱⿡ �� ��Ģ��
	//5���� ������ (����Ű�� �ε��� + 1)�� ���� 5 - 2, 3�� �ű�°��̴�.
	int iLoopCount = m_iCount - (_iter.m_iIdx + 1);
	
	for (int i = 0; i < iLoopCount; ++i)
	{
		m_pData[i + _iter.m_iIdx] = m_pData[i + _iter.m_iIdx + 1];
	}

	_iter.m_bVaild = false;

	--m_iCount;

	return iterator(this,m_pData,_iter.m_iIdx);
}
