#include "TemplateArr.h"

int main()
{
	Arr<int> arr;

	arr.push_back(1);
	arr.push_back(2);
	arr.push_back(3);
	arr.push_back(4);

	Arr<int>::iterator iter = arr.begin();

	int sdata = *iter;

	--iter;
	--iter;

	int o = *iter;

	++iter;
	++iter;
	++iter;
	
	
	arr.push_back(5);
	++iter;
	--iter;

	

	arr.push_back(6);

	int rdata = *iter;

	arr.check();

	return 0;
}
