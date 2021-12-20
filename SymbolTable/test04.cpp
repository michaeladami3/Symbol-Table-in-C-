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
#include<fstream>
using namespace std;


TEST_CASE("(4) curr and  look up") 
{
  symtable<string, string>  table;
  
  REQUIRE(table.size() == 0);
  REQUIRE(table.numscopes() == 0);

  table.enterScope("global");
  
  table.insert("i", "int");
  table.insert("j", "double");
  
  REQUIRE(table.size() == 2);
  REQUIRE(table.numscopes() == 1);
  
  table.enterScope("x");
  table.insert("k", "char");
  
  REQUIRE(table.size() == 3);
  REQUIRE(table.numscopes() == 2); 
  
  //
  // these lookups should both succeed:
  //
  string symbol;
  table.insert("k","string");
  REQUIRE(table.size() == 3);
  REQUIRE(table.numscopes() == 2); 
  REQUIRE(table.lookup("i", symbol));
  REQUIRE(symbol == "int");
  REQUIRE(table.lookup("j", symbol));
  REQUIRE(symbol == "double");
  //
  // this lookup should return false:
  //
  REQUIRE((!table.lookup("x", symbol)));
}
