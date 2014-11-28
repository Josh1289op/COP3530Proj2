#define CATCH_CONFIG_MAIN // This tells Catch to provide a main() - only do this in one cpp file
#include "Hashmap.h"
#include "HashmapBucket.h"
#include "catch/include/catch.hpp"


TEST_CASE("ADDING/REMOVING", "ADDING AND REMOVING FROM HASH, FILL AND EMPTY"){
	SECTION("FILLING"){

		Hashmap<char*, int> hashchar = Hashmap<char*, int>(5, 0);
		hashchar.insert("c", 13);
		hashchar.insert("c", 15);
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

