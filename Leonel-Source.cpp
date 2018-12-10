#ifndef _SOURCE_CPP
#define _SOURCE_CPP

#include "LinkedList.h"
#include "HashTable.h"

using namespace std;

void leonelMain()
{
	char endProgram;
	HashTable<int> test(5);
	int* pInt = test.getPArray();
	//Add to HashTable
	test.add(24);
	test.add(2);
	cout << "add " << pInt[1] << endl;
	cout << "add " << pInt[5] << endl;

	//Search for data
	int index = test.search(24);
	cout << "search " << index << endl;
	//Remove from HashTable
	if (test.removebyData(24))
	{
		cout << "remove " << pInt[1] << endl;
		cout << "remove " << pInt[5] << endl;
	}
	else
		cout << "FAIL" << endl;
	if (test.removebyData(24))
	{
		cout << "remove " << pInt[1] << endl;
		cout << "remove " << pInt[5] << endl;
	}
	else
		cout << "FAIL" << endl;

	test.removebyIndex(5);
	cout << "remove " << pInt[1] << endl;
	cout << "remove " << pInt[5] << endl;

	cout << "Press <Enter>";
	cin.get(endProgram);
	//return 0;
}
#endif // !_SOURCE_CPP