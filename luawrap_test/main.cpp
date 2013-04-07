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

int testfunc(lua_State *L)
{
  cout << "test de fonction wrappée" << endl;
  return 0;
}

int main(int argc, char** argv)
{
		if(argc != 2) {
			cout << "Syntax : " << argv[0] << " <testscript.lua>" <<endl;
			return EXIT_FAILURE;
		}
		
		
    print_luawrap_version();

    lua_State * l = luaL_newstate();
    luaL_openlibs(l);
    
    /*lua_newtable(l);
    lua_pushstring(l, "key");
    lua_pushstring(l, "value");
    lua_settable(l, -3);
    //luaL_getmetatable(l, "thobj");
    //lua_setmetatable(l, -2);
    lua_setglobal(l, "thomas");*/
    
    LuaTable table("thomas");
    LuaTable sous;
    
    table.addField_String("__index", "thomas");
    table.addField_String("key", "value");
    table.addField_Number("num", 12);
    table.addField_Boolean("b", false);
    
    LuaFunction fun("testf");
    fun.setFunction(testfunc);
    fun.globalize(l, "fooo");
    
    LuaNumber num(15.42);
    num.globalize(l, "test");
    
    LuaBoolean b(true);
    b.globalize(l, "b");
    
    sous.addField_Boolean("boo", b);
    sous.addField_Function("testf", &fun);
    
    table.addField_Table("soustable", &sous);
    table.addField_Function("testfunc", &fun);
    table.addIndex_String(1, "foobar");
    table.globalize(l, "thomas");
    
    int erred = luaL_dofile(l, argv[1]);
    if(erred)
        std::cout << "Lua error: " << luaL_checkstring(l, -1) << std::endl;
  
  
    if(num.getFromLua(l, "fooint"))
      cout << num.getDouble() << endl;
    else
      cout << "Can't get" << endl;
    
    LuaString s;
    
    if(s.getFromLua(l, "foostr"))
      cout << s.get() << endl;
    else
      cout << "Can't get" << endl;
    
    if(LuaWrap::isNil(l, "foonil"))
      cout << "nil" << endl;
    
    lua_close(l);

    return 0;
}

