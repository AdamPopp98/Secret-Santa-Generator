#include "Node.h"

Node::Node()
{
	m_name = "NONE";
	m_next = nullptr;
	m_prev = nullptr;
}

Node::Node(string name)
{
	m_name = name;
	m_next = nullptr;
	m_prev = nullptr;
}

Node::~Node()
{
	m_name = "NONE";
	m_next = nullptr;
	m_prev = nullptr;
}

string Node::getName()
{
	return m_name;
}

Node* Node::getPrev()
{
	return m_prev;
}

Node* Node::getNext()
{
	return m_next;
}

void Node::setName(string name)
{
	m_name = name;
}

void Node::setLink(Node* next)
{
	m_next = next;
	m_next->m_prev = this;
}

void Node::printNode()
{
	cout << " " << getName() << " gives to " << getNext()->getName() << "\n" << endl;
}

void Node::printAll()
{
	Node* curNode = this;
	while ((curNode->getNext()) && (curNode->getNext() != this))
	{
		curNode->printNode();
		curNode = curNode->getNext();
	}
	curNode->printNode();
}

void Node::ClearAll()
{
	Node* curNode = this;
	while (curNode->getNext())
	{
		Node* nextNode = curNode->getNext();
		if (curNode->getPrev())
		{
			curNode->getPrev()->m_next = nullptr;
		}
		if (nextNode != curNode)
		{
			nextNode->m_prev = nullptr;
			delete curNode;
			curNode = nextNode;
		}
		else
		{
			delete curNode;
			break;
		}
	}
}
