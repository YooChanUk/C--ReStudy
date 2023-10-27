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

//두 문자를 비교하여 같으면 0 왼쪽이 크면 1 오른쪽이 크면 -1
//첫번째 인덱스의 아스키코드값이 같으면 사전적으로 같다. 그러므로 넘어가고
//만약 두번째 인덱스부터 값이 다르다면 사전적으로 어느쪽이 더큰지 가늠하여 넘어가야한다.
//abc 와 acb의 아스키 코드를 더하면 같은값이라 뜨기에 이것은 틀렸다.
//abc 와 acb는 ab ac를 비교했을때 b가 사전적으로 더 높기에 왼쪽이 1로 나와야한다.
//이것은 문자인덱스가 늘어난경우에도 똑같다. 우리는 wcscmp 함수를 만드는것이기에
//고로 문자열의 길이를 체크한뒤
//문자열의 길이가 서로 다르면 

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
