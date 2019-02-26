#ifndef _HASHTABLE_H
#define _HASHTABLE_H

#include <string>
#include <fstream>
#include "Pokemon.h"
#include "LinkedList.h"

/*
Hashtable
This is the last status report. I'd say im 99% (because I tested it as much as I could, but there could still be errors).
Comments are important for understanding what im doing. Ill document everything as best as possible so you can easily follow along.
#Include LinkedList.h is my linkedlist.h file.
There is no writing to file mechanisms in this. If there are, then it would be in HashdisplayAll. I'll leave that to Cliff to do.
Main Functions:
Private:
hash - this function takes in a pokemon pointer, and follows a simple algorithm to return an index.
collisionResolution - this function performs linear collision resolution. Basically, if the index in the
array is full, it progresses through the array linearly until it finds an open slot. If no slots, returns -1.
collisionSearch - this function performs linear search through the hash array if the search function does not
find the parameter in the hashtable. If the linear search fails, index is -1.
collisionLinkedList - This is the linked list collision resolution mechanism. If the add function hits a collision, then
the data is stored into a SELF-ADJUSTING LINKED LIST (option 1 of the CIS22c options).
collisionLLSearch - If data is not in the hash array, then this function searches through the linkedlist to find
if it is stored in that. If not, it returns a negative value.
selfAdjustSearch - this function follows the SELF-ADJUSTING LINKED LIST criteria where if you search a piece of data, it gets moved
to the front without changing the other positions. (basically remove where it located, then add it to position 0).
Public:
Constructor - sets arrayLength, then dynamically creates an array of that length.
Destructor - deletes the dynamically created array. The LinkedList deletes on its own because it isn't dynamically created.
hashDisplay - If you call this function (probably wont because requirement is list all), it displays the content of the
item in the HASH ARRAY index you specify.
LinkedListDisplay -If you call this function (probably wont because requirement is list all), it displays the content of the
item in the LINKEDLIST index you specify
hashDisplayAll - this function loops through hashDisplay and LinkedListDisplay to display EVERYTHING stored.
add - This function takes in a pokemon pointer, goes through the hash function to get an index, and then stores it into the HASH ARRAY.
IMPORTANT COMMENT: THIS FUNCTION HAS 2 FORMS.
FORM 1: IF YOU CHOOSE TO DO LINEAR COLLISION RESOLUTION, THEN IT CALLS COLLISIONRESOLUTION AND STORES IT INTO AN EMPTY SLOT IN HASH ARRAY.
FORM 2: IF YOU CHOOSE TO DO LINKEDLIST RESOLUTION, THEN IT CALLS COLLISIONLINKEDLIST AND STORES IT IN THE
FIRST SLOT OF THE LINKEDLIST. (This is to follow the self-adjusting linkedlist requirement.)
removeByData - This function takes in a pokemon pointer, goes through the hash function to get an index, and then compares the data
stored in that index to the data you specified. If same, then remove. If not, then depending on which collision resolution you are using,
you either call collisionSearch and then remove the data from the HASHARRAY, or you call collisionLLSearch and remove it from the LinkedList.
removeByIndex - this function is likely never going to get called, but if you want to remove an item from the hash array by index,
this does just that.
Search - This function takes in a pokemon pointer, calls the hash function, and compares the data in that index of the HASH ARRAY
to that of the parameter. If no match, then depending on what you are using, you either call collisionSearch to linear search through the
HASH ARRAY for it, or you call collisionLLSearch, which looks through the linked list for it.
rehash - This function modifies the size of the hashArray if 75% of the array is filled up. This works with or without linkedlist as all
it does is take the original array and duplicates it, set the original array all to nullptrs, delete the original array, then dynamically
create an array of (size x 2) + 1, and then copy everything from the duplicate back to the resized array. yay for rehash.
Getters and Setters: Self explanatory.
Well. that everything for the functions! There not much I can say anymore.
If there is a problem with one of the functions, notify me so I can look through my code and try to identify the error.
Well, that everything. Good luck on integrating everything together.
*/


class HashTable
{
private:
	Pokemon** pokemonPtrArray;
	int arrayLength;
	int itemCount = 0;
	LinkedList<Pokemon*> linkedListOverflow; //ONLY FOR LINKED LIST COLLISION

								/*This function follows a mathematical algorithm that takes the paramater's primary data and returns an index.
								Pre: Data - a pokemon pointer
								Post:
								Return: an integer
								*/
	int hash(Pokemon* data)
	{
		//return (((data->getSerialNumber() * data->getSerialNumber()) + 1) % arrayLength);
		return (data->getSerialNumber() - 1);
	}

	/*This function takes an index and then searches through the hashtable for an open slot.
	Pre: hashIndex - an integer
	Post: hashIndex is changed based on the results of the function. Positive if a slot is open, negative if not.
	Return: hashIndex
	*/
	int collisionResolution(int &hashIndex)
	{
		for (int i = hashIndex + 1; i < arrayLength; i++)
		{
			if (pokemonPtrArray[i] == nullptr)
			{
				hashIndex = i;
				return hashIndex;
			}
		}
		for (int j = 0; j < hashIndex; j++)
		{
			if (pokemonPtrArray[j] == nullptr)
			{
				hashIndex = j;
				return hashIndex;
			}
		}
		hashIndex = -1;
		return hashIndex;
	}

	/*This function takes an index and pokemon pointer and then searches through the hashtable for it.
	Pre: index - an integer
	data - a pokemon pointer
	Post: hashIndex is changed based on the results of the function. Positive if found, negative if not.
	Return: hashIndex
	*/
	int collisionSearch(int &index, Pokemon* data)
	{
		for (int i = index + 1; i < arrayLength; i++)
		{
			if (pokemonPtrArray[i] != nullptr)
			{
				if (pokemonPtrArray[i]->getSerialNumber() == data->getSerialNumber())
				{
					index = i;
					return index;
				}
			}
		}
		for (int j = 0; j < index; j++)
		{
			if (pokemonPtrArray[j] != nullptr)
			{
				if (pokemonPtrArray[j]->getSerialNumber() == data->getSerialNumber())
				{
					index = j;
					return index;
				}
			}
		}
		index = -1;
		return index;
	}

	/*This function takes a pokemon pointer and then adds it into a link-list.
	Pre: data - a pokemon pointer.
	Post: If successful, data is added to pLink.
	Return:
	*/
	void collisionLinkList(Pokemon* data) //ONLY FOR USING LINK LIST COLLISION RESOLUTION
	{
		Node<Pokemon*>* temp = new Node<Pokemon*>(data);
		linkedListOverflow.addAnywhere(0, temp);
	}

	/*This function takes a pokemon pointer and searches through the link-list for it.
	Pre: data - a pokemon pointer
	Post:
	Return: an integer that represents an index.
	*/
	int collisionLLSearch(Pokemon* data) //ONLY FOR USING LINK LIST COLLISION RESOLUTION
	{
		return linkedListOverflow.searchAnywhere(data);
	}

	/*This function adjusts the link-list when a search is called so that the searched Item is placed in the front of the list.
	Pre: index - an integer
	data - a pokemon pointer.
	Post: data is moved from its original position into position 0 of the link list.
	Return:
	*/
	void selfAdjustSearch(int index, Pokemon* data)
	{
		Node<Pokemon*>* temp = new Node<Pokemon*>(data);
		linkedListOverflow.removeAnywhere(index);
		linkedListOverflow.addAnywhere(0, temp);
	}

public:
	//Constructor
	HashTable(int l)
	{
		arrayLength = (l + 1); // Hopefully Less collisions when size increased by 1.
		pokemonPtrArray = new Pokemon*[arrayLength];
		for (int i = 0; i < arrayLength; i++)
		{
			pokemonPtrArray[i] = nullptr;
		}
	}

	//Destructor
	~HashTable()
	{
		std::cout << "Deleting hashTable" << std::endl;
		delete[] pokemonPtrArray; // delete the dynamic array
		pokemonPtrArray = nullptr;
	}

	/*This function displays the content stored in an index in the hashtable.
	Pre: index - an integer.
	Post:
	Return:
	*/
	void hashDisplay(int index)
	{
		if (pokemonPtrArray[index] != nullptr)
			std::cout << pokemonPtrArray[index] << std::endl;
	}

	/*This function displays the content stored in an index in the linked list..
	Pre: index - an integer.
	Post:
	Return:
	*/
	void LinkedListDisplay(int index) //ONLY FOR LINKED LIST COLLISION RESOLUTION
	{
		Node<Pokemon*>* temp = linkedListOverflow.obtainDataAnywhere(index);
		if (temp->getData() != nullptr)
			std::cout << *(temp->getData()) << std::endl;
	}

	/*This function displays all content stored in the hashtable (and the linked list if using linkedlist collision resolution)
	Pre:
	Post:
	Return:
	*/
	void hashDisplayAll()
	{
		for (int i = 0; i < arrayLength; i++)
		{
			hashDisplay(i);
		}

		//this is INCLUDED in hashDisplayAll IF you are using LINKED LIST COLLISION RESOLUTION.
		//REMOVE IF NOT USING LINKEDLIST COLLISION RESOLUTION.
		int linkedSize = linkedListOverflow.getCurrentSize();
		std::cout << "Now displaying everything stored in Linked List" << std::endl;
		for (int j = 0; j < linkedSize; j++)
		{
			LinkedListDisplay(j);
		}

	}

	//Follow comments to know which section goes with which.
	/*
	This function adds a pokemon pointer into the hashtable.
	Pre: data - a pokemon pointer
	Post: if successful, data is stored in the appropriate location in the hashtable. If not, it is stored in an open slot.
	(If linkedList resolution - If not, it is stored in the linked list in position 0).
	Return:
	*/
	void add(Pokemon* data)
	{
		//This is for BOTH linear and Linked List
		int hashIndex; //basically holds index after hash function
		hashIndex = hash(data); // Call hash function (see hash)

		// if the hashIndex number is greater than the size of the array, add the item to the linked list
		if (hashIndex > arrayLength)
		{
			collisionLinkList(data);
		}

		else if (pokemonPtrArray[hashIndex] == nullptr)
		{
			pokemonPtrArray[hashIndex] = data; // insert data to appropriate location.
			itemCount++; //increment counter
		}


		//THIS IS LINEAR COLLISION RESOLUTION ELSE STATEMENT
		/*
		else
		{
		collisionResolution(hashIndex); // Fixed Collision!
		pArray[hashIndex] = data;
		itemCount++;
		}
		*/

		//THIS IS LINK LIST COLLISION RESOLUTION ELSE STATEMENT
		else
		{
			collisionLinkList(data);
		}

		//This is for both Linked List and Linear Resolution
		if (((double)itemCount / (double)arrayLength) >= 0.75)
			rehash();
	}

	/*This function removes the content of an index in the hashtable.
	Pre: data - a pokemon pointer
	Post: If successful, data is removed from the hashtable.
	(If linkedList - or data is removed from the linked list if data is not in hashtable)
	Return: true or false
	*/
	bool removebyData(Pokemon* data)
	{
		//Both Linear Collision and LinkedList resolution
		bool isRemoved = false;
		int index = hash(data);

		// if the index number is out of bounds, check the linked list
		if (index >= arrayLength)
		{
			//isRemoved = false;
			//return isRemoved;
			index = collisionLLSearch(data);
			isRemoved = linkedListOverflow.removeAnywhere(index);
			return isRemoved;
		}
		else if (pokemonPtrArray[index] != nullptr)
		{
			if (pokemonPtrArray[index]->getSerialNumber() == data->getSerialNumber())
			{
				delete pokemonPtrArray[index];
				pokemonPtrArray[index] = nullptr;
				itemCount--;
				isRemoved = true;
				return isRemoved;
			}

			//LINEAR COLLISION RESOLUTION INNER ELSE STATEMENT
			/*
			else
			{
			collisionSearch(index, data);
			if (index >= 0)
			{
			delete pArray[index];
			pArray[index] = nullptr;
			itemCount--;
			isRemoved = true;
			return isRemoved;
			}
			}
			*/

			//LINKED LIST COLLISION RESOLUTION INNER ELSE STATEMENT
			else
			{
				index = collisionLLSearch(data);
				isRemoved = linkedListOverflow.removeAnywhere(index);
				return isRemoved;
			}
		}
		else
		{
			//LINEAR COLLISION RESOLUTION OUTER ELSE STATEMENT
			/*
			collisionSearch(index, data);
			if (index >= 0)
			{
			delete pArray[index];
			pArray[index] = nullptr;
			itemCount--;
			isRemoved = true;
			return isRemoved;
			}
			*/

			//LINKED LIST COLLISION RESOLUTION OUTER ELSE STATEMENT
			index = collisionLLSearch(data);
			isRemoved = linkedListOverflow.removeAnywhere(index);
			return isRemoved;
		}

		return isRemoved;
	}

	//This remove function is likely not to be used in either linear or linked list.
	//This is an array remove, so doesnt work for linkedlist.
	/*This function removes the content stored in an index in the hashtable.
	Pre: index - an integer.
	Post: if successful, removes the data from the hashtable.
	Return:
	*/
	void removebyIndex(int index)
	{
		if (index >= 0 && index < arrayLength && pokemonPtrArray[index] != nullptr)
		{
			delete pokemonPtrArray[index];
			pokemonPtrArray[index] = nullptr;
			itemCount--;
		}
	}

	/*This function searches for data in the hashtable and returns it's index.
	Pre: data - a pokemon pointer.
	Post:
	Return: an integer representing the index.
	*/
	int search(Pokemon* data)
	{
		int index = hash(data);
		if (pokemonPtrArray[index] != nullptr)
		{
			if (pokemonPtrArray[index]->getSerialNumber() == data->getSerialNumber())
			{
				return index;
			}

			//THIS IS LINEAR COLLISION SEARCH INNER ELSE STATEMENT
			/*
			else
			{
			collisionSearch(index, data);
			return index;
			}
			*/

			//THIS IS LINKED LIST RESOLUTION SEARCH INNER ELSE STATEMENT
			else
			{
				std::cout << "Searching LinkList" << std::endl;
				index = collisionLLSearch(data);
				selfAdjustSearch(index, data);
				return index; //In main: HAVE IF STATEMENT CHECKING IF INDEX > 0. ( >= 0 means success, < 0 means failure)
			}
		}
		else
		{
			//THIS IS LINEAR COLLISION RESOLUTION OUTER ELSE STATEMENT
			/*
			collisionSearch(index, data);
			return index;
			*/

			//THIS IS LINKED LIST COLLISION RESOLUTION OUTER ELSE STATEMENT
			std::cout << "Searching LinkList" << std::endl;
			index = collisionLLSearch(data);
			return index;
		}

		index = -1;
		return index;
	}

	/*This function resizes the hashtable if the fill count is 75%.
	Pre:
	Post: arrayLength is now (twice in size + 1). pArray now points to a larger dynamically created array.
	Return:
	*/
	void rehash()
	{
		int OrigLength = arrayLength; // 6
		Pokemon** pArray2 = new Pokemon*[OrigLength]; //6
		for (int i = 0; i < OrigLength; i++)
		{
			pArray2[i] = pokemonPtrArray[i];
			pokemonPtrArray[i] = nullptr;
		}
		delete[] pokemonPtrArray;
		pokemonPtrArray = nullptr;
		arrayLength = (arrayLength * 2) + 1; // 13
		pokemonPtrArray = new Pokemon*[arrayLength]; //13
		for (int k = 0; k < arrayLength; k++)
		{
			pokemonPtrArray[k] = nullptr;
		}
		for (int i = 0; i < OrigLength; i++)
		{
			if (pArray2[i] != nullptr)
			{
				pokemonPtrArray[i] = pArray2[i];
				pArray2[i] = nullptr;
			}
		}
		delete[] pArray2;
		pArray2 = nullptr;
	}

	// Getters
	Pokemon** getPArray() const
	{
		return pokemonPtrArray;
	}
	int getLength() const
	{
		return arrayLength;
	}
	int getItemCount() const
	{
		return itemCount;
	}

	// Setters
	void setPArray(Pokemon** pArr)
	{
		pokemonPtrArray = pArr;
	}
	void setLength(int l)
	{
		arrayLength = l;
	}
	void setCount(int c)
	{
		itemCount = c;
	}
};
#endif // !_HASHTABLE_H