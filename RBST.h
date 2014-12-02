#include <iostream>
#include <ostream>
#include <queue>
#include <string> 
#include <stdio.h>
#include <cstdlib>
#include <sstream>
#include <cstring>
#include <string>
#include <vector>
#include <time.h>
#include <typeinfo>
template <typename K, typename V>
class RBST{
private:
	struct Node{
		int right;
		int left;
		V value;
		K key;
	};
	std::size_t SIZE;
	std::size_t CAPACITY;
	int freelist;
	int root;
	Node ** map;
public:
	RBST(int capacity){
		srand(time(NULL));
		map = new Node*[capacity];
		for (int i = 0; i < capacity; ++i){
			map[i] = new Node;
			if (i < capacity - 1){
				map[i]->right = -1;
				map[i]->left = i + 1;
			}
			else{
				map[i]->right = -1;
				map[i]->left = -1;
			}
		}
		freelist = 0;
		root = -1;
		SIZE = 0;
		CAPACITY = capacity;
	}

	~RBST(){}

	int insert(K key, V value){
		//get random number and decide whether or not to enter at root or leaf node
		int v = 0; // NODES VISITED
		//if the root index is null, insert at root.
		for (int i = 0; i < CAPACITY; ++i){
			++v;
			if (compareTo(map[i]->key, key)){
				map[i]->value = value;
				return v;
			}
		}
		v = 0;
		if (root == -1) {//root is empty
			root = freelist;
			freelist = map[freelist]->left;
			map[root]->left = -1;
			map[root]->right = -1;
			map[root]->key = key;
			map[root]->value = value;
		}
		else{
			int random = rand() % 10;
			if (random == 0){//insert at root
				std::cout << "ROOT INSERT" << std::endl;
				v = insertAtRoot(root, key, value, v);
			}
			else{//insert at leaf node
				v = insertAtLeaf(root, key, value, v);
			}
		}
		return v;
	}

	int remove(K key, V& value){
		int v = 0;
		int parent = 0;
		if (compareTo(map[root]->key, key)){
			parent = root;
			return removeRoot();
		}
		else{
			parent = findNode(key, root, v);//returns the parent to the key
		}
		int child = -1;//initialize the child
		bool left = true;
		if (parent == -1){//didn't find anything.
			return -1 * v;
		}
		if (greater(map[parent]->key, key)){//which child are you
			child = map[parent]->right;
			left = false;
		}
		else{
			child = map[parent]->left;
		}
		std::cout << "Parent: " << parent << " Child:" << child << " value:" << map[child]->value << std::endl;
		//CASE1: if node has no children
		if (map[child]->right == -1 && map[child]->left == -1){
			value = map[child]->value;
			left ? map[parent]->left = -1 : map[parent]->right = -1;
			pushFrontFreelist(child);
		}
		//CASE2: if node has only one child
		else if ((map[child]->right == -1) != (map[child]->left == -1)){
			value = map[child]->value;
			if (map[child]->right != -1){//we have a right child
				left ? map[parent]->left = map[child]->right : map[parent]->right = map[child]->right;
				pushFrontFreelist(child);
			}
			else{//map[child]->left != -1 // we have a left child
				left ? map[parent]->left = map[child]->left : map[parent]->right = map[child]->left;
				pushFrontFreelist(child);
			}

		}
		//CASE3: AHHHH node has two children
		else{
			int min = map[child]->right;
			findMin(map[child]->right, min);
			value = map[child]->value;
			K tempKey = map[min]->key;
			map[child]->value = map[min]->value;
			printArray(std::cout);
			V placeholder;

			remove(min, placeholder);
			map[child]->key = tempKey;

		}
		return v + 1;
	}



	void findMin(int parent, int& min){
		if (greater(map[parent]->key, map[min]->key)){
			min = parent;
		}
		if (map[parent]->right != -1){
			findMin(map[parent]->right, min);
		}
		if (map[parent]->left != -1){
			findMin(map[parent]->left, min);
		}

	}

	int findNode(K key, int parent, int& v){//RECURSIVE SEARCHING FUNCTION. RETURNS ARRAY POSITION OF KEY VALUE
		++v;
		if (greater(map[parent]->key, key)){
			if (map[parent]->right != -1){
				if (compareTo(map[map[parent]->right]->key, key)){
					return parent;
				}
				else{
					return findNode(key, map[parent]->right, v);
				}
			}
			return -1;
		}
		else{
			if (map[parent]->left != -1){
				if (compareTo(map[map[parent]->left]->key, key)){
					return parent;
				}
				else{
					return findNode(key, map[parent]->left, v);
				}
			}
			return -1;
		}




	}

	int search(K key, V& value){
		int v = 0;
		int parent = 0;
		if (compareTo(map[root]->key, key)){
			parent = root;
		}
		else{
			parent = findNode(key, root, v);//returns the parent to the key
		}
		int child = -1;//initialize the child
		bool left = true;
		if (parent == -1){//didn't find anything.
			return -1 * v;
		}
		if (greater(map[parent]->key, key)){//which child are you
			child = map[parent]->right;
			left = false;
		}
		else{
			child = map[parent]->left;
		}
	}

	std::ostream& printArray(std::ostream& out){
		out << "Root: " << root << std::endl;
		out << "Freelist " << freelist << std::endl;
		for (int i = 0; i < CAPACITY; ++i){
			out << "Index: " << i << "  Key: " << map[i]->key << "  Value: " << map[i]->value << "  Left: " << map[i]->left << "  Right: " << map[i]->right << std::endl;
		}

		printArrayHelper(out, root);

		out << "\n\n";
		return out;
	}

	std::ostream& printArrayHelper(std::ostream& out, int parent){
		std::queue<int> que = std::queue<int>();
		out << "[";
		que.push(parent);//prime
		while (!que.empty()){
			int n = que.front();
			que.pop();
			if (n != -1){
				out << map[n]->key;
				que.push(map[n]->left);
				que.push(map[n]->right);
			}
			else{
				out << "-";
			}
			if (!que.empty()){
				out << ", ";
			}
			else{
				out << "]\n\n";
			}
		}
		return out;

	}

	std::size_t size(){
		return SIZE;
	}

	std::size_t capacity(){
		return CAPACITY;
	}

	double load(){
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


private:

	int insertAtLeaf(int parent, K key, V value, int v){
		++v;
		if (greater(map[parent]->key, key)){
			if (map[parent]->right == -1 && freelist != -1){
				//if the right is empty and theres a node avail, put the next freenode there and move freenode
				map[parent]->right = freelist;//giving right child freenode
				freelist = map[freelist]->left;//giving freelist the next free, it gets -1 if there is no free.
				int child = map[parent]->right;
				map[child]->right = -1;
				map[child]->left = -1;
				map[child]->value = value;
				map[child]->key = key;
				++SIZE;//ITEM WAS ADDED
				return v;//RETURN VISITED NODES
			}
			else if (map[parent]->right == -1){
				return -1 * v; //NO ROOM FOR NODE
			}
			else{
				return insertAtLeaf(map[parent]->right, key, value, v);// move on to find next free
			}
		}
		else{//key, less than parent key moving left
			if (map[parent]->left == -1 && freelist != -1){
				//if the right is empty and theres a node avail, put the next freenode there and move freenode
				map[parent]->left = freelist;//giving right child freenode
				freelist = map[freelist]->left;//giving freelist the next free, it gets -1 if there is no free.
				int child = map[parent]->left;
				map[child]->right = -1;
				map[child]->left = -1;
				map[child]->value = value;
				map[child]->key = key;
				++SIZE;//ITEM WAS ADDED
				return v;//RETURN VISITED NODES
			}
			else if (map[parent]->left == -1){
				return -1 * v; //NO ROOM FOR NODE
			}
			else{
				return insertAtLeaf(map[parent]->left, key, value, v);// move on to find next free
			}
		}
		return v;
	}


	int insertAtRoot(int parent, K key, V value, int v){
		std::cout << "INSERTING AT ROOT " << std::endl;
		++v;
		if (greater(map[parent]->key, key)){
			if (map[parent]->right == -1 && freelist != -1){
				std::cout << "Going right" << std::endl;
				//if the right is empty and theres a node avail, put the next freenode there and move freenode
				map[parent]->right = freelist;//giving right child freenode
				freelist = map[freelist]->left;//giving freelist the next free, it gets -1 if there is no free.
				int child = map[parent]->right;
				map[child]->right = -1;
				map[child]->left = -1;
				map[child]->value = value;
				map[child]->key = key;
				++SIZE;//ITEM WAS ADDED
				rotateLeft(parent);
				return v;//RETURN VISITED NODES
			}
			else if (map[parent]->right == -1){
				return -1 * v; //NO ROOM FOR NODE
			}
			else{
				v = insertAtRoot(map[parent]->right, key, value, v);// move on to find next free
				rotateLeft(parent);//before returning, rotate back up, in the oposite direction
				return v;
			}
		}
		else{//key, less than parent key moving left
			if (map[parent]->left == -1 && freelist != -1){
				std::cout << "Going left" << std::endl;
				//if the right is empty and theres a node avail, put the next freenode there and move freenode
				map[parent]->left = freelist;//giving right child freenode
				freelist = map[freelist]->left;//giving freelist the next free, it gets -1 if there is no free.
				int child = map[parent]->left;
				map[child]->right = -1;
				map[child]->left = -1;
				map[child]->value = value;
				map[child]->key = key;
				++SIZE;//ITEM WAS ADDED
				rotateRight(parent);
				return v;//RETURN VISITED NODES
			}
			else if (map[parent]->left == -1){
				std::cout << "No Nodes Left" << std::endl;
				return -1 * v; //NO ROOM FOR NODE
			}
			else{
				v = insertAtRoot(map[parent]->left, key, value, v);// move on to find next free
				rotateRight(parent);//before returning, rotate back up, in the oposite direction
				return v;
			}
		}
		return v;
		return 0;
	}

	void rotateRight(int parent){
		int temp = map[parent]->left;//get the left childs address
		Node * swap = map[temp];// save the left child's Node
		map[temp] = map[parent];// swap the left child with parent Node
		map[parent] = swap;//save the left child in the old slot (Parent's parent now points here)

		map[temp]->left = map[parent]->right;//point old parent right to old parent
		map[parent]->right = temp;// 

	}

	void rotateLeft(int parent){
		std::cout << "rotating left " << std::endl;
		int temp = map[parent]->right;//get the right childs address
		Node * swap = map[temp];// save the right child's Node
		map[temp] = map[parent];// swap the right child with parent Node
		map[parent] = swap;//save the right child in the old slot (Parent's parent now points here)

		map[temp]->right = map[parent]->left;//point old parent left to old parent
		map[parent]->left = temp;// 

	}

	void pushFrontFreelist(int i){
		map[i]->right = -1;
		map[i]->left = freelist;
		map[i]->key = 0;
		map[i]->value = 0;
		freelist = i;
	}

	int removeRoot(){
		std::cout << "removing root" << std::endl;
		return 0;
	}

	//-----------------------EQUAL TO OPERATOR----------------------//
	bool compareTo(std::string a, std::string b){
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
	bool greater(std::string a, std::string b){
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