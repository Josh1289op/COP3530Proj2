#include <iostream>
#include <ostream>
#include <cstdlib>
template <typename K, typename V>
class HashmapBucket{

private:
	struct Node{
		K key;
		V value;
		Node* next = NULL;

	};
	Node** map;
	int SIZE;
	int OCCUPIED;
	int CAPACITY;

		
public:
	HashmapBucket(int size){
		map = new Node*[size];
		for (int i = 0; i < size; ++i){
			map[i] = NULL;
		}
		SIZE = 0;
		OCCUPIED = 0;
		CAPACITY = size;
	}
	~HashmapBucket(){

	}

	bool inmainrt(K key, V value){//insert a value into the map
		int position = hash(key);
		Node* current = map[position];
		std::cout << "inserting: " << endl;
		if (current == NULL){//IF BUCKET COMPLETELY EMPTY!!!!
			current = new Node();
			current->key = key;
			current->value = value;
			map[position] = current;
			++OCCUPIED;
			++SIZE;
			return true;
		}
		else{
			int i = 1;
			std::cout << "BLAH: " << current->key << "   " << key << endl;

			while (current->next != NULL && !compareTo(current->key, key)){
				std::cout << current->key << "   " << key << endl;
				current = current->next;
			}			std::cout << "BLAH: " << current->key << "   " << key << endl;

			std::cout << "BLAH: " << current->key << "   " << key << endl;

			if (compareTo(current->key, key)){//if matching key was found, replace the value. 
				current->value = value;
			}
			else{//if no matching key was found, create a new link

				current->next = new Node();
				current = current->next;
				current->key = key;
				current->value = value;
			}
			++SIZE;
			return true;
		}
	}

	bool remove(K key, V &value){//remove an item from the map
		int position = hash(key);
		Node* current = map[position];
		Node* temp;
		if (compareTo(current->key, key)){// if the first item in the bucket is the item i need
			value = current->value;
			temp = current->next;
			if (temp == NULL){ --OCCUPIED; } // If the first item is the last item, --OCCUPIED
			delete current;
			map[position] = temp;
			--SIZE;
			return true;
		}
		while (current->next != NULL){
			if (compareTo(current->next->key, key)){
				temp = current->next;
				value = temp->value;
				temp = temp->next;
				delete current->next;
				current->next = temp;
				--SIZE;
				return true;
			}
			current = current->next;
		}
		return false;
	}
	bool search(K key, V &value){//search for a value in the map
		int position = hash(key);
		Node * current = map[position];
		Node* temp;
		if (compareTo(current->key == key)){
			value = current->value;
			return true;
		}
		while (current->next != NULL){
			if (compareTo(current->next->key, key)){
				temp = current->next;
				value = temp->value;
				return true;
			}
			current = current->next;
		}
		return false;
	}


	void clear(){//clear the whole map
		for (int i = 0; i < CAPACITY; ++i){
			Node * current = map[i];
			Node * temp = current;
			while (current != NULL){
				temp = current;
				current = current->next;
				delete temp;
			}
		}
		delete[] map;
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
		return double(OCCUPIED) / CAPACITY;
	}

	std::ostream& print(std::ostream& out) const {
		Node * current;
		for (int i = 0; i < CAPACITY; ++i){
			current = map[i];
			out << "Bucket: " << i << " - ";
			while (current != NULL){
				out << "  [Key: " << current->key << " | Value: " << current->value << "]  - ";
				current = current->next;
			}
			out << "\n";
		}
		return out;
	}


	K remove_random(){
		srand(time(NULL));
		int r = rand() % CAPACITY;
		while (map[r] == NULL){
			r = rand() % CAPACITY;
		}
		std::cout << r << std::endl;
		K key = map[r]->key;
		V myValue;
		Node * temp = map[r];
		map[r] = map[r]->next;
		delete temp;
		return key;
	}

private:
	//------MAIN HASHING FUNCTION--------------------------------
	int hash(int key){//INT HASH
		//h(k, i) = f(k) + p(i) % M
		return (key % CAPACITY);
	}
	//-----------------------------------------------------------


	int hash(double key){//DOUBLE HASH
		int count = 0;
		while (true){
			key *= 10;
			if (static_cast<long>(key) % 10 == 0){
				break;
			}
			++count;
		}
		count = (int(key) * count) / 10;
		return hash(count);
	}


	int hash(string key){//STRING HASH
		//convert strings to c strings and calculate the position that way. 
		char const* cstring = key.c_str();
		return hash(cstring);
	}

	int hash(char const* key){//Cstring HASH
		int j = 0;
		int intKey = 0;
		while (key[j] != NULL){
			intKey += key[j] + j;
			++j;
		}
		return hash(intKey);
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
}
;