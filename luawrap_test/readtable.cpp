/*

Copyright (C) 2013 Thomas MAURICE

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License along
with this program; if not, write to the Free Software Foundation, Inc.,
51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.

*/

extern "C"
{
  #include <lua.h>
  #include <lauxlib.h>
  #include <lualib.h>
}

#include <iostream>
#include <sstream>
#include <cstdlib>
#include <libluawrap.h>

using namespace std;

int main(int argc, char** argv)
{
  if(argc != 3) {
    cout << "Syntax : " << argv[0] << " <testscript.lua> <tablename>" <<endl;
    return EXIT_FAILURE;
  }
		
		
  print_luawrap_version();

  lua_State * l = luaL_newstate();
  luaL_openlibs(l);
    
  int erred = luaL_dofile(l, argv[1]);
  if(erred)
    std::cout << "Lua error: " << luaL_checkstring(l, -1) << std::endl;
  
  LuaTableElement conf= LuaWrap::readTableFromLua(l, argv[2]);
  conf.dump();
    
  lua_close(l);

  return 0;
}
