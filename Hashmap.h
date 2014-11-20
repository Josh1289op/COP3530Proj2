#include <iostream>
#include <ostream>

class Hashmap{

private:
	int* keys;
	char* values;
	int SIZE;
	int CAPACITY;
	char valueEmpty = '-';
	int keyEmpty = -1;
public:
	Hashmap(int size){
		keys = new int[size];
		values = new char[size];
		SIZE = 0;
		CAPACITY = size;
		for (int i = 0; i < size; ++i){
			keys[i] = keyEmpty;
			values[i] = valueEmpty;
		}
	}
	~Hashmap(){

	}

	bool insert(int key, char value){//insert a value into the map
		int i = 0;
		while (i < CAPACITY){
			int position = hash(key, i++);
			if (values[position] == valueEmpty || keys[position] == key){
				keys[position] = key;
				values[position] = value;
				++SIZE;
				return true;
			}
		}
		return false;
	}

	bool remove(int key, char &value){//remove an item from the map
		int position = hash(key, 0);
		int start = position;
		while (keys[position] != key && values[position] != valueEmpty){
			if (position == CAPACITY - 1){
				position = 0;
			}
			else{
				++position;
			}
			if (position == start){ //if we are at the end of the array, go to zero.
				return false;
			}
		}
		if (values[position] == valueEmpty){
			return false;
		}
		else{//return the removed item, and reorder the list
			value = values[position];
			values[position] = valueEmpty;
			keys[position] = keyEmpty;
			--SIZE;
			if (position == CAPACITY - 1){
				position = 0;
			}
			else{
				++position;
			}
			if (position == start){ //if we are at the end of the array, go to zero.
				return true;
			}
			while (values[position] != valueEmpty){
				char tempValue = values[position];
				int tempKey = keys[position];
				
				values[position] = valueEmpty;
				keys[position] = keyEmpty;
				
				insert(tempKey, tempValue);
				
				if (position == CAPACITY - 1){
					position = 0;
				}
				else{
					++position;
				}
				--SIZE;
				if (position == start){ //if we are at the end of the array, go to zero.
					break;
				}
			}
			--SIZE;
			return true;
		}

	}
	bool search(int key, char &value){//search for a value in the map
		int position = hash(key, 0);
		int start = position;
		while (keys[position] != key && values[position] != valueEmpty ){
			position >= CAPACITY ? 0 : ++position; // if not in the right place go to the next position
			if (position == start){ //if we are at the end of the array, go to zero.
				return false;
			}
		}
		if (values[position] == valueEmpty){
			return false;
		}
		else{
			value = values[position];
			return true;
		}
	}
	void clear(){//clear the whole map
		delete[] keys;
		delete[] values;
		keys = new int[SIZE];
		values = new char[SIZE];
	}

	bool is_empty(){//is the map empty?
		return SIZE == 0;
	}

	std::size_t capacity(){//size of the map?
		return CAPACITY;
	}

	std::size_t size(){//amount of items in the map?
		return SIZE;
	}

	double load(){//size = load * capacity
		return double(SIZE) / CAPACITY;
	}

	std::ostream& print(std::ostream& out) const {
		out << "Capacity: " << CAPACITY << "  " << "SIZE: " << SIZE << "\n";
		out << "k : v\n-----\n";
		for (int i = 0; i < CAPACITY; ++i){
			if (keys[i] == -1){
				out << "-";
			}
			else{
				out << keys[i];
			}
			out << " : " << values[i] << "\n";
		}
		return out;
	}


private: 
	int hash(int key, int i){
		//h(k, i) = f(k) + p(i) % M
		return ((key + i) % CAPACITY);
	}
}
;