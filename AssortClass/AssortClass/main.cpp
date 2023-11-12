#include "CArr.h"
#include "CList.h"
//#include<iostream>

using namespace std;

int main()
{
	/*CArr<int> carr;

	carr.push_back(10);
	carr.push_back(20);
	carr.push_back(30);

	carr.check();

	int i = carr[1] = 500;

	std::cout << i << std::endl;*/

	CArr<int> myvector;
	myvector.push_back(1);
	myvector.push_back(2);
	myvector.push_back(3);

	CArr<int>::iterator myiter = myvector.begin();

	int s = *myiter;

	for (; myiter != myvector.end(); ++myiter)
	{
		cout << *myiter << endl;
	}

	--myiter;
	int r = *myiter;


	return 0;
}