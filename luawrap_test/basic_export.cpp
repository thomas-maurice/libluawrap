#include <iostream>
#include <cstdlib>
#include <libluawrap.h>

using namespace std;

/**
  \file luawrap_test/basic_export.cpp
  
  Basic script to export variables from C++ to Lua. This is demonstrated with
  a LuaNumber and a LuaString but the export functions are the same for every
  object of the library.
  
  Execute: basic_export <path to sources>/test_scripts/basic_export.lua
*/
/*
  File: luawrap_test/basic_export.cpp
  
  Basic script to export variables from C++ to Lua. This is demonstrated with
  a LuaNumber and a LuaString but the export functions are the same for every
  object of the library.
  
  Execute: basic_export <path to sources>/test_scripts/basic_export.lua
*/
int main(int argc, char** argv) {
  if(argc != 2) {
    cout << "Syntax : " << argv[0] << " <testscript.lua>" <<endl;
    return EXIT_FAILURE;
  }
  
 lua_State* L = LuaWrap::newLuaContext();
  
  // Let's create a number
  LuaNumber num(42);
  // Let's export it !
  num.globalize(L, "num");
  
  // String
  LuaString str("foobar");
  str.globalize(L, "str");
  
  // Let's execute a file !
  int erred = luaL_dofile(L, argv[1]);
  if(erred)
    std::cout << "Lua error: " << luaL_checkstring(L, -1) << std::endl;
  
  LuaWrap::closeContext(L);

  return EXIT_SUCCESS;
}
