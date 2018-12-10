//#define _CRT_SECURE_NO_WARNINGS
#ifndef _HASHTABLE_H
#define _HASHTABLE_H


//#include "Node.h"
#include <fstream>
#include<iostream>
//#include"Pokemon.h"
//class Pokemon;

/*
Hashtable
NOTICE: THIS IS USING MY NODE CLASS. I'm used to my node, so i used it. Will change it to reflect the node class we choose.
I'm uploading my node.h as well incase you want to see what i used.
This is status report #1. I'd say im about 50% complete with the hash table. Have working add, remove, and search functions.
Technically hash works, but might modify it.
Missing Collision handling and Rehashing.
Main Functions:
Constructor - complete
Destructor - complete
Add - Tested with int class. Will modify/test for pokemon soon.
Remove (by index and by data) - Both tested with int class. Will modify/test for pokemon soon.
Search - Tested with int class. Will modify/test for pokemon soon.
Hash (Key function) - Currently a working placeholder. will modify.
Rehash - planned but not done
Collision (handle collision) - planned but likely last to be done.
Getters and Setters - complete.
*/
template <class T>
class HashTable
{
private:
	T* hashedTableArray;
	int arrayLength;
	int counter;

	int hash(T data) // Temporary hash/key function
	{
		int number;
		number = static_cast<int>(*data);
		number = (number - 1);
		return number;
		//return (((data * data) + 1) % arrayLength);
	}

public:
	//Constructor
	HashTable(int size)
	{
		counter = 0;  // added for testing 
		arrayLength = (size + 1); // Hopefully Less collisions when size increased by 1.
		hashedTableArray = new T[arrayLength]; //Dynamically allocated array
	}

	//Destructor
	~HashTable()
	{
		delete[] hashedTableArray; // delete the dynamic array
		hashedTableArray = nullptr;
	}

	void coutHashedTable()
	{
		for (int count = 0; count < (arrayLength-1); count++)
		{
			cout << hashedTableArray[count] << endl;
		}
	}


	//TODO: Collision check
	void add(T data)
	{
		int hashHolder; //basically holds index after hash function
		hashHolder = hash(data); // Call hash function (see hash)
		//hashHolder = counter;
		hashedTableArray[hashHolder] = data; // insert data to appropriate location.
		//counter++;
	}

	void add(T data, int serialNumber)
	{
		int hashHolder; //basically holds index after hash function
		//hashHolder = hash(data); // Call hash function (see hash)
		hashHolder = counter;
		hashedTableArray[hashHolder] = data; // insert data to appropriate location.
		counter++;
	}


	bool removebyData(T data) //Searches for data. If found, remove. Else, nothing.
	{
		bool isRemoved = false;
		for (int i = 0; i < arrayLength; i++)
		{
			if (hashedTableArray[i] == data)
			{
				hashedTableArray[i] = NULL;
				isRemoved = true;
				return isRemoved;
			}
		}
		return isRemoved;
	}

	void removebyIndex(int index) //Remove by index. 
	{
		hashedTableArray[index] = NULL;
	}

	int search(T data) // Finds data. if found, returns index. if not, index is -1.
	{
		int index = -1;
		for (int i = 0; i < arrayLength; i++)
		{
			if (hashedTableArray[i] == data)
			{
				index = i;
				return index;
			}
		}
		return index;
	}
	/*
	Not complete. Still thinking it through
	void collision()
	{
	}
	void rehash()
	{
	}
	*/

	// Getters
	T* getPArray() const
	{
		return hashedTableArray;
	}
	int getLength() const
	{
		return length;
	}

	// Setters
	void setPArray(T* pArr)
	{
		hashedTableArray = pArr;
	}
	void setLength(int l)
	{
		length = l;
	}

};
#endif // !_HASHTABLE_H