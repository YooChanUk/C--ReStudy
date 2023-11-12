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

		//Arr�� �ʱ� �����صξ��� ũ�Ⱑ ������ resize�� �Ѵ�. resize�� ���ο� ���޸𸮿�
		//�ּҸ� �Űܰ��� ������ m_data�� �� resize�ÿ� �ּҸ� �ٽ� �ǹ޾ƿ;� �Ѵ�.

	private:
		Arr* m_arr;
		T* m_data;
		int m_idx;

	public:
		T& operator *()
		{

			if (m_idx == -1 && m_arr->m_count == 0)
			{
				//�����Ͱ� ������
				std::cout << "�����Ͱ� ����" << std::endl;
			}
			else if (m_idx == -1 && m_arr->m_count > 0)
			{
				//iter�� ���� ����Ű��������
				std::cout << "�����Ͱ� end�� ����Ű�� ��" << std::endl;
			}
			
			if (m_arr->m_data != m_data)
			{
				//resize�ϰų� ���޸� ����ÿ��� ���Ҵ�
				m_data = m_arr->m_data;
			}

			return m_data[m_idx];
		}

		iterator& operator ++()
		{
			if (m_idx == -1 && m_arr->m_count > 0)
			{
				//iter�� ���� ����Ű�������� �״�� ��ȯ
				std::cout << "�����Ұ� �����Ͱ� end�� ����Ű�� ��" << std::endl;
				return *this;
			}

			if (m_arr->m_count - 1 == m_idx)
			{
				//�����Ͱ� ���� �ٴٶ������
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
				//�ε����� �׻� 0���� �����Ѵ�.
				//��� 0���� �۾����� ���� �����
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
	//������ �����ʹ� �� �������� ���� -1�̶�� ��ø� �س��Ҵ�.
	//�׷��� ������ �����ʹ� Arr��ü�� Count�� �����ֱ⶧���� Count ���ڿ� ���� �����Ͱ� ���ٸ�
	//�̶�� end�� ���ص� ����� ����.
	//end�� ����ڰ� ���ϱ� �����ΰ� ����.

	return iterator(this,m_data,-1);
}

