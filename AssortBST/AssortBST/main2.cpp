#include"CBST.h"
#include<iostream>
#include<map>
using std::wcout;
using std::endl;

using std::wstring;


int main()
{
	CBST<int, int> bstint;

	tPair<int, int> pair;
	pair.first = 100;

	bstint.insert(pair);

	pair.first = 150;

	bstint.insert(pair);

	pair.first = 50;

	bstint.insert(pair);

	return 0;
}
