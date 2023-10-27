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

	class iterator;//아래 인식하기위해 이터레이터가 있음
	iterator begin();
public:
	CArr();
	~CArr();

	class iterator
	{
	private:
		T* m_pData;
		int m_iIdx;

	public:
		iterator()
			:m_pData(nullptr)
			, m_iIdx(-1)
		{

		}

		iterator(T* _pData,int _iIdx)
			: m_pData(_pData)
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
	//시작을 가리키는 이터레이터를 만들어 반환
	return iterator(m_pData, 0);
}