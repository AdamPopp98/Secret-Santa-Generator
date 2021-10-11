#pragma once
#include "NameList.h"
class Node
{
	string m_name;
	Node* m_next;
	Node* m_prev;
public:
	Node();
	Node(string name);
	~Node();
	string getName();
	Node* getPrev();
	Node* getNext();
	void setName(string name);
	void setLink(Node* next);
	void printNode();
	void printAll();
	void ClearAll();
};
