#include <iostream>
#include <ostream>
template <typename K, typename V>
class RBST{
private:
	struct Node{
		int right = -1;
		int left = -1;
		V value;
		K key;
	};
	std::size_t SIZE = 0;
	std::size_t CAPACITY;
	int freelist = 0;
	int root = -1;
	Node ** map;
public:
	RBST(int capacity){
		map = new Node*[capacity]; 
		for (int i = 0; i < capacity; ++i){
			map[i] = new Node;
			if (i < capacity - 1){
				map[i]->left = i + 1;
			}
			else{
				map[i]->left = -1;
			}
		}
		CAPACITY = capacity;
	}

	~RBST(){}

	int insert(K key, V value){
		int v = 0;
		if (root == -1){
			root = freelist;
			map[freelist]->value = value;
			map[freelist]->key = key;
			int i = map[freelist]->left;
			map[freelist]->left = -1;
			map[freelist]->right = -1;
			freelist = i;
			++SIZE;
			return 0;//ROOT NULL, CREATE ROOT AND RETURN 0
		}
		int current = root;
		int previous = root;
		while (current != -1){
			if (compareTo(map[current]->key, key)){//if the ket already exist
				++v;//visited another node
				std::cout << "KEY IS EQUAL" << endl;
				map[current]->value = value;
				return v;//KEY = KEY REPLACE VALUE AND RETURN V
			}
			else if (greater(map[current]->key, key)){
				++v;//visited another node
				std::cout << "ITEM IS GREATER" << endl;
				previous = current;
				current = map[current]->right;//moving right
				if (current == -1 && freelist != -1){
					map[previous]->right = freelist;
					current = map[previous]->right;
					break;
				}
			}
			else{
				++v;//visited another node
				std::cout << "ITEM IS LESS" << endl;
				previous = current;
				current = map[current]->left;//moving left
				if (current == -1 && freelist != -1){
					map[previous]->left = freelist;
					current = map[previous]->left;
					break;
				}
			}
		}
		if (freelist == -1){
			std::cout << "Getting to Neg" << endl;
			return -1 * v;
		}
		freelist = map[freelist]->left;
		map[current]->value = value;
		map[current]->key = key; 
		map[current]->left = -1;
		map[current]->right = -1;
		++SIZE;
		return v;
	}


	int search(K key, V& value){
		int v = 0;
		int current = root;
		while (current != -1){
			if (compareTo(map[current]->key, key)){
				value = map[current]->value;
				return v;
			}
			if (greater(map[current]->key, key)){
				current = map[current]->right;
			}
			else{
				current = map[current]->left;
			}
			++v;
		}
		return v;
	}

	std::ostream& printArray(std::ostream& out){
		out << endl;
		for (int i = 0; i < CAPACITY; ++i){
			out << "Array: " << i << endl;
			out << "Left: " << map[i]->left << "   Right: " << map[i]->right << endl << endl;
		}
		return out;
	}

	std::size_t size(){
		return SIZE;
	}
	
	std::size_t capacity(){
		return CAPACITY;
	}

	std::double_t load(){
		return(double(SIZE) / CAPACITY);
	}

	bool isEmpty() {
		return SIZE == 0;
	}

	void clear(){
		for (int i = 0; i < CAPACITY; ++i){
			delete map[i];
		}
		for (int i = 0; i < capacity; ++i){
			map[i] = new Node;
			if (i < capacity - 1){
				map[i]->left = i + 1;
			}
			else{
				map[i]->left = -1;
			}
		}
		SIZE = 0;
	}
	std::ostream& print(std::ostream& out){

		out << "\n--------------------\n";
		int current = freelist;
		while(current != -1){
			cout << map[current]->left;
			current = map[current]->left;
		}
		out << "\n--------------------\n";

		printHelp(out, root);
		return out;
	}

	std::ostream& printHelp(std::ostream& out, int current){
		if (current == -1){
			return out;
		}
		out <<"Node: " << current << " | Key: " << map[current]->key << " | Value: " << map[current]->value << " | Left: " << map[current]->left << " | Right: " << map[current]->right << endl;
		printHelp(out, map[current]->left);
		printHelp(out, map[current]->right);
		
	}
	
	
private:

//-----------------------EQUAL TO OPERATOR----------------------//
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

//-----------------------GREATER THAN OPERATOR---------------//
	bool greater(string a, string b){
		if (strcmp(a.c_str(), b.c_str()) < 0){
			return true;
		}
		return false;
	}

	bool greater(char const* a, char const* b){
		if (strcmp(a, b) < 0){
			return true;
		}
		return false;
	}

	bool greater(double a, double b){
		return a < b;
	}

	bool greater(int a, int b){
		return a < b;
	}


};