#include<assert.h>
#include<iostream>
//using namespace std;

template<typename T>
class Arr
{
private:
	T* m_data;
	int m_count;
	int m_maxCount;

public:
	void push_back(const T& data);
	void resize(const int resizeCount);
	void check();

	T& operator [](int idx);

	class iterator;
	iterator begin();
	iterator end();

public:
	Arr()
		:m_data(nullptr)
		, m_count(0)
		, m_maxCount(2)
	{
		//새로운 데이터를 생성하는것이기 때문에 완전히 새로운 힙메모리를 생성한다.
		m_data = new T[m_maxCount];
	}

	Arr(const T& m_data,const int& count,const int& max_count)
		:m_data(m_data)
		,m_count(count)
		,m_maxCount(max_count)
	{
		//이미 있는 힙 메모리가 있다면 그것을 가져오는것이다. 맥스카운트와 카운트도 모두 가져오기 때문에
		//복사 붙여넣기와 비슷한 생성자다.
		//const를 붙여 원본 데이터를 건들지는 않겠다는것을 명시한다.
	}

	~Arr()
	{
		//힙 메모리 완전 해제 영역
		delete[] m_data;
	}

public:
	class iterator
	{
		//이터레이터는 정확한 위치에 정확한 데이터가 있는지를 확인하며
		//이 정확한 위치에 기반하여 객체를 반환하여 정확한 데이터가 있는지를 확인하게 해주는 도구이다.
		//그렇기에 원본의 위치와 데이터의 위치가 정확히 일치하는지 확인하는것도 필요할수있다.
		//그러나 원본의 데이터와는 상관없이 그저 위치만을 원한다면 원본의 데이터만 있으면된다.

		//Arr은 초기 선정해두었던 크기가 꽉차면 resize를 한다. resize는 새로운 힙메모리에
		//주소를 옮겨가기 떄문에 m_data가 그 resize시에 주소를 다시 되받아와야 한다.

	private:
		Arr* m_arr;
		T* m_data;
		int m_idx;

	public:
		T& operator *()
		{

			if (m_idx == -1 && m_arr->m_count == 0)
			{
				//데이터가 없을시
				std::cout << "데이터가 없음" << std::endl;
			}
			else if (m_idx == -1 && m_arr->m_count > 0)
			{
				//iter가 끝을 가리키고있을때
				std::cout << "데이터가 end를 가리키는 중" << std::endl;
			}
			
			if (m_arr->m_data != m_data)
			{
				//resize하거나 힙메모리 변경시에는 재할당
				m_data = m_arr->m_data;
			}

			return m_data[m_idx];
		}

		iterator& operator ++()
		{
			if (m_idx == -1 && m_arr->m_count > 0)
			{
				//iter가 끝을 가리키고있을때 그대로 반환
				std::cout << "전진불가 데이터가 end를 가리키는 중" << std::endl;
				return *this;
			}

			if (m_arr->m_count - 1 == m_idx)
			{
				//데이터가 끝에 다다랐을경우
				m_idx = -1;
			}
			else
			{
				++m_idx;
			}

			
			return *this;
		}

		iterator& operator --()
		{
			if (m_idx <= 0)
			{
				//인덱스는 항상 0부터 시작한다.
				//고로 0보다 작아질수 없게 만든다
				m_idx = 0;
			}
			else
			{
				--m_idx;
			}


			return *this;
		}


	public:
		iterator()
			:m_arr(nullptr)
			, m_data(nullptr)
			, m_idx(-1)
		{

		}

		iterator(Arr* _m_arr, T* _m_data, int idx)
			:m_arr(_m_arr)
			, m_data(_m_data)
			, m_idx(idx)
		{

		}


		~iterator()
		{

		}

	};
};

template<typename T>
void Arr<T>::push_back(const T& data)
{
	if (m_count >= m_maxCount)
	{
		resize(m_maxCount * 2);
	}

	m_data[m_count] = data;
	++m_count;
}

template<typename T>
void Arr<T>::resize(const int resizeCount)
{
	//사이즈를 늘리는것은 새로운 힙메모리를 만들어 그곳에 이전 시키는것이기때문에
	//힙메모리를 새로 만들어 위치를 바꾸는 것이다.
	//이미 존재하는 사이즈보다는 작게 만들거나 같게만드는것은 의미 없기 때문에 예외처리를 해야한다.

	if (m_maxCount >= resizeCount)
	{
		assert(nullptr);
	}

	T* NewData = new int[resizeCount];

	for (int i = 0; i < m_count; ++i)
	{
		NewData[i] = m_data[i];
	}

	delete[] m_data;

	m_data = NewData;

	m_maxCount = resizeCount;

}

template<typename T>
void Arr<T>::check()
{
	for (int i = 0; i < m_count; ++i)
	{
		std::cout << m_data[i] << std::endl;
	}
}

template<typename T>
T& Arr<T>::operator [](int idx)
{
	return m_data[idx];
}


template<typename T>
typename Arr<T>::iterator Arr<T>::begin()
{
	if (this->m_count == 0)
	{
		return iterator(this, m_data, -1);
	}
	else
	{
		return iterator(this, m_data, 0);
	}

	
}

template<typename T>
typename Arr<T>::iterator Arr<T>::end()
{
	//마지막 데이터는 끝 데이터의 다음 -1이라고 명시를 해놓았다.
	//그러나 마지막 데이터는 Arr객체의 Count가 세고있기때문에 Count 숫자와 안의 데이터가 같다면
	//이라는 end로 정해도 상관은 없다.
	//end는 사용자가 정하기 나름인것 같다.

	return iterator(this,m_data,-1);
}

