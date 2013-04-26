#include <iostream>
#include <sstream>
#include <cstdlib>
#include <libluawrap.h>

using namespace std;

/**
  \file luawrap_test/readtable.cpp
  
  This program reads a table within a Lua file and dumps it.
  
  The porgram is called this way: readtable <lua file> <tablename>
*/
/*
  File: luawrap_test/readtable.cpp
  
  This program reads a table within a Lua file and dumps it.
  
  The porgram is called this way: readtable <lua file> <tablename>
  For example: readtable <source path>test_scripts/conf.lua conf
*/
int main(int argc, char** argv)
{
  if(argc != 3) {
    cout << "Syntax : " << argv[0] << " <testscript.lua> <tablename>" <<endl;
    return EXIT_FAILURE;
  }
		
	// Just somr version information
  print_luawrap_version();

  lua_State * l = LuaWrap::newLuaContext();
    
  // Execute the file
  int erred = luaL_dofile(l, argv[1]);
  if(erred)
    std::cout << "Lua error: " << luaL_checkstring(l, -1) << std::endl;
  
  // Just read the table
  LuaTableElement conf= LuaWrap::readTableFromLua(l, argv[2]);
  // And dump it
  conf.dump();
    
  LuaWrap::closeContext(l);

  return EXIT_SUCCESS;
}
