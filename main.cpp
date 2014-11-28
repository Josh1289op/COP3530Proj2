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
		hashstring.insert("l", 232323);
		hashstring.print(std::cout);
		std::cout << "Search Probe: " << hashstring.search("l", myValue) << std::endl;
		std::cout << "Value: " << myValue << std::endl;



	}
}

//Hashmap<int, int> hashInt = Hashmap<int, int>(5, 0);
//Hashmap<double, int> hashChar = Hashmap<double, int>(5, 0);
//Hashmap<char*, int> hashCharStar = Hashmap<char*, int>(5, 0);
//Hashmap<std::string, int> hashCharString = Hashmap<std::string, int>(5, 0);

