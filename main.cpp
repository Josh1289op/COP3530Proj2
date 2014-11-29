#define CATCH_CONFIG_MAIN // This tells Catch to provide a main() - only do this in one cpp file
#include "Hashmap.h"
#include "HashmapBucket.h"
#include "RBST.h"
#include "catch/include/catch.hpp"




TEST_CASE("RBST", "WRITING BST CODE"){
	SECTION("GENERAL TESTING"){
		RBST<std::string, int> rbst = RBST<std::string, int>(5);
		
		rbst.printArray(std::cout);
		rbst.print(std::cout);

		cout << "inserting Hello - 6" << endl;
		std::cout << "Hello: " << rbst.insert("Hello", 6) << endl;
		std::cout << rbst.size() << std::endl;
		std::cout << rbst.load() << std::endl;

		cout << "inserting Abs - 7" << endl;
		cout << "Abs: " << rbst.insert("Abs", 7);

		rbst.printArray(std::cout);
		rbst.print(std::cout);


	
		cout << "inserting Zoe - 8" << endl;
		std::cout << "Zoe: " << rbst.insert("Zoe", 8) << endl;
		
		rbst.printArray(std::cout);
		rbst.print(std::cout);

		cout << "inserting Heo - 7" << endl;
		std::cout << "Heo: " << rbst.insert("Heo", 12) << endl;

		rbst.print(std::cout);
		rbst.printArray(std::cout);

		cout << "inserting Chicko - 7" << endl;
		std::cout << "Chicko: " << rbst.insert("Chicko", 12) << endl;

		rbst.print(std::cout);
		rbst.printArray(std::cout);

		int myValue = 0;
		std::cout << "v: " << rbst.search("Chicko", myValue) << endl;
		std::cout << myValue << endl;
	}
}

/*
TEST_CASE("ADDING/REMOVING", "ADDING AND REMOVING FROM HASH, FILL AND EMPTY"){
	SECTION("FILLING"){

		Hashmap<char*, int> hashchar = Hashmap<char*, int>(5, 0);
		hashchar.insert("c", 13);
		hashchar.insert("cs", 15);
		hashchar.insert("d", 200);
		hashchar.insert("h", 120);
		hashchar.print(std::cout);
		std::cout << endl << endl;
		int myValue = 0;
		hashchar.remove("c", myValue);
		std::cout << "Returned Value: " << myValue << endl;
		hashchar.print(std::cout);
		std::cout << endl << endl;
		std::cout << endl << endl;

		Hashmap<std::string, int> hashstring = Hashmap<std::string, int>(5, 0);

		hashstring.insert("l", 5);
		hashstring.print(std::cout);
		hashstring.insert("l", 3);
		hashstring.insert("v", 1);
		hashstring.insert("s", 21);
		hashstring.insert("t", 4);
		hashstring.insert("e", 223);
		hashstring.insert("k", 9);
		hashstring.print(std::cout);
		std::cout << "Search Probe: " << hashstring.search("v", myValue) << std::endl;
		std::cout << "Value: " << myValue << std::endl;


		std::cout << "Removed: " << hashstring.remove("s", myValue);
		std::cout << "   " << myValue << std::endl;
		std::cout << "Removed: " << hashstring.remove("l", myValue);
		std::cout << "   " << myValue << std::endl;
		hashstring.print(std::cout);
		std::cout << "Removed: " << hashstring.remove("s", myValue);
		std::cout << "   " << myValue << std::endl;
		hashstring.print(std::cout);
		
		std::cout << hashstring.cluster_distribution();
		std::cout << std::endl << std::endl;

		std::cout << hashstring.remove_random() << std::endl;
		hashstring.print(std::cout);
		std::cout << hashstring.remove_random() << std::endl;
		hashstring.print(std::cout);
	}
}

//Hashmap<int, int> hashInt = Hashmap<int, int>(5, 0);
//Hashmap<double, int> hashChar = Hashmap<double, int>(5, 0);
//Hashmap<char*, int> hashCharStar = Hashmap<char*, int>(5, 0);
//Hashmap<std::string, int> hashCharString = Hashmap<std::string, int>(5, 0);

TEST_CASE("BUCKETS ADDING/REMOVING", "ADDING AND REMOVING FROM BUCKET HASH, FILL AND EMPTY"){
	SECTION("FILLING"){
		std::cout << "BUCKETS: " << endl;
		HashmapBucket<char*, int> bucket = HashmapBucket<char*, int>(5);
		char* var = "Hello";
		bucket.insert(var, 5);
		bucket.print(std::cout);
		bucket.insert(var, 12);
		bucket.print(std::cout);
		bucket.insert("HEllo", 6);
		bucket.insert("HEllO", 7);
		bucket.insert("HELlo", 8);
		bucket.insert("1", 1);
		bucket.insert("2", 2);
		bucket.insert("3", 3);
		bucket.insert("4", 4);
		bucket.insert("5", 5);
		bucket.insert("0", 0);
		bucket.print(std::cout);
		int myValue = 0;
		bucket.remove(var, myValue);
		std::cout << myValue << endl;
		bucket.print(std::cout);
		bucket.remove("HELlo", myValue);
		std::cout << myValue << endl;
		bucket.print(std::cout);
		bucket.remove("5", myValue);
		std::cout << myValue << endl;
		bucket.print(std::cout);

		std::cout << bucket.remove_random();
		bucket.print(std::cout);
	}
}
*/