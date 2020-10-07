#pragma once
#include <string>

using namespace std;

class HashTable{

public:

	HashTable(); //default constructor 
	HashTable(int n); //constructor
	HashTable(const HashTable & ht); //copy constructor
	~HashTable(); //destructor

	HashTable & operator= (const HashTable & ht); //operator=

	void insert(string value); //insert. Insert string value into table
	bool find(string value) const; //find. Find string value in table
	int size() const; //size. Amount of values in table
	int maxSize() const; //maxSize. size of the table
	float loadFactor() const; //loadFactor

private:

	string* arr; //underlying array of string objects
	int arrSize; //size of array
	int valueTwo; //value for h2
	int currentSize; //current items in table

	//Helper functions
	int firstHash(string k) const; //Convert string to int and mod with arrSize
	int secondHash(string k) const; //Convert string to int and do second hash calculation
	int getPrime(int n) const; //Get the nearest prime
	void increaseArray(); //Increase size of array used in insertion
	void deepCopy(const HashTable & ht); //Create a deep copy of the HashTable parameter
};