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
	
	T& operator[] (int idx);

	class iterator;//�Ʒ� �ν��ϱ����� ���ͷ����Ͱ� ����
	iterator begin();
	iterator end();
public:
	CArr();
	~CArr();

	class iterator
	{
	private:
		CArr* m_pArr; //iterator�� ����ų �����͸� �����ϴ� �����迭 �ּ�
		T* m_pData; // �����͵��� ���� �ּ�
		int m_iIdx; // ����Ű�� �������� �ε���

	public:
		T& operator *()
		{
			//iterator�� �˰��ִ� �ּҰ� �޶����ų� iterator�� end�� ����Ű�� �ִ� ���
			if (m_pArr->m_pData != m_pData || -1 == m_iIdx)
			{
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
			,m_pData(nullptr)
			, m_iIdx(-1)
		{

		}

		iterator(CArr* _pArr,T* _pData,int _iIdx)
			:m_pArr(_pArr)
			,m_pData(_pData)
			,m_iIdx(_iIdx)
		{

		}


		~iterator()
		{

		}
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