#include<stdio.h>
#include<wchar.h>

int Strlen(const wchar_t* str);
int Strcmp(const wchar_t* str1, const wchar_t* str2);

int main()
{
	int len2 = wcscmp(L"abc", L"abcd");
	int len = Strcmp(L"abc", L"abcdef");

	return 0;
}

//�� ���ڸ� ���Ͽ� ������ 0 ������ ũ�� 1 �������� ũ�� -1
//ù��° �ε����� �ƽ�Ű�ڵ尪�� ������ ���������� ����. �׷��Ƿ� �Ѿ��
//���� �ι�° �ε������� ���� �ٸ��ٸ� ���������� ������� ��ū�� �����Ͽ� �Ѿ���Ѵ�.
//abc �� acb�� �ƽ�Ű �ڵ带 ���ϸ� �������̶� �߱⿡ �̰��� Ʋ�ȴ�.
//abc �� acb�� ab ac�� �������� b�� ���������� �� ���⿡ ������ 1�� ���;��Ѵ�.
//�̰��� �����ε����� �þ��쿡�� �Ȱ���. �츮�� wcscmp �Լ��� ����°��̱⿡
//��� ���ڿ��� ���̸� üũ�ѵ�
//���ڿ��� ���̰� ���� �ٸ��� 

int Strcmp(const wchar_t* str1, const wchar_t* str2)
{
	unsigned int str1len = Strlen(str1);
	unsigned int str2len = Strlen(str2);

	unsigned int str1res = 0;
	unsigned int str2res = 0;


	for (int i = 0; i < str1len; ++i)
	{
		str1res += str1[i];
	}
	
	for (int i = 0; i < str2len; ++i)
	{
		str2res += str2[i];
	}

	if (str1res == str2res)
	{
		return 0;
	}
	else if (str1res > str2res)
	{
		return 1;
	}
	else
	{
		return -1;
	}
}

int Strlen(const wchar_t* str)
{
	int i = 0;

	while ('\0' != str[i])
	{
		++i;
	}

	return i;
}
