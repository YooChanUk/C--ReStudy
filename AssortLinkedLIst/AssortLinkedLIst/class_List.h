#pragma once

struct Node
{
	int idata;
	Node* nextNode;
};

class List
{
private:
	Node* headNode;
	int count;

public:
	void pushBack();
	void pushFront();

	List();
};