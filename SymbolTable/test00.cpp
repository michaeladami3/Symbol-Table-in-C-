//
// A symtable unit test based on Catch framework
//
// Michael J Adami III
// U. of Illinois, Chicago
// CS 251, Spring 2020
// Project #03: symtable
//
#include <iostream>

#include "symtable.h"

#include "catch.hpp"

using namespace std;
TEST_CASE("(0) initially empty") 
{
    symtable<string, string> table;
    REQUIRE(table.size() == 0);
    REQUIRE(table.numscopes() == 0);
}