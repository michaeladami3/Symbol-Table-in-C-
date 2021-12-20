//
// A symtable unit test based on Catch framework
//
// Michael J Adami III
// U. of Illinois, Chicago
// CS 251, Spring 2020
// Project #03: symtable
//
#include <iostream>

#include <string>

#include "symtable.h"

#include "catch.hpp"

using namespace std;


TEST_CASE("(6) Exit and Enter") 
{
  symtable<string, string>  table;
  string symbol;
  REQUIRE(table.size() == 0);
  REQUIRE(table.numscopes() == 0);
  table.enterScope("global");
  table.insert("i", "int");
  table.insert("j", "double");
  REQUIRE(table.lookup("i",symbol));
  REQUIRE(symbol == "int");
  REQUIRE(table.lookup("j",symbol));
  REQUIRE(symbol == "double");
  REQUIRE(!table.lookup("w",symbol));
  REQUIRE(table.size()==2);
  REQUIRE(table.numscopes()==1);
  table.exitScope();
    
  table.enterScope("x");
  REQUIRE(!table.lookup("i",symbol));
  table.insert("p","int");
  table.insert("q","double");
  REQUIRE(table.lookup("p",symbol));
  REQUIRE(symbol == "int");
  REQUIRE(table.lookup("q",symbol));
  REQUIRE(symbol == "double");
  table.exitScope();
    
  REQUIRE(table.size() == 0);
  REQUIRE(table.numscopes() == 0);
  REQUIRE(!table.lookup("i",symbol));
  REQUIRE(!table.lookup("j",symbol));
}