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
	iterator end();
public:
	CArr();
	~CArr();

	class iterator
	{
	private:
		CArr* m_pArr; //iterator가 가리킬 데이터를 관리하는 가변배열 주소
		T* m_pData; // 데이터들의 시작 주소
		int m_iIdx; // 가리키는 데이터의 인덱스

	public:
		T& operator *()
		{
			//iterator가 알고있는 주소가 달라지거나 iterator가 end를 가리키고 있는 경우
			if (m_pArr->m_pData != m_pData || -1 == m_iIdx)
			{
				assert(nullptr);
			}

			return m_pData[m_iIdx];
		}

		iterator& operator ++()
		{
			//iterator가 마지막 데이터를 가리키는 경우와 end iterator인 경우
			//그리고 주소가 변경된경우
			if (m_pArr->m_pData != m_pData || -1 == m_iIdx)
			{
				assert(nullptr);
			}

			//마지막데이터를 가리키는 경우에 해당하는것이다. count의 값을 바꾸는게아닌
			//마지막데이터는 -1로 하자고 임의로 정했기에 m_iIdx는 -1이된다.
			//또한 인덱스번호는 0부터 시작하지만 가변배열에 숫자가 들어가면
			//우리는 1부터 숫자를 세기에 카운트에 -1을 하여 인덱스번호와 숫자가 일치한지 확인 
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

		//후위연산자는 호출시점은 동일하다.
		//파라미터에 이름없는 자료형을 넣으면 후위 연산자로 동작한다.
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

		//비교연산자

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

	//시작을 가리키는 이터레이터를 만들어 반환
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
	//끝의 다음을 가리키는 이터레이터를 만들어 반환
	return iterator(this, m_pData, -1);

}