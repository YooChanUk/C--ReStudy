#include "Array.h"

void arrayinit(array* _pArr, int maxcount)
{
	_pArr->arr = (int*)malloc(sizeof(int) * maxcount);
	_pArr->count = 0;
	_pArr->maxcount = maxcount;
}

void increaseMaxarray(array* _pArr)
{
	int beforeMaxcount = _pArr->maxcount;
	_pArr->maxcount *= 2;
	int* tArr = (int*)malloc(sizeof(int) * _pArr->maxcount);

	for (int i = 0; i < beforeMaxcount; i++)
	{
		tArr[i] = _pArr->arr[i];
	}

	free(_pArr->arr);


	_pArr->arr = tArr;
}

void arrayinput(array* _pArr, int inum)
{
	if (_pArr->count == _pArr->maxcount)
	{
		increaseMaxarray(_pArr);
	}

	_pArr->arr[_pArr->count] = inum;
	++_pArr->count;
}