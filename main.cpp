#include "LinkedList.h"
#include <typeinfo>
using namespace std;

int getCommand()
{
	int command = 0;
	cout << "\n Type the number of the action you would like to perform:" << endl;
	cout << "\n 1) Display list of names" << endl;
	cout << "\n 2) Display randomization constraints" << endl;
	cout << "\n 3) Add randomization constraits" << endl;
	cout << "\n 4) Remove randomization constraits" << endl;
	cout << "\n 5) Randomize" << endl;
	cout << "\n -1) Exit Program" << endl;
	cout << " ";
	cin >> command;
	//Input validation loop
	while (cin.fail())
	{
		cout << "\n Error invalid input type: please enter an integer." << endl;
		cin.clear();
		cin.ignore(256, '\n');
		cout << "\n Type the number of the action you would like to perform:" << endl;
		cout << "\n 1) Display list of names" << endl;
		cout << "\n 2) Display randomization constraints" << endl;
		cout << "\n 3) Add randomization constraits" << endl;
		cout << "\n 4) Remove randomization constraits" << endl;
		cout << "\n 5) Randomize" << endl;
		cout << "\n -1) Exit Program" << endl;
		cout << " ";
		cin >> command;
	}
	cout << endl;
	return command;
}

bool getInput(string& gifter, string& giftee, vector<string> names)
{
	bool foundName = false;
	//GIFTER INPUT BLOCK
	cout << " Enter the gifter's name or type -1 to cancel:\n ";
	cin >> gifter;
	if (gifter == "-1")
	{
		return true;
	}
	for (unsigned int i = 0; i < names.size(); i++)
	{
		if (gifter == names.at(i))
		{
			foundName = true;
			break;
		}
	}
	//gifter input validation sub-block
	while (!foundName)
	{
		cout << " " << gifter << " Not found please enter a valid name or type -1 to cancel:\n ";
		cin >> gifter;
		if (gifter == "-1")
		{
			return true;
		}
		for (unsigned int i = 0; i < names.size(); i++)
		{
			if (gifter == names.at(i))
			{
				foundName = true;
				break;
			}
		}
	}
	//GIFTEE INPUT BLOCK
	foundName = false;
	cout << " Enter the giftee's name or type -1 to cancel:\n ";
	cin >> giftee;
	if (giftee == "-1")
	{
		return true;
	}
	if (gifter != giftee)
	{
		for (unsigned int i = 0; i < names.size(); i++)
		{
			if (giftee == names.at(i))
			{
				foundName = true;
				break;
			}
		}
	}
	//giftee input validation sub-block
	while (!foundName)
	{
		if (gifter == giftee)
		{
			cout << " gifter and giftee must be different please enter a valid name or type -1 to cancel:\n ";
		}
		else
		{
			cout << " " << giftee << " Not found please enter a valid name or type -1 to cancel:\n ";
		}
		cin >> giftee;
		if (giftee == "-1")
		{
			return true;
		}
		if (giftee != gifter)
		{
			for (unsigned int i = 0; i < names.size(); i++)
			{
				if (giftee == names.at(i))
				{
					foundName = true;
					break;
				}
			}
		}
	}
	return false;
}

void menu(MainList list)
{
	const string defaultName = "NONE";
	string gifter = defaultName;
	string giftee = defaultName;
	NameList names = list.getNameList();
	int command = 0;
	//Menu Loop
	while (command != -1)
	{
		command = getCommand();
		switch (command)
		{
		case -1:
		{
			//Exits Program.
			break;
		}
		case 1:
		{
			//Prints all names
			list.printNames();
			break;
		}
		case 2:
			//Prints all constraints or a message saying that there are no constraints
			list.displayConstaints();
			break;
		case 3:
		{
			//User is asked to input names from the list
			gifter = defaultName;
			giftee = defaultName;
			bool cancel = getInput(gifter, giftee, names.getNameArray());
			if (cancel)
			{
				cout << " Canceled addConstraint(). Returning to menu" << endl;
				break;
			}
			//Checks for conflicting constraints and prompts user if they want to overwrite them.
			list.addConstraint(gifter, giftee);
			break;
		}
		case 4:
		{
			//User is asked to input names from the list
			gifter = defaultName;
			giftee = defaultName;
			bool cancel = getInput(gifter, giftee, names.getNameArray());
			if (cancel)
			{
				cout << " Canceled removeConstraint(). Returning to menu" << endl;
				break;
			}
			//Removes specified constraint
			list.removeConstraint(gifter, giftee);
			break;
		}
		case 5:
		{
			//Generates random list then applies specified constraints recursively.
			list.randomize();
			break;
		}
		default:
			cout << " Please enter a valid action number" << endl;
			break;
		}
	}
	cout << " Thank you for using the program, Goodbye" << endl;
}

int main()
{
	MainList primaryList("NameListFile.txt");
	menu(primaryList);
	return 0;
}
