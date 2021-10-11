#include "LinkedList.h"

Constraint::Constraint()
{
	cout << " empty constraint constructed" << endl;
	return;
}

Constraint::~Constraint()
{
	return;
}

Constraint::Constraint(string gifter, string giftee)
{
	m_gifter = gifter;
	m_giftee = giftee;
}

string Constraint::message()
{
	string msg = " " + m_gifter + " gives to " + m_giftee;
	return msg;
}

ConstraintList::ConstraintList()
{
	m_numConstraints = 0;
}

ConstraintList::~ConstraintList()
{
	m_constraints.clear();
}

bool ConstraintList::checkForConflicts(string gifter, string giftee)
{
	bool conflicts = false;
	for (unsigned int i = 0; i < m_constraints.size(); i++)
	{
		if ((m_constraints.at(i).m_giftee == giftee) || (m_constraints.at(i).m_gifter == gifter))
		{
			conflicts = true;
			break;
		}
	}
	return conflicts;
}

bool ConstraintList::findConstraint(string gifter, string giftee)
{
	int foundConstraint = false;
	for (unsigned int i = 0; i < m_constraints.size(); i++)
	{
		if ((m_constraints.at(i).m_gifter == gifter) && (m_constraints.at(i).m_giftee == giftee))
		{
			foundConstraint = true;
			break;
		}
	}
	return foundConstraint;
}

void ConstraintList::addConstraint(string gifter, string giftee)
{
	//CONFLICTION CHECK BLOCK
	bool conflictingConstraint = checkForConflicts(gifter, giftee);
	//Runs if one or more conflicting constraints are found
	if (conflictingConstraint)
	{
		for (unsigned int i = 0; i < m_constraints.size() - 1; i++)
		{
			Constraint curConstraint = m_constraints.at(i);
			if ((curConstraint.m_gifter == gifter) && (curConstraint.m_giftee == giftee))
			{
				cout << " This constraint already exists" << endl;
				cout << " returning to menu" << endl;
				return;
			}
		}
		//USER INPUT BLOCK
		int actionNum = 0;
		cout << " " << gifter << " gives to " << giftee << " conflicts with the existing constraints:" << endl;
		cout << " Type the action number you would like to do \n 1) Overwrite the conflicting constraints \n 2) Cancel" << endl;
		cin >> actionNum;
		while ((actionNum != 1) && (actionNum != 2))
		{
			cout << " Please enter a valid action number" << endl;
			cout << " Type the action number you would like to do \n 1) Overwrite the conflicting constraints \n 2) Cancel" << endl;
			cin >> actionNum;
		}
		//REMOVE AND RESTRUCTURE BLOCK
		if (actionNum == 1)
		{
			cout << " Overwriting constraint(s)" << endl;
			removeConstraints(gifter, giftee);
		}
	}
	//CONSTRAINT CREATION BLOCK
	m_constraints.push_back(Constraint(gifter, giftee));
	m_numConstraints++;
	cout << " returning to menu" << endl;
}

void ConstraintList::removeConstraints(string gifter, string giftee)
{
	Constraint curConstraint;
	for (int i = m_constraints.size() - 1; i >= 0; i--)
	{
		curConstraint = m_constraints.at(i);
		if ((curConstraint.m_gifter == gifter) || (curConstraint.m_giftee == giftee))
		{
			if (!(i == m_constraints.size() - 1))
			{
				m_constraints.at(i).m_gifter = m_constraints.at(m_constraints.size() - 1).m_gifter;
				m_constraints.at(i).m_giftee = m_constraints.at(m_constraints.size() - 1).m_giftee;
			}
			m_constraints.pop_back();
			m_numConstraints--;
		}
	}
}

void ConstraintList::displayConstraintList() const
{
	if (m_numConstraints)
	{
		cout << " Displaying list of randomization constraints:" << endl;
		for (unsigned int i = 0; i < m_constraints.size(); i++)
		{
			Constraint display = m_constraints.at(i);
			cout << display.message() << endl;
		}
	}
	else
	{
		cout << " There are currently no randomization constraints" << endl;
	}
}

int ConstraintList::getNumConstraints()
{
	return m_numConstraints;
}

vector<Constraint> ConstraintList::getConstraints()
{
	return m_constraints;
}

MainList::MainList()
{
	string fileName;
	cout << " Please enter the fileName you want to load in:" << endl;
	cin >> fileName;
	m_listofNames = new NameList(fileName);
	m_constraintList = new ConstraintList();
}

MainList::MainList(NameList names)
{
	m_listofNames = &names;
	m_constraintList = new ConstraintList();
}

MainList::MainList(string file)
{
	m_listofNames = new NameList(file);
	m_constraintList = new ConstraintList();
}

MainList::~MainList()
{
	delete m_listofNames;
	delete m_constraintList;
}

void MainList::addConstraint(string gifter, string giftee)
{
	m_constraintList->addConstraint(gifter, giftee);
}

void MainList::removeConstraint(string gifter, string giftee)
{
	if (m_constraintList->findConstraint(gifter, giftee))
	{
		cout << " removing constraint: " << gifter << " gives to " << giftee << endl;
		m_constraintList->removeConstraints(gifter, giftee);
	}
	else
	{
		cout << " No matching constraints found for: " << gifter << " gives to " << giftee << endl;
	}
}

void MainList::printNames() const
{
	cout << " Displaying list of names:" << endl;
	m_listofNames->PrintNames();
}

void MainList::randomize()
{
	//RANDOMIZATION BLOCK
	Node* headNode;
	cout << " Generating randomized secrect santa list" << endl;
	//creates a vector containing all unassigned names.
	vector<string> unusedNames;
	for (unsigned int i = 0; i < getNameList().getNameArray().size(); i++)
	{
		unusedNames.push_back(getNameList().getNameArray().at(i));
	}

	//Creates the headNode using one of the names from the unusedNames vector
	int nameIndex = rand() % unusedNames.size();
	string curName = unusedNames.at(nameIndex);
	Node* curNode = new Node(curName);
	headNode = curNode;
	//Removes the name from the vector so it cannot be used again.
	unusedNames.erase(unusedNames.begin() + nameIndex);
	//Creates Nodes using the same proccess as was used to create the headNode.
	for (unsigned int i = 1; i < getNameList().getNameArray().size(); i++)
	{
		int nameIndex = rand() % unusedNames.size();
		string curName = unusedNames.at(nameIndex);
		Node* nextNode = new Node(curName);
		unusedNames.erase(unusedNames.begin() + nameIndex);
		//The new node is then linked to the curNode.
		curNode->setLink(nextNode);
		//CurNode traverses to the newly linked node.
		curNode = curNode->getNext();
	}
	//Links the last node back to the first node after all nodes are created.
	curNode->setLink(headNode);
	
	//CONSTRAIN AND DISPLAY BLOCK
	//Constraints are applied recursively
	applyConstraints(headNode);
	//Prints all Nodes then deletes them.
	headNode->printAll();
	headNode->ClearAll();
}

void MainList::applyConstraints(Node* head)
{
	for (unsigned int i = 0; i < getConstraintList().getConstraints().size(); i++)
	{
		//Sets gifter and giftee for convienience at the start of the function.
		string gifter = getConstraintList().getConstraints().at(i).m_gifter;
		string giftee = getConstraintList().getConstraints().at(i).m_giftee;
		Node* curNode = head;
		bool looped = false;
		while ((!looped) || (curNode != head))
		{
			//Sets looped to true so that the loop does not run multiple times.
			if (curNode->getPrev() == head)
			{
				looped = true;
			}
			if ((curNode->getPrev()->getName() == gifter) && (curNode->getName() != giftee))
			{
				//Finds the node containing the giftee's name and switching the names of it and the node the giftee should be at.
				bool looped2 = false;
				Node* temp = curNode;
				while ((temp != curNode) || (!looped2))
				{
					//sets looped2 to true so that the loop does not run multiple times.
					if (temp->getPrev() == curNode)
					{
						looped2 = true;
					}
					//switches the names of the nodes then breaks the loop.
					if (temp->getName() == giftee)
					{
						temp->setName(curNode->getName());
						curNode->setName(giftee);
						break;
					}
					//traverses to the next node if the names do not match.
					else
					{
						temp = temp->getNext();
					}
				}
				//Recursive Call
				applyConstraints(curNode->getNext());
				//Returns to the previous recursion
				return;
			}
			//If the gifter and giftee are already in the right positions the loop breaks
			else if ((curNode->getPrev()->getName() == gifter))
			{
				break;
			}
			//Traverses to the next Node if the previous Node does not contain the gifter's name.
			else
			{
				curNode = curNode->getNext();
			}
		}
	}
}

void MainList::displayConstaints() const
{
	m_constraintList->displayConstraintList();
}

NameList MainList::getNameList()
{
	return *m_listofNames;
}

ConstraintList MainList::getConstraintList()
{
	return *m_constraintList;
}
