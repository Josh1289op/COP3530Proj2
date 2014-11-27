#define CATCH_CONFIG_MAIN // This tells Catch to provide a main() - only do this in one cpp file
#include "Hashmap.h"
#include "HashmapBucket.h"
#include "catch/include/catch.hpp"


TEST_CASE("ADDING/REMOVING", "ADDING AND REMOVING FROM HASH, FILL AND EMPTY"){
	SECTION("FILLING"){

		Hashmap<char*, int> hashchar = Hashmap<char*, int>(5, 0);
		hashchar.insert("hey", 1);
		hashchar.insert("hey", 1);
		hashchar.print(std::cout);
	}
}

//Hashmap<int, int> hashInt = Hashmap<int, int>(5, 0);
//Hashmap<double, int> hashChar = Hashmap<double, int>(5, 0);
//Hashmap<char*, int> hashCharStar = Hashmap<char*, int>(5, 0);
//Hashmap<std::string, int> hashCharString = Hashmap<std::string, int>(5, 0);

