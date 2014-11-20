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
		int position = hash(key);
		Node* current = map[position];
		if (current == NULL){//IF BUCKET COMPLETELY EMPTY!!!!
			current = new Node();
			current->key = key;
			current->value = value;
			map[position] = current;
			++SIZE;
			return true;
		}
		else{
			int i = 1;
			while (current->next != NULL && current->key != key){
				current = current->next;
			}
			if (current->next == NULL){//if no matching key was found, create a new link
				current->next = new Node();
				current = current->next;
				current->key = key;
				current->value = value;
			}
			else{//if matching key was found, replace the value. 
				current->value = value;
			}
			++SIZE;
			return true;
		}
	}

	bool remove(int key, char &value){//remove an item from the map
		int position = hash(key);
		Node* current = map[position];
		Node* temp;
		if (current->key == key){
			value = current->value;
			temp = current->next;
			delete current;
			map[position] = temp;
			--SIZE;
			return true;
		}
		while (current->next != NULL){
			if (current->next->key == key){
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
	bool search(int key, char &value){//search for a value in the map
		int position = hash(key);
		Node * current = map[position];
		Node* current = map[position];
		Node* temp;
		if (current->key == key){
			value = current->value;
			return true;
		}
		while (current->next != NULL){
			if (current->next->key == key){
				temp = current->next;
				value = temp->value;
				return true;
			}
			current = current->next;
		}
		return false;
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
		Node * current;
		for (int i = 0; i < CAPACITY; ++i){
			current = map[i];
			out << "Bucket: " << i << " - ";
			while (current != NULL){
				out << "  [Key: " << current->key << " Value: " << current->value << "]  - ";
				current = current->next;
			}
			out << "\n";
		}
		return out;
	}


private:
	int hash(int key){
		//h(k, i) = f(k) + p(i) % M
		return ((key) % CAPACITY);
	}
}
;