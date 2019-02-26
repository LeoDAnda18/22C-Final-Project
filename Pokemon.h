#ifndef POKEMON_H
#define POKEMON_H

#include <string>
#include <fstream>

class Pokemon
{
private:
	std::string pokemonName;
	int serialNumber;
	std::string elementalType;
	//std::string type2;
	int offense;
	int defense;
public:
	//Constructors
	Pokemon() // default constructor
	{
		pokemonName = "unknown name";
		serialNumber = -1;  // -1 because you can not enter anything less than 1 as a valid serial number
		elementalType = "unknown type";
		//type2 = "";
		offense = 0;
		defense = 0;
	}
	Pokemon(std::string name, int idNumber, std::string emelents, int offenseNumber, int defenseNumber)
	{
		pokemonName = name;
		serialNumber = idNumber;
		elementalType = emelents;
		//type2 = "";
		offense = offenseNumber;
		defense = defenseNumber;
	}

	//getters
	std::string getPokemonName()
	{
		return pokemonName;
	}
	int getSerialNumber()
	{
		return serialNumber;
	}
	std::string getElementalType()
	{
		return elementalType;
	}
	//std::string getType2()
	//{
	//	return type2;
	//}
	int getOffenseStat()
	{
		return offense;
	}
	int getDefenseStat()
	{
		return defense;
	}

	//setters
	void setPokemonName(std::string name)
	{
		pokemonName = name;
	}
	void setSerialNumber(int idNumber)
	{
		serialNumber = idNumber;
	}
	void setElementType(std::string element)
	{
		elementalType = element;
	}
	//void setType2(std::string x)
	//{
	//	type2 = x;
	//}
	void setOffenseStat(int offenseNumber)
	{
		offense = offenseNumber;
	}
	void setDefenseStat(int defenseNumber)
	{
		defense = defenseNumber;
	}
	void setAll(std::string name, int number, std::string element, int attack, int defend)
	{
		pokemonName = name;
		serialNumber = number;
		elementalType = element;
		offense = attack;
		defense = defend;
	}
	//Overloading >> operator to read in data from file
	friend std::ifstream& operator >> (std::ifstream &file, Pokemon &creature)
	{
		std::string tempString;
		int tempNumber;
		getline(file, tempString, '|');
		tempNumber = std::stoi(tempString);
		creature.setSerialNumber(tempNumber);
		getline(file, tempString, '|');
		creature.setPokemonName(tempString);
		getline(file, tempString, '|');
		creature.setElementType(tempString);
		//getline(file, tempStr, '|');
		//p.setType2(tempStr);
		getline(file, tempString, '|');
		creature.setOffenseStat(std::stoi(tempString));
		getline(file, tempString, '\n');
		creature.setDefenseStat(std::stoi(tempString));
		return file;
	}

	//// overload unique ptr input stream operator
	//friend std::ifstream& operator >> (std::ifstream &file, std::unique_ptr<Pokemon, std::default_delete<Pokemon>> &creature)
	//{
	//	std::string tempString;
	//	int tempNumber;
	//	getline(file, tempString, '|');
	//	tempNumber = std::stoi(tempString);
	//	creature->setSerialNumber(tempNumber);
	//	getline(file, tempString, '|');
	//	creature->setPokemonName(tempString);
	//	getline(file, tempString, '|');
	//	creature->setElementType(tempString);
	//	//getline(file, tempStr, '|');
	//	//p.setType2(tempStr);
	//	getline(file, tempString, '|');
	//	creature->setOffenseStat(std::stoi(tempString));
	//	getline(file, tempString, '\n');
	//	creature->setDefenseStat(std::stoi(tempString));
	//	return file;
	//}

	//  Overload the instream pointer operator
	friend std::ifstream& operator >> (std::ifstream &file, Pokemon *&creature)
	{
		std::string tempString;
		int tempNumber;
		getline(file, tempString, '|');
		tempNumber = std::stoi(tempString);
		creature->setSerialNumber(tempNumber);
		getline(file, tempString, '|');
		creature->setPokemonName(tempString);
		getline(file, tempString, '|');
		creature->setElementType(tempString);
		//getline(file, tempStr, '|');
		//p.setType2(tempStr);
		getline(file, tempString, '|');
		creature->setOffenseStat(std::stoi(tempString));
		getline(file, tempString, '\n');
		creature->setDefenseStat(std::stoi(tempString));
		return file;
	}




	// overloaded out stream operator 
	friend std::ostream &operator << (std::ostream &outStream, Pokemon &creature)
	{
		std::cout << creature.serialNumber << " " << creature.pokemonName << " " << creature.elementalType;
		return outStream;
	}

	//  Overload the outstream pointer operator
	friend std::ostream &operator << (std::ostream &outStream, Pokemon *&creature)
	{
		//std::cout << creature->serialNumber << " " << creature->pokemonName << " " << creature->elementalType;
		std::cout << "[" << creature->serialNumber << "]" << " " << creature->pokemonName;
		return outStream;
	}


	//  Overloaded multiplication operator
	int operator*(const Pokemon *&right)
	{
		int temp;
		temp = this->serialNumber * right->serialNumber;
		return temp;
	}

	// Overloaded <= pointer operation
	bool operator <= (const Pokemon *&rightSide)
	{
		bool status;
		if (this->serialNumber == rightSide->serialNumber)
		{
			status = true;
		}
		else if (this->serialNumber < rightSide->serialNumber)
		{
			status = true;
		}
		else
		{
			status = false;
		}
		return status;
	}

	// Overloaded >= pointer operation
	bool operator >= (const Pokemon *&rightSide)
	{
		bool status;
		if (this->serialNumber == rightSide->serialNumber)
		{
			status = true;
		}
		else if (this->serialNumber > rightSide->serialNumber)
		{
			status = true;
		}
		else
		{
			status = false;
		}
		return status;
	}

	// more overload stuff
	bool operator >= (const Pokemon &rightSide)
	{
		bool status;
		if (this->serialNumber == rightSide.serialNumber)
		{
			status = true;
		}
		else if (this->serialNumber > rightSide.serialNumber)
		{
			status = true;
		}
		else
		{
			status = false;
		}
		return status;
	}

	//// Overloaded <=  operation
	//bool operator<=(const Pokemon &rightSide)
	//{
	//	bool status;
	//	if (this->serialNumber == rightSide.serialNumber)
	//	{
	//		status = true;
	//	}
	//	else if (this->serialNumber < rightSide.serialNumber)
	//	{
	//		status = true;
	//	}
	//	else
	//	{
	//		status = false;
	//	}
	//	return status;
	//}


	bool operator<=(const int &number)
	{
		bool status;
		if (this->serialNumber == number)
		{
			status = true;
		}
		else if (this->serialNumber < number)
		{
			status = true;
		}
		else
		{
			status = false;
		}
		return status;
	}


	bool operator>=(const int &number)
	{
		bool status;
		if (this->serialNumber == number)
		{
			status = true;
		}
		else if (this->serialNumber > number)
		{
			status = true;
		}
		else
		{
			status = false;
		}
		return status;
	}

	// overloaded > operator
	bool operator > (const int &number)
	{
		bool status;
		if (this->serialNumber > number)
		{
			status = true;
		}
		else
		{
			status = false;
		}
		return status;
	}

	// overloaded > operator for the pokemon pointer
	bool operator > (const Pokemon *&rightSide)
	{
		bool status;
		if (this->serialNumber == rightSide->serialNumber)
		{
			status = true;
		}
		else if (this->serialNumber > rightSide->serialNumber)
		{
			status = true;
		}
		else
		{
			status = false;
		}
		return status;
	}

	// overloaded > operator for the pokemon pointer
	bool operator > (const Pokemon &rightSide)
	{
		bool status;
		if (this->serialNumber == rightSide.serialNumber)
		{
			status = true;
		}
		else if (this->serialNumber > rightSide.serialNumber)
		{
			status = true;
		}
		else
		{
			status = false;
		}
		return status;
	}



	operator int ()
	{
		int number;
		number = this->getSerialNumber();
		return number;
	}

	//int operator - (const int&number)
	//{
	//	int result;
	//	result = (this->serialNumber - number);
	//	return result;
	//}


	// overloaded conditional equal operator,  checks the int number to the serial number of the creature
	bool operator==(const int &rightSide)
	{
		bool status;
		if (this->serialNumber == rightSide)
		{
			status = true;
		}
		else
		{
			status = false;
		}
		return status;
	}

	// overloaded conditional equal operator when using a pokemon class pointer
	// compares the serial numbers of the two creatures, if the numbers match it will return true, else return false
	bool operator==(const Pokemon *&rightSide)
	{
		bool status;
		if (this->serialNumber == rightSide->serialNumber)
		{
			status = true;
		}
		else
		{
			status = false;
		}
		return status;
	}

	bool operator==(const Pokemon &rightSide)
	{
		bool status;
		if (this->serialNumber == rightSide.serialNumber)
		{
			status = true;
		}
		else
		{
			status = false;
		}
		return status;
	}



};
#endif