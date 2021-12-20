//
// A symtable unit test based on Catch framework
//
// Michael J Adami III
// U. of Illinois, Chicago
// CS 251, Spring 2020
// Project #03: symtable
//
#include <string>

#include "symtable.h"

#include "catch.hpp"

using namespace std;


TEST_CASE("(5) Empty ") 
{
    symtable<string, string> table;
    
    try{
        REQUIRE(table.size() == 0);
        REQUIRE(table.numscopes() == 0);
        table.exitScope();
        REQUIRE(false);
        }
    catch(...){
        REQUIRE(true);
    }
        
    try{
        REQUIRE(table.size()==0);
        REQUIRE(table.numscopes()==0);
        table.curScope();
        REQUIRE(false);
    }
    catch(...){
        REQUIRE(true);
    }
    }
