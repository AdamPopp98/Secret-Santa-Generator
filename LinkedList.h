#pragma once
#include "Node.h"

class Constraint
{
public:
	string m_gifter;
	string m_giftee;

public:

	Constraint();
	~Constraint();
	Constraint(string gifter, string giftee);
	string message();

};

class ConstraintList
{
	int m_numConstraints;
	vector<Constraint> m_constraints;

public:
	
	ConstraintList();
	~ConstraintList();
	bool checkForConflicts(string gifter, string giftee);
	bool findConstraint(string gifter, string giftee);
	void addConstraint(string gifter, string giftee);
	void removeConstraints(string giftee, string gifter);
	void displayConstraintList() const;
	vector<Constraint> getConstraints();

private:

	int getNumConstraints();

};

class MainList
{
	NameList* m_listofNames;
	ConstraintList *m_constraintList;

public:

	MainList();
	MainList(NameList names);
	MainList(string file);
	~MainList();
	void addConstraint(string gifter, string giftee);
	void removeConstraint(string gifter, string giftee);
	void printNames() const;
	void randomize();
	void applyConstraints(Node* head);
	void displayConstaints() const;
	NameList getNameList();
	ConstraintList getConstraintList();
};
