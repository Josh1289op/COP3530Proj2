#define CATCH_CONFIG_MAIN // This tells Catch to provide a main() - only do this in one cpp file
#include "Hashmap.h"
#include "HashmapBucket.h"
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


TEST_CASE("ADDING/REMOVING BUCKETS", "ADDING AND REMOVING FROM HASH BUCKETS, FILL AND EMPTY"){
	SECTION("BUCKETS"){
		HashmapBucket bucket = HashmapBucket(5);
		REQUIRE(bucket.insert(0, '0'));
		REQUIRE(bucket.insert(1, '1'));
		REQUIRE(bucket.insert(114, '2'));		
		REQUIRE(bucket.insert(14, '3'));
		REQUIRE(bucket.insert(1, '4'));
		REQUIRE(bucket.insert(13, '5'));		
		REQUIRE(bucket.insert(4, '6'));
		REQUIRE(bucket.insert(16, '7'));
		REQUIRE(bucket.insert(3, '8'));		
		REQUIRE(bucket.insert(10, '9'));
		REQUIRE(bucket.insert(11, 'a'));
		REQUIRE(bucket.insert(12, 'b'));		
		REQUIRE(bucket.insert(3442, 'c'));
		REQUIRE(bucket.insert(26, 'd'));
		REQUIRE(bucket.insert(4, 'e'));
		char test;
		REQUIRE(bucket.remove(16, test));
		std::cout << test << std::endl;
		bucket.print(std::cout);
	}



}