#include "HashTable.h"
#include <string>

using namespace std;

//default constructor 
HashTable::HashTable(){
	
	currentSize = 0; // Initialize the currentSize variable to 0
	arrSize = 101; // Set array size to default 101	
	arr = new string[arrSize]; // Assign size to the arr

	for(int i = 0; i < arrSize; i++){ // Set all array elements to the empty string
		arr[i] = "";
	}

	//Sets the value used for secondHash function
	valueTwo = (arrSize / 2);  
	valueTwo += 1; // Plus one for it will always be greater 
	valueTwo = getPrime(valueTwo); // Get the prime number through helper function getPrime
}

//constructor
HashTable::HashTable(int n){

	int newSize = 0; 
	newSize = n * 2; // Size of underlying array is multiplied by 2 
	currentSize = 0; 
	arrSize = getPrime(newSize); // Get the greatest or equal number closest to the result of n * 2

	arr = new string[arrSize]; // Assign the size to the array

	for(int i = 0; i < arrSize; i++){ // Set all array elements to the empty string
		arr[i] = ""; 
	}

	//Sets the value used for secondHash function
	valueTwo = (arrSize / 2);
	valueTwo += 1;
	valueTwo = getPrime(valueTwo);
}

//copy constructor
HashTable::HashTable(const HashTable & ht){
	deepCopy(ht); // Creates a deep copy of its HashTable referenec parameter using the deepCopy helper function	
}

//destructor
HashTable::~HashTable(){
	delete[] arr; // De-allocates any dynamic memory
}

//operator=
HashTable & HashTable::operator= (const HashTable & ht){
	if(this != &ht){ // If the calling object and parameter are not equal
		delete[] arr; // Delete contents of the calling object 
		deepCopy(ht); // Using helper deepCopy will copy to the calling object
	}

	return *this; // Return a reference to the calling object
}

//insert
void HashTable::insert(string value){

	float hashLoad = 0.67; // Used for comparison for the loadFactor() function

	if((!find(value))){ // If find is false (Value not found in hash table), run insert
		if(arr[firstHash(value)] == ""){ // If the index of firstHash(value) result is empty, insert the value into the hash table
			arr[firstHash(value)] = value; // Insert the string into that specific index
			currentSize++; //Raise current size 
			if(loadFactor() > hashLoad){ // Check if the current state of the Hash Table(loadFactor result) is greater than hashLoad value (0.67)
				increaseArray(); // Run helper function increaseArray if that statement is true (Description down below)
			}
		}else{ //If the result of firstHash index is occupied (collision happens) then do double hashing (run secondHash)
			int probeV = secondHash(value); // Result of secondHash to have an increment value
			int index = firstHash(value); // Original index spot that's occupied 
			int count = 0; // A count to keep track of incrementing
			bool run = true; // bool statement to keep the while loop running.
			while(run){ // A while loop with a bool statement true. It will keep running until we can find an open spot
				index += 1; //Increment the index by one ONLY for now in case we access go beyond the arrSize - 1 index
				if(index == arrSize){ //When index == arrSize, make it go back to 0, like a circular array
					index = 0;
				}
				count++; // count follows the incrementing of index += 1, basically the probeV value so we can make sure to not go beyond array size
				if(count == probeV){ // When the count is equal to probeV. Meaning our index is at the point where index += probeV would end up in as well
					if(arr[index] == ""){ // if the spot is empty, put the value in that index
						arr[index] = value;
						currentSize++;
						if(loadFactor() > hashLoad){
							increaseArray();
						}
						run = false; // end while loop for we found an open spot
					}
					count = 0; // else we reset the count and keep looping through the table again until the next spot of index += probeV would end up in
				}
			}
		}	
	}
}

//Find string value in table
bool HashTable::find(string value) const{

	if(arr[firstHash(value)] == value){ // If the initial index of firstHash(value) is equal to the value then the string is in the table
		return true;
	}else if((arr[firstHash(value)] != "") && (arr[firstHash(value)] != value)){ // Else if the spot is occupied and the spot occupied is not the value
		for(int i = 0; i < arrSize; i++){ // 
			int index = ((firstHash(value) + (i * secondHash(value))) % arrSize); // Formula used to find collisions (or in this case duplicates) for double hashing
			if(index > 0 && arr[index] == value){ 								  // Probe sequence formula for double hashing to help find keys / index
				return true;
			}	
		}
	}

	return false;
}

//size
int HashTable::size() const{
	return currentSize; // Return amount of items in table
}

//max of the size
int HashTable::maxSize() const{
	return arrSize; // return hashtable's array size
}

//LoadFactor function | as table fills, the outcome of loadFactor increases which also increases chances of collision
float HashTable::loadFactor() const{

	float value = 0; // Set a return value for the outcome

	float items = currentSize; // Put the current size in a float variable
	float size = arrSize; // Put the size of array in a float variable

	value = items / size; // Compute the value of number of items / table size

	return value;
}

/*

	 HELPER FUNCTIONS DOWN BELOW

*/

// Computing the first hash of the value produces key dependent probe sequences
int HashTable::firstHash(string k) const{

	int result = 0;
	int putString = 0;

	// Using Horner's method, convert the string to an int, and as well mod at same time to
	// reduce overflow
	putString = ((k[0] - 96));

	for(int i = 1; i < k.size(); i++){
		int asc = k[i] - 96;
		putString = ((putString * 32) + asc) % arrSize; // Mod by the array size		
	}	

	result = putString;
	return result;	

}

// Computing the second hash of the value produces key dependent probe sequences
int HashTable::secondHash(string k) const{

	int result = 0;
	int putString = 0;

	// Using Horner's method, convert the string to an int, and as well mod at same time to
	// reduce overflow
	putString = ((k[0] - 96));

	for(int i = 1; i < k.size(); i++){
		int asc = k[i] - 96;
		putString = ((putString * 32) + asc) % valueTwo; // Mod by the p2 value which is h2 stated in the assignment	
	}	

	result = putString;	

	int hashTwo = valueTwo - result; // Do the p2 formula (valueTwo - (k % valueTwo))

	return hashTwo;
}

// Getting the prime number from the resulting given int value 
int HashTable::getPrime(int n) const{

	int count = 0;
	bool increase = true;
	int primeNum = 0;
	int findPrime = n; 
	
	while(increase){ // Keep increasing until found
		for(int i = 2; i <= findPrime; i++){
			if(findPrime % i == 0){ // If findPrime % current i is 0 then add to count
				count++;
			}
		}
		if(count > 1){ // If count is more than one meaning not a prime number (more than one factor)
			findPrime++;
			count = 0;
			increase = true;
		}else{ // If count 1 then it's prime
			increase = false;
		}
	}

	primeNum = findPrime; // return the new number (prime)

	return primeNum;
}

void HashTable::increaseArray(){

	int before = arrSize; // Assign the arrSize to an int value to get all the elements in previous table array
 
	arrSize *= 2; // increase size of array
	arrSize = getPrime(arrSize); // Get prime number
	
	string* temp = arr; // assign original contents to a temp variable
	arr = new string[arrSize]; // make arr the new size

	valueTwo = (arrSize / 2); // Set valueTwo value used for secondHash to new arrSize as well
	valueTwo += 1;
	valueTwo = getPrime(valueTwo);

	for(int i = 0; i < before; i++){ // Make sure to get every element in original arr with arrSize
		if(temp[i] != ""){ // Discard the empty spots
			if(arr[firstHash(temp[i])] == ""){ //Hash the current variable from temp, if empty then add the element back to arr
				arr[firstHash(temp[i])] = temp[i];
			}else if (arr[firstHash(temp[i])] != ""){ // Else if first hash spot is occupied, do same method as insert. Get second hash and increment till open spot
				int probeV = secondHash(temp[i]); 	  	
				int index = firstHash(temp[i]);
				bool run = true;
				int count = 0;
				while(run){
					index += 1;
					if(index == arrSize){
						index = 0;
					}
					count++;
					if(count == probeV){
						if(arr[index] == ""){
							arr[index] = temp[i]; // assign temp into arr spot at index where index += probeV
							run = false; // Stop loop if found
						}
						count = 0; // If not found reset counter
					}
				}
			}
		}
	}

	delete[] temp; // Delete the temp array
}

//Deep copy for copy constructor and operator function
void HashTable::deepCopy(const HashTable & ht){

	arrSize = ht.arrSize; //Copy parameter arrSize to arr
	currentSize = ht.currentSize; // Copy current size
	valueTwo = ht.valueTwo; // Copy the value for secondHash
 
	arr = new string[arrSize]; // make arr the new size

	for(int i = 0; i < arrSize; i++){
		arr[i] = ht.arr[i]; // copy variables from parameter to arr 
	}
}