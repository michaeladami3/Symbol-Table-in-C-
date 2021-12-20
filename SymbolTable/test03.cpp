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


TEST_CASE("(3) lookup") 
{
  symtable<string, string>  table;
  string symbol;
  REQUIRE(table.size() == 0);
  REQUIRE(table.numscopes() == 0);

  table.enterScope("global");
  
  table.insert("i", "int");
  table.insert("j", "double");
  
  REQUIRE(table.size() == 2);
  REQUIRE(table.numscopes() == 1);
  
  table.enterScope("x");
  table.insert("k", "char");
  

  
  REQUIRE(table.lookup("i", symbol));
  REQUIRE(symbol == "int");
  
  REQUIRE(table.lookup("j", symbol));
  REQUIRE(symbol == "double");
//   try{
//   table.curScope();
//   REQUIRE(false);
//   }
//   catch(...){
//     REQUIRE(true);
//   }
  symtable<string, string>::Scope scope;
  scope = table.curScope();  
  REQUIRE(table.size() == 3);
  REQUIRE(table.numscopes() == 2); 
  
  //
  // these lookups should both succeed:
  //
  
  table.insert("k","string");
  REQUIRE(table.size() == 3);
  REQUIRE(table.numscopes() == 2); 
  REQUIRE(scope.Symbols.count("k")==1);
  REQUIRE(!scope.Symbols.count("j")==1);
  REQUIRE(table.lookup("j",symbol,symtable<string,string>::ScopeOption::GLOBAL));
  REQUIRE(!table.lookup("k",symbol,symtable<string,string>::ScopeOption::GLOBAL));
  REQUIRE(table.lookup("k",symbol,symtable<string,string>::ScopeOption::CURRENT));
  REQUIRE(table.lookup("k",symbol,symtable<string,string>::ScopeOption::ALL));
  // this lookup should return false:
  //
  REQUIRE((!table.lookup("x", symbol)));
}
