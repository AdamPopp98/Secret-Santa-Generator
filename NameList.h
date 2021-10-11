#pragma once

#include<iostream>
#include<fstream>
#include<string>
#include <vector>

using namespace std;

class NameList
{
	vector<string> m_nameArray;
	int m_numNames = 0;
public:
	NameList();
	NameList(string fileName);
	~NameList();
	int getNumNames() const;
	void PrintNames();
	vector<string> getNameArray();
};
