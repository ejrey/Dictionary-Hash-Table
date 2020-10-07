#include "HashTable.h"
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

vector<string> extraLetter(const HashTable & ht, string word){
	
	vector<string> result;
	string givenWord = ""; 
	givenWord = word; //Assign word into givenWord
	bool ran = false;

	if(ht.find(word)){ //If word is in the file, insert word into vector 
		result.push_back(word);
	}else if((!ht.find(word))){ //If word is not found in file, but potentially find options stated in question  
		for(int i = 0; i < givenWord.size(); i++){
			string isWord = givenWord.erase(i,1); //Erase the current letter of the string (whatever i is currently)
			if(ht.find(isWord)){ //If that word is found put into vector
				result.push_back(isWord);
				ran = true; //Make bool statement true for deleting a letter from word		
			}
			givenWord = word; //Restart givenWord and continue onto the next letter in string
		}			
	}else if((!ht.find(word)) && (!ran)){ //If no word is found and ran is still false, make vector empty
		result.clear();
	}

	sort(result.begin(),result.end()); //Sort the vector in alphabetical order
	return result;	
}

vector<string> transposition(const HashTable & ht, string word){

	vector<string> result;
	string givenWord = "";
	givenWord = word; //Assign word into givenWord	
	bool ran = false;

	if(ht.find(word)){ //If word is in the file, insert word into vector 
		result.push_back(word);
	}else if((!ht.find(word))){ //If word is not found in file, but potentially find options stated in question  
		for(int i = 0; i < givenWord.size(); i++){
			swap(givenWord[i],givenWord[i+1]); //Swap current letter of string with the next letter in the string
			if(ht.find(givenWord)){ //If the word is in the file store into vector
				result.push_back(givenWord);
				ran = true;	//Make bool statement true for deleting a letter from word		
			}
			givenWord = word; //Restart givenWord and continue onto the next letter in string	
		}	
	}else if((!ht.find(word)) && (!ran)){ //If no word is found and ran is still false, make vector empty
		result.clear();
	}

	return result;
}

vector<string> missingSpace(const HashTable & ht, string word){

	vector<string> result;
	string givenWord = "";
	givenWord = word;	
	string wordOne = ""; //Assign string before string
	string wordTwo = ""; //Assign string after string
	int index = 1; //Place space at 1 (No need to put at zero or end of array for string will be word)
	int space = 0; //Int value to find (from string library) to see where space is in the string
	bool ran = false;		

	if(ht.find(word)){ //If word is in the file, insert word into vector 
		result.push_back(word);
	}else if((!ht.find(word))){ //If word is not found in file, but potentially find options stated in question  
		while(index < word.size()){ //Loop for each epace in word
			givenWord.insert(index, " "); //Insert the space
			space = givenWord.find(" "); //Assign the current spot of find in the string
			int afterSpace = space + 1; //Create and index for after the area where space is 
			for(int i = 0; i < space; i++){ //Get the letters involving the first letters before the space
				wordOne += givenWord[i];
			}
			for(int i = afterSpace; i < givenWord.size(); i++){ //Get the letters after the space before the end of the string 
				wordTwo += givenWord[i];
			}

			if(ht.find(wordOne) && ht.find(wordTwo)){ //Now put both strings in the find function from the Hash Table class
				result.push_back(givenWord); //If strings are words then insert into vector
				ran = true;
			}
			//Restart variables and increase the space in the string
			wordOne = "";
			wordTwo = "";
			givenWord = word;
			index++;		
		}
	}else if((!ht.find(word)) && (!ran)){ //If no word is found and ran is still false, make vector empty
		result.clear();
	}	
	
	return result;
}

vector<string> missingLetter(const HashTable & ht, string word){

	vector<string> result;
	string givenWord = ""; 
	givenWord = word;
	bool ran = false;
	char letter = 97; //97 represents the letter 'a' in ASCII
	
	if(ht.find(word)){ //If word is in the file, insert word into vector 
		result.push_back(word);
	}else if((!ht.find(word))){ //If word is not found in file, but potentially find options stated in question  
		for(int i = 0; i <= word.size(); i++){ //For the i represents the current spot of the string
			while(letter <= 122){ //A while to check every letter a - z (97 - 122)
				givenWord.insert(i, 1, letter); // Insert the letter in the current spot of i
				if(ht.find(givenWord)){ // If its a word insert into vector
					result.push_back(givenWord);
					ran = true; //Make bool statement true for finding a word with the letter
				}
				givenWord = word; //restart the word
				letter++; //go to next letter till z
			}
			givenWord = word; //restart the word
			letter = 97; //restart letter
		}
	}else if((!ht.find(word)) && (!ran)){ //If no word is found and ran is still false, make vector empty
		result.clear();
	}	

	sort(result.begin(),result.end()); //Sort the vector in alphabetical order
	return result;
}

vector<string> incorrectLetter(const HashTable & ht, string word){

	vector<string> result;
	string givenWord = "";
	givenWord = word;
	bool ran = false;
	char letter = 97; //97 represents the letter 'a' in ASCII

	if(ht.find(word)){ //If word is in the file, insert word into vector 
		result.push_back(word);
	}else if((!ht.find(word))){ //If word is not found in file, but potentially find options stated in question  
		for(int i = 0; i < word.size(); i++){ //index for each letter in word
			givenWord.erase(i, 1); //removes current letter of the string
			while(letter <= 122){
				givenWord.insert(i, 1, letter); //inserts a new letter in the current index, and attempts a - z in that current spot
				if(ht.find(givenWord)){ //If word store into vector
					result.push_back(givenWord);
					ran = true; //Make bool statement true for finding a word with the letter
				}
				givenWord = word; //restart word by removing the letter we tested
				letter++; // increase letter
				givenWord.erase(i, 1); //erase current spot again and loop back to try new letter
			}
			givenWord = word; // restart whole word
			letter = 97; //restart letter	
		}
	}else if((!ht.find(word)) && (!ran)){ //If no word is found and ran is still false, make vector empty
		result.clear();
	}

	sort(result.begin(),result.end()); //Sort the vector in alphabetical order
	return result;
}