#include <iostream>

#include "symtable.h"

#include "catch.hpp"
#include<fstream>
using namespace std;


int main()
{
  ofstream i;
  i.open("Hello.txt");
  symtable<string, string>  table;
  table.enterScope("global");
  table.insert("i", "int");
  table.insert("j", "double");
  table.enterScope("x");
  table.insert("k", "char");
  table.insert("p","string");
 
  
  table.dump(i,symtable<string, string>::ScopeOption::ALL);
  return 0;
}