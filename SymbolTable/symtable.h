/*symtable.h*/

// 
// Michael Adami
// U. of Illinois, Chicago
// CS 251: Spring 2020
// Project #03: symtable
//
// Symbol Table: a symbol table is a stack of scopes, typically used by a
// compiler to keep track of symbols in a program (functions, variables,
// types, etc.).  In most programming languages, you "enter scope" when you 
// see {, and "exit scope" when you see the corresponding }.  Example:
//
// int main()
// {              <-- enterScope()
//    int i;      <-- enter "i" into symbol table as type "int"
//    .
//    .
//    while (true)
//    {              <-- enterScope()
//       char i;     <-- enter "i" into symbol table as type "char"
//
// Notice there are two variables named "i", which is legal because
// they are in different scopes.
//

#pragma once

#include <iostream>
#include <deque>
#include <map>

using namespace std;

template<typename KeyT, typename SymbolT>
class symtable
{
public:
  //
  // A symbol table is a stack of scopes.  Every scope has a name, and 
  // we use a map to hold the symbols in that scope.  You can *add* to
  // this class, but you must use the Name and Symbols as given to store
  // the scope name, and scope symbols, respectively.
  //
  class Scope
  {
  public:
    string              Name;
    map<KeyT, SymbolT>  Symbols;

    // constructors:
    Scope()
    {
    Name="";
    Symbols={};
      // default empty string and an empty map:
    }

    Scope(string name)
    {
      this->Name = name;
      // empty map created by map's constructor:
    }
  };

private:
  deque<Scope> d; //Using to store scopes
  int counter=0; //Scope Counter
  int elementsCounter=0; 
public:
  enum class ScopeOption
  {
    ALL, 
    CURRENT,
    GLOBAL
  };

  //
  // default constructor:
  //
  // Creates a new, empty symbol table.  No scope is open.
  //
  symtable()
  {
    //
    // TODO: note that member variables will have their default constructor 
    // called automatically, so there may be nothing to do here.
    //
  }

  //
  // size
  //
  // Returns total # of symbols in the symbol table.
  //
  // Complexity: O(1)
  //
  int size() const
  {
   return elementsCounter;
  }

  //
  // numscopes
  //
  // Returns the # of open scopes.
  //
  // Complexity: O(1)
  //
  int numscopes() const
  { 
    return counter;
  }

  //
  // enterScope
  //
  // Enters a new, open scope in the symbol table, effectively "pushing" on
  // a new scope.  You must provide a name for the new scope, although
  // the name is currently used only for debugging purposes.
  //
  // NOTE: the first scope you enter is known as the GLOBAL scope, since this
  // is typically where GLOBAL symbols are stored.  
  //
  // Complexity: O(1)
  //
  void enterScope(string name)
  {
    Scope tabl;
    tabl.Name = name;
    d.push_front(Scope(tabl));
    counter++; //increase scope counter when entered
  }

  //
  // exitScope
  //
  // Exits the current open scope, discarding all symbols in this scope.
  // This effectively "pops" the symbol table so that it returns to the 
  // previously open scope.  A runtime_error is thrown if no scope is 
  // currently open.  
  //
  // Complexity: O(1)
  //
  void exitScope()
  {
    if(!d.empty()){        
        counter--; // Empty subtract one from the scope counter
        elementsCounter-=d.front().Symbols.size(); //Remove all the variables inside of scope
        d.pop_front();

        }
    else{
        throw runtime_error("symtable::exitScope: empty"); //If it is empty throw an error
      }
  }

  //
  // curScope
  //
  // Returns a copy of the current scope.  A runtime_error is thrown if
  // no scope is currently open.
  //
  // Complexity: O(N) where N is the # of symbols in the current scope
  //
  Scope curScope() const
  {
    if(!d.empty())
        return d.front();
    else
        throw runtime_error("symtable::exitScope: empty"); //If it is empty throw error
  }

  //
  // insert
  //
  // Inserts the (key, symbol) pair in the *current* scope.  If the key
  // already exists in the current scope, the associated symbol is replaced
  // by this new symbol.
  //
  // Complexity: O(lgN) where N is the # of symbols in current scope
  //
  void insert(KeyT key, SymbolT symbol)
  {
    
    if(d.front().Symbols.count(key)==0){ //If not inside scope
        d.front().Symbols.emplace(key,symbol); //Put it inside
        elementsCounter++; 
        }
    else
        d.front().Symbols.at(key)=symbol; //Update
  }

  //
  // lookup
  //
  // Searches the symbol table for the first (key, symbol) pair that 
  // matches the given key.  The search starts in the current scope, and 
  // proceeds "outward" to the GLOBAL scope.  If a matching (key, symbol)
  // pair is found, true is returned along with a copy of the symbol (via 
  // "symbol" reference parameter).  If not found, false is returned and
  // the "symbol" parameter is left unchanged.
  //
  // NOTE: the search can be controlled by the "option" parameter.  By 
  // default, the entire symbol table is searched as described above.
  // However, the search can also be limited to just the current scope, 
  // or just the GLOBAL scope, via the "option" parameter.
  //
  // Example:
  //   symtable<string,string>  table;
  //   string                   symbol;
  //   bool                     found;
  //   ...
  //   found = table.lookup("i", 
  //                        symbol, 
  //                        symtable<string,string>::ScopeOption::CURRENT);
  //
  // Complexity: O(SlgN) where S is the # of scopes and N is the largest #
  // of symbols in any one scope
  //
  bool lookup(KeyT key, 
              SymbolT& symbol, 
              ScopeOption option = ScopeOption::ALL) const
  {
    if(option==ScopeOption::ALL){ // If they want ALL scope
        for(int i=0;i<d.size();i++){ //For all scopes in d
            if(d[i].Symbols.count(key)!=0){ //If its in there
                   symbol=d[i].Symbols.at(key); //FOUND IT!
                    return true; // Lets tell em.
            }
        }
    }
   else if(option==ScopeOption::CURRENT){//CURRENT SCOPE
       if(d.front().Symbols.count(key)!=0){  //If not found return
            symbol=d.front().Symbols.at(key); //FOUND IT
            return true;   //Lets tell em.
            }
        }
   else if(option==ScopeOption::GLOBAL){ //GLOBAL SCOPE
       if(d.back().Symbols.count(key)!=0){ //IF it is not in return
           symbol=d.back().Symbols.at(key);//FOUND IT
           return true;
       }
   }
    return false; //No such thing
  }

  //
  // dump
  // 
  // Dumps the contents of the symbol table to the output stream, 
  // starting with the current scope and working "outward" to the GLOBAL
  // scope.  You can dump the entire symbol table (the default), or dump
  // just the current scope or global scope; this is controlled by the 
  // "option" parameter.
  //
  // Example:
  //   symtable<string,string>  table;
  //   ...
  //   table.dump(std::cout, symtable<string,string>::ScopeOption::GLOBAL);
  //
  // Complexity: O(S*N) where S is the # of scopes and N is the largest #
  // of symbols in any one scope
  //
  void dump(ostream& output, ScopeOption option = ScopeOption::ALL) const
  {    
    
    output << "**************************************************" << endl;
    if (option == ScopeOption::ALL){ //ALL scope
      output << "*************** SYMBOL TABLE (ALL) ***************" << endl;
      output << "** # of scopes: " << this->numscopes() << endl;
      output << "** # of symbols: " << this->size() << endl;
      for(int i=0;i<d.size();i++){
          output <<"** "<<d[i].Name<<" **"<<endl;
          for(pair<KeyT, SymbolT> t : d[i].Symbols){
               output<< t.first << ": " << t.second << endl;
                }
             }
           }
    else if (option == ScopeOption::CURRENT){ //CURRENT SCOPE
      output << "*************** SYMBOL TABLE (CUR) ***************" << endl;
      output << "** # of scopes: " << this->numscopes() << endl;
      output << "** # of symbols: " << this->size() << endl;
      output<<"** "<<d.front().Name<<" **"<<endl;
      for (pair<KeyT, SymbolT> t : d.front().Symbols){
           output<< t.first << ": " << t.second << endl;
            }
        }
    else{ // global:
      output << "*************** SYMBOL TABLE (GBL) ***************" << endl;
      output << "** # of scopes: " << this->numscopes() << endl;
      output << "** # of symbols: " << this->size() << endl;
      output<<"** "<<d.back().Name<<" **"<<endl;
        for (pair<KeyT, SymbolT> t : d.back().Symbols){
           output<< t.first << ": " << t.second << endl;
            }
     }


    //
    // output format per scope:
    //
    // ** scopename **
    // key: symbol
    // key: symbol
    // ...
    //

    output << "**************************************************" << endl;
  }

};
