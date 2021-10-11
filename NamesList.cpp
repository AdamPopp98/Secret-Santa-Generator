#include "NameList.h"

NameList::NameList()
{
	cout << " Please enter the name of the text file you want to load in:" << endl;
	string fileName;
	cin >> fileName;
	ifstream file;
	file.open(fileName);
	if (file.is_open())
	{
		string curLine;
		while (getline(file, curLine))
		{
			m_nameArray.push_back(curLine);
			m_numNames++;
		}
		if (getNumNames())
		{
			cout << " Successfully loaded " << getNumNames() << " names from " << fileName << "." << endl;
		}
		else
		{
			cout << " The selected file is empty, please use a valid file." << endl;
		}
		file.close();
	}
	else
	{
		cout << " Error loading: " << fileName << "please confirm that the fileName matches the name of the file containing the list of names." << endl;
	}
}

NameList::NameList(string fileName)
{
	ifstream file;
	file.open(fileName);
	if (file.is_open())
	{
		string curLine;
		while (getline(file, curLine))
		{
			m_nameArray.push_back(curLine);
			m_numNames++;
		}
		if (getNumNames())
		{
			cout << " Successfully loaded " << getNumNames() << " names from " << fileName << "." << endl;
		}
		else
		{
			cout << " The selected file is empty, please use a valid file." << endl;
		}
		file.close();
	}
	else
	{
		cout << " Error loading: " << fileName << "please confirm that the fileName matches the name of the file containing the list of names." << endl;
	}
}

NameList::~NameList()
{
	m_nameArray.clear();
}

void NameList::PrintNames()
{
	for (int i = 0; i < m_nameArray.size(); i++)
	{
		cout << "\n " << m_nameArray.at(i) << endl;
	}
}

vector<string> NameList::getNameArray()
{
	return m_nameArray;
}

int NameList::getNumNames() const
{
	return m_numNames;
}
