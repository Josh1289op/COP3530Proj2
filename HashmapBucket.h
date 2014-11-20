#include <iostream>
#include <ostream>

class HashmapBucket{

private:
	struct Node{
		int key;
		char value;
		Node* next = NULL;

	};
	Node** map;
	int SIZE;
	int CAPACITY;

		
public:
	HashmapBucket(int size){
		map = new Node*[size];
		for (int i = 0; i < size; ++i){
			map[i] = NULL;
		}
		SIZE = 0;
		CAPACITY = size;
	}
	~HashmapBucket(){

	}

	bool insert(int key, char value){//insert a value into the map
		int position = hash(key, 0);
		Node* current = map[position];
		if (current == NULL){//IF BUCKET COMPLETELY EMPTY!!!!
			current = new Node;
			current->key = key;
			current->value = value;
		}
		else{
			while (current->next != NULL && current->key != key){
				current = current->next;
			}
			if (current->next == NULL){//if no matching key was found, create a new link
				current->next = new Node;
				current = current->next;
				current->key = key;
				current->value = value;
			}
			else{//if matching key was found, replace the value. 
				current->value = value;
			}
			return true;
		}
	}

	bool remove(int key, char &value){//remove an item from the map

	}
	bool search(int key, char &value){//search for a value in the map
		
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

	std::ostream& print(std::ostream& out) const {

	}


private:
	int hash(int key, int i){
		//h(k, i) = f(k) + p(i) % M
		return ((key + i) % CAPACITY);
	}
}
;