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
	myvector.push_back(4);
	myvector.push_back(5);
	myvector.push_back(6);

	CArr<int>::iterator myiter = myvector.begin();
	

	for (myiter = myvector.begin(); myiter != myvector.end();)
	{
		if (1 <= *myiter && 5 >= *myiter)
		{
			myiter = myvector.erase(myiter);
		}
		else
		{
			++myiter;
		}
	}

	//for (int i = 0; i < myvector.size(); ++i)
	//{
	//	cout << myvector[i] << endl;
	//}

	CList<int> mylist;
	mylist.push_back(100);
	mylist.push_back(200);
	mylist.push_back(300);

	CList<int>::iterator listiter = mylist.begin();
	*listiter = 150;

	++listiter;

	mylist.insert(listiter, 300);

	for (listiter = mylist.begin(); listiter != mylist.end(); ++listiter)
	{
		cout << *listiter << endl;
	}

	return 0;
}