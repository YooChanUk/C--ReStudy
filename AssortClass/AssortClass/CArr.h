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

	class iterator;//아래 인식하기위해 이터레이터가 있음
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
		CArr* m_pArr; //iterator가 가리킬 데이터를 관리하는 가변배열 주소
		T* m_pData; // 데이터들의 시작 주소
		int m_iIdx; // 가리키는 데이터의 인덱스
		bool m_bVaild;

	public:
		T& operator *()
		{
			//iterator가 알고있는 주소가 달라지거나 iterator가 end를 가리키고 있는 경우
			if (m_pArr->m_pData != m_pData || -1 == m_iIdx || !m_bVaild)
			{
				//m_pData = m_pArr->m_pData;
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
			if (m_iIdx == -1) //만약 끝부분이거나 데이터가 없으면 -1이기 때문에 m_iCount-1을해주면 된다.
				//데이터가 없을경우 m_iCount는 0이기에 -1을 하면 -1이 된다.
			{
				m_iIdx = m_pArr->m_iCount-1;
			}

			if (m_iIdx <= 0)
			{
				//인덱스는 항상 0부터 시작한다.
				//고로 0보다 작아질수 없게 만든다
				m_iIdx = 0;
			}
			else
			{
				--m_iIdx;
			}

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

template<typename T>
typename CArr<T>::iterator CArr<T>::erase(iterator& _iter)
{
	//iteraotr가 다른 요소를 가리키거나 end를 가리킨 경우 삭제불가
	if (_iter.m_pArr != this || end() == _iter || _iter.m_iIdx >= m_iCount)
	{
		assert(nullptr);
	}

	//데이터 삭제 이행시에 뒤에있던 데이터를 앞으로 옮겨와야하기 떄문에
	//어느정도의 루프를 돌아야하는가 만약 5개의 데이터가 있고 인덱스 1번째 데이터를 지운다고하면
	//우리는 데이터 10개숫자에서 2번째의 데이터를 지운다.
	// 1 [2] 3 4 5 (데이터) 
 	// 0 [1] 2 3 4 (인덱스)
	// 1 [3] 4 5
	// 0 [1] 2 3
	//우리는 데이터를 3번 옮길것이기에 이 규칙상
	//5개의 데이터 (가리키는 인덱스 + 1)을 빼면 5 - 2, 3번 옮기는것이다.
	int iLoopCount = m_iCount - (_iter.m_iIdx + 1);
	
	for (int i = 0; i < iLoopCount; ++i)
	{
		m_pData[i + _iter.m_iIdx] = m_pData[i + _iter.m_iIdx + 1];
	}

	_iter.m_bVaild = false;

	--m_iCount;

	return iterator(this,m_pData,_iter.m_iIdx);
}
