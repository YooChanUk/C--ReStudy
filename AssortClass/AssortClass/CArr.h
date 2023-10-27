#pragma once
#include<iostream>
#include<assert.h>

template<typename T>
class CArr
{
private:
	T* m_pInt;
	int m_iCount;
	int m_iMaxCount;

public:
	void push_back(const T& _idata);
	void resize(int _iResizeCount);
	void check();
	
	T& operator[] (int idx);
public:
	CArr();
	~CArr();
};

template<typename T>
CArr<T>::CArr()
	:m_pInt(nullptr)
	,m_iCount(0)
	,m_iMaxCount(2)
{
	m_pInt = new T[2];
}

template<typename T>
CArr<T>::~CArr()
{
	delete[] m_pInt;
}

template<typename T>
void CArr<T>::push_back(const T& _iData)
{
	if (m_iMaxCount <= m_iCount)
	{
		resize(m_iMaxCount * 2);
	}

	m_pInt[m_iCount++] = _iData;
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
		pNew[i] = m_pInt[i];
	}

	delete[] m_pInt;

	m_pInt = pNew;

	m_iMaxCount = _iResizeCount;
}

template<typename T>
void CArr<T>::check()
{
	std::cout << m_pInt[0] << "/" << m_pInt[1] << "/" << m_pInt[2];
}

template<typename T>
T& CArr<T>::operator[](int idx)
{
	return m_pInt[idx];
}