#include <iostream>
#include <ostream>
#include <cstring>
#include <string>
#include <vector>

#include <typeinfo>


using namespace std;
template <typename K, typename V>
class Hashmap{

private:
	struct Node{
		K key;
		V value;
	};
	Node ** map;
	int SIZE;
	int CAPACITY;
	int PROBE;
public:
	Hashmap(int size, int probe){
		map = new Node*[size];
		for (int i = 0; i < size; ++i){
			map[i] = NULL;
		}
		SIZE = 0;
		CAPACITY = size;
		PROBE = probe;
	}

		
	~Hashmap(){

	}

	int insert(K key, V value){//insert a value into the map
		int i = 0;
		int position = hash(key, i);
		if (map[position] == NULL){
			map[position] = new Node;
			++SIZE;
			map[position]->key = key;
			map[position]->value = value;
		}
		else{
			while (true){
				if (i == CAPACITY){ //if we've probed too many times. FAIL! 
					return (-1 * i);
				}
				if (map[position] != NULL){
					if (compareTo(map[position]->key, key)){
						break; //this key exist, break  or empty position found
					}
				}
				position = hash(key, ++i);
				if (map[position] == NULL){
					++SIZE;
					map[position] = new Node;
					break;
				}
			}
			map[position]->value = value;
			map[position]->key = key;
		}
		return i;
	}

	int remove(K key, V &value){//remove an item from the map
		int i = 0;
		int position = hash(key, i);
		while (true){
			if (compareTo(map[position]->key, key) || map[position] == NULL || i > CAPACITY){
				break;
			}
			position = hash(key, ++i);
		}
		if (map[position] == NULL){//IF MAP POSITION == NULL, THEY KEY ISN'T IN THE MAP
			return (-1 * i);
		}
		else{//RETURN THE VALUE
			value = map[position]->value;//RETURNING VALUE
			delete map[position];//DELETING OLD NODE
			map[position] = NULL;//SETTING OLD POSITION TO NODE(BASE VALUE)
			--SIZE;//DECREASING SIZE
			int tempI = i; //NUMBER OF PROBE ATTEMPTS TO FIND THE KEY
			while (true){//NOW REDISTRIBUTE CLUSTER
				position = hash(key, ++tempI);
				if (map[position] == NULL){
					break;
				}
				V tempValue = map[position]->value;
				K tempKey = map[position]->key;
				delete map[position];
				map[position] = NULL;
				--SIZE;
				insert(tempKey, tempValue);
			}
		}

		return i;//RETURN AMOUNT OF PROBE TIMES
	}
	int search(K key, V &value){//search for a value in the map
		int i = 0;
		int position = hash(key, i);
		while (true){
			if (compareTo(map[position]->key, key)){
				value = map[position]->value;
				return i;
			}
			int position = hash(key, ++i);
		}

		return i;
	}
	void clear(){//clear the whole map
		
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

	std::ostream& print(std::ostream& out) {
		out << "Hash Map: " << endl << "Size: " << SIZE << endl << "Capacity: " << CAPACITY << endl << "Load: ";
		out << load() << endl << endl;	
		out << "  KEY : VALUE  \n";
		out << "  -----------\n";
		for (int i = 0; i < CAPACITY; ++i){
			if (map[i] != NULL){
				out << setw(5) << map[i]->key << " : " << map[i]->value << endl;
			}
			else{
				out << setw(8) << " : " << endl;
			}
		}

		return out;
	}


private: 
	//------------------------------------PROBING FUNCTION------------------------------------------------
	int probe(int key, int i) {//DEPENDING ON THE HASHING SETTING, DENOTES WHICH FUNCTION WE WILL USE
		if (PROBE == 0) { //LINEAR
			return i; 
		}
		else if (PROBE == 1) { //QUADRATIC 
			return i*i; 
		}
		else { //double hash
			return ((key * i) + i); 
		}
	}
	//-----------------------------------------------------------------------------------------------------


	//------MAIN HASHING FUNCTION--------------------------------
	int hash(int key, int i){//INT HASH
		//h(k, i) = f(k) + p(i) % M
		return ((key + probe(key, i)) % CAPACITY);
	}
	//-----------------------------------------------------------


	int hash(double key, int i){//DOUBLE HASH
		int count = 0;
		while (true){
			key *= 10;
			if (static_cast<long>(key) % 10 == 0){
				break;
			}
			++count;
		}
		count = (int(key) * count) / 10;
		return hash(count, i);
	}


	int hash(string key, int i){//STRING HASH
		//convert strings to c strings and calculate the position that way. 
		char const* cstring = key.c_str();
		return hash(cstring, i);
	}

	int hash(char const* key, int i){//Cstring HASH
		int j = 0;
		int intKey = 0;
		while (key[j] != NULL){
			intKey += key[j] + j;
			++j;
		}
		return hash(intKey, i);
	}

	bool compareTo(string a, string b){
		return (strcmp(a.c_str(), b.c_str()) == 0);
	}

	bool compareTo(char const* a, char const* b){
		return strcmp(a, b) == 0;
	}
	bool compareTo(double a, double b){
		return a == b;
	}
	bool compareTo(int a, int b){
		return a == b;
	}

};