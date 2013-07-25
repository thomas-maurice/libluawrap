#include <iostream>
#include <cstdlib>
#include <libluawrap.h>

using namespace std;

/**
  \file luawrap_test/object.cpp
  
  This script shows you how to export a new object to Lua
  
  Execute: object <path to sources>/test_scripts/snaffle.lua
*/
/*
  File: luawrap_test/basic_export.cpp
  
  Basic script to export variables from C++ to Lua. This is demonstrated with
  a LuaNumber and a LuaString but the export functions are the same for every
  object of the library.
  
  Execute: basic_export <path to sources>/test_scripts/basic_export.lua
*/

class Snaffle {
	public:
		Snaffle() {
			s = "I'm a snaffle !";
			entier = 0;
		}
		
		void doSnaffle() {
			cout << "Snaffle ! " << s << " " << entier << endl;
		}
		
		void setSnaffle(std::string p_s) {
			s = p_s;
		}
		
		std::string getSnaffle() {
			return s;
		}
		
		void plus() {
			entier++;
		}
		
	private:
		std::string s;
		int entier;
};

CHECK_UDATA(Snaffle*, snaffle_check_snaffle, "Snaffle");

int new_snaffle(lua_State* L)
{
  Snaffle** s = (Snaffle**)lua_newuserdata(L, sizeof(Snaffle*)); // Alloue un bloc de
  // mémoire de taille qui va bien pour stocker l'objet.
  // On assigne a tout les objets la même metatable
  luaL_getmetatable(L, "Snaffle");
  lua_setmetatable(L, -2); // Puisque l'objet et en position -2 sur la stack

 	*s = new Snaffle();
	
  return 1; // Userdatum on the stack
}

int splus(lua_State* L) {
	Snaffle** s = snaffle_check_snaffle(L);
	(*s)->plus();
	return 0;
}

int do_snaffle(lua_State* L) {
	Snaffle** s = snaffle_check_snaffle(L);
	(*s)->doSnaffle();
	return 0;
}

int set_snaffle(lua_State* L) {
	Snaffle** s = snaffle_check_snaffle(L);
	std::string str = luaL_checkstring(L, 2);
	(*s)->setSnaffle(str);
	return 0;
}

int get_snaffle(lua_State* L) {
	Snaffle** s = snaffle_check_snaffle(L);
	LuaString str((*s)->getSnaffle());
	str.push(L);
	return 1;
}

int main(int argc, char** argv) {
  if(argc != 2) {
    cout << "Syntax : " << argv[0] << " <testscript.lua>" <<endl;
    return EXIT_FAILURE;
  }
  
  lua_State* L = LuaWrap::newLuaContext();
	
	LuaTableElement table("Snaffle");
	
	table.addChildren(new_snaffle, "new");
	table.addChildren(do_snaffle, "doSnaffle");
	table.addChildren(get_snaffle, "getSnaffle");
	table.addChildren(set_snaffle, "setSnaffle");
	table.addChildren(splus, "plus");
	
	table.globalize(L);
  // Let's execute a file !
 
  int erred = luaL_dofile(L, argv[1]);
  if(erred)
    std::cout << "Lua error: " << luaL_checkstring(L, -1) << std::endl;
  
  LuaWrap::closeContext(L);

  return EXIT_SUCCESS;
}
