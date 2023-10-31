#include<assert.h>
#include<iostream>
using namespace std;

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
	//iterator end();

public:
	Arr()
		:m_data(nullptr)
		, m_count(0)
		, m_maxCount(2)
	{
		//���ο� �����͸� �����ϴ°��̱� ������ ������ ���ο� ���޸𸮸� �����Ѵ�.
		m_data = new T[m_maxCount];
	}

	Arr(const T& m_data,const int& count,const int& max_count)
		:m_data(m_data)
		,m_count(count)
		,m_maxCount(max_count)
	{
		//�̹� �ִ� �� �޸𸮰� �ִٸ� �װ��� �������°��̴�. �ƽ�ī��Ʈ�� ī��Ʈ�� ��� �������� ������
		//���� �ٿ��ֱ�� ����� �����ڴ�.
		//const�� �ٿ� ���� �����͸� �ǵ����� �ʰڴٴ°��� ����Ѵ�.
	}

	~Arr()
	{
		//�� �޸� ���� ���� ����
		delete[] m_data;
	}

public:
	class iterator
	{
		//���ͷ����ʹ� ��Ȯ�� ��ġ�� ��Ȯ�� �����Ͱ� �ִ����� Ȯ���ϸ�
		//�� ��Ȯ�� ��ġ�� ����Ͽ� ��ü�� ��ȯ�Ͽ� ��Ȯ�� �����Ͱ� �ִ����� Ȯ���ϰ� ���ִ� �����̴�.
		//�׷��⿡ ������ ��ġ�� �������� ��ġ�� ��Ȯ�� ��ġ�ϴ��� Ȯ���ϴ°͵� �ʿ��Ҽ��ִ�.
		//�׷��� ������ �����Ϳʹ� ������� ���� ��ġ���� ���Ѵٸ� ������ �����͸� ������ȴ�.

	private:
		T* m_data;
		int m_idx;

	public:


	public:
		iterator()
			:m_data(nullptr)
			,m_idx(-1)
		{
		
		}

		iterator(T* _m_data,int idx)
			:m_data(_m_data)
			,m_idx(idx)
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
	//����� �ø��°��� ���ο� ���޸𸮸� ����� �װ��� ���� ��Ű�°��̱⶧����
	//���޸𸮸� ���� ����� ��ġ�� �ٲٴ� ���̴�.
	//�̹� �����ϴ� ������ٴ� �۰� ����ų� ���Ը���°��� �ǹ� ���� ������ ����ó���� �ؾ��Ѵ�.

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
		cout << m_data[i] << endl;
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
	return iterator(m_data,0);
}

