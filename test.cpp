#include <iostream>
#include <fstream>
#include <vector>
#include <iterator>
#include "HashTable.h"
#include "spellcheck.h"

using namespace std;

// Opens a file and reads the contents into a vector
// PARAM: infile = name of the file to be opened
// PRE: the file contains words separated by white space // POST: returns a vector containing the contents of infile 
vector<string> readFile(string infile)
{
	ifstream ist(infile.c_str()); 
	if (ist.fail())
		throw runtime_error(infile + " not found"); 
	istream_iterator<string> start(ist), end; 
	vector<string> result(start, end);
	
	ist.close(); 
	return result;
}

int main(){

	HashTable ht(2);

	// vector<string> file = readFile("wordList1000.txt");
	// for(int i = 0; i < file.size(); i++){
	// 	// cout << file[i] << endl;
	// 	ht.insert(file[i]);
	// }

	// vector<string> test = extraLetter(ht, "chate");
	// vector<string> test = transposition(ht, "atr");
	// vector<string> test = missingSpace(ht, "rateat");
	// vector<string> test = missingLetter(ht, "eat");	
	// vector<string> test = incorrectLetter(ht, "thed");		

	// // test = extraLetter(ht, "mra");

	// for(int i = 0; i < test.size(); i++){
	// 	cout << test[i] << endl;
	// }

	ht.insert("dog");
	ht.insert("froh");
	ht.insert("cat");	
	// ht.insert("eric");
	// ht.insert("lie");
	// ht.insert("die");
	// ht.insert("cry");	
	// ht.insert("a");	
	// ht.insert("tea");
	// ht.insert("see");	
	// ht.insert("dough");	
	// ht.insert("low");
	// ht.insert("push");	
	// ht.insert("pop");	
	// ht.insert("hello");	
	// ht.insert("sail");						

	// ht.insert("pseudopseudohypoparathyroidism");
	// // ht.insert("hello");
	// ht.insert("antidisestablishmentarianism");
	// ht.insert("supercalifragilisticexpialidocious");
	// ht.insert("incomprehensibilities");
	// ht.insert("floccinaucinihilipilification");	
	// ht.insert("chate");	
	// ht.display();
	cout << "SIZE -> " << ht.size() << endl;
	cout << "SIZEMAX -> " << ht.maxSize() << endl;

	return 0;
}