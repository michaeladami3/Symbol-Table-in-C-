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


TEST_CASE("(2) Number of Scopes and Elements") 
{
  symtable<string, string>  table;
  string symbol;
  REQUIRE(table.size() == 0);
  REQUIRE(table.numscopes() == 0);
    
  table.enterScope("global");
  table.insert("i", "int");
  table.insert("j", "double");
    
  table.enterScope("x");
  table.insert("p","int");
  table.insert("p","double");
  
  REQUIRE(table.size() == 3);
  REQUIRE(table.numscopes() == 2);
    
  REQUIRE(table.lookup("p",symbol,symtable<string,string>::ScopeOption::CURRENT));
  table.enterScope("y");
  table.enterScope("x");
  table.insert("k", "char");
   
    
  REQUIRE(!(table.lookup("x",symbol,symtable<string,string>::ScopeOption::GLOBAL)));
  REQUIRE(table.size() == 4);
  REQUIRE(table.numscopes() == 4);
  
  table.exitScope();
  REQUIRE(table.size() == 3);
  REQUIRE(table.numscopes() == 3);
    
  table.exitScope();
  REQUIRE(table.size() == 3);
  REQUIRE(table.numscopes()== 2);
   
  table.exitScope();
  REQUIRE(table.size() == 2);
  REQUIRE(table.numscopes()== 1);
    
  table.exitScope();
  REQUIRE(table.size() == 0);
  REQUIRE(table.numscopes()== 0);
  
}