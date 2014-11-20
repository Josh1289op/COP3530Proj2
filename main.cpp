#define CATCH_CONFIG_MAIN // This tells Catch to provide a main() - only do this in one cpp file
#include "Hashmap.h"
#include "catch/include/catch.hpp"


TEST_CASE("ADDING/REMOVING", "ADDING AND REMOVING FROM HASH, FILL AND EMPTY"){

	SECTION("FILLING"){
		Hashmap hash = Hashmap(5);
		REQUIRE(hash.insert(0, '0'));
		REQUIRE(hash.insert(1, '1'));
		REQUIRE(hash.insert(2, '2'));
		REQUIRE(hash.insert(3, '3'));
		REQUIRE(hash.insert(200, '4'));
		REQUIRE_FALSE(hash.insert(5, '5'));

		SECTION("Overriding Key Value"){
			REQUIRE(hash.insert(3, 'F'));
			hash.print(std::cout);
		}
		SECTION("ATTEMPTING TO USE SAME KEY HASH VALUE"){
			REQUIRE_FALSE(hash.insert(22, 'Z'));
		}
	}
	SECTION("DUMPING"){
		Hashmap hash = Hashmap(5);
		REQUIRE(hash.insert(0, '0'));
		REQUIRE(hash.insert(1, '1'));
		REQUIRE(hash.insert(2, '2'));
		REQUIRE(hash.insert(3, '3'));
		REQUIRE(hash.insert(200, '4'));
		char hello;
		REQUIRE(hash.remove(0, hello));
		REQUIRE(hello == '0');
		REQUIRE(hash.remove(1, hello));
		REQUIRE(hello == '1');
		REQUIRE(hash.remove(2, hello));
		REQUIRE(hello == '2');
		REQUIRE(hash.remove(3, hello));
		REQUIRE(hello == '3');
		REQUIRE(hash.remove(200, hello));
		REQUIRE(hello == '4');
		REQUIRE_FALSE(hash.remove(5, hello));
	}

}

