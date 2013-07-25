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

#ifndef LUA__WRAP
#define LUA__WRAP
#include <lua_defs.h>

/**
  \file lua_wrap.h
  \author Thomas Maurice
  
  \class LuaWrap
  \brief Misc class to store useful functions
  
  Functions will be stored here and accessible with LuaWrap::Function
*/
class LuaWrap
{
  public:
    /** Useless constructor*/
    LuaWrap() {};
    
    static bool isNil(lua_State* L, std::string varname); //!< Test if a variable is nil
    static LuaTableElement readTableFromLua(lua_State *L, std::string var); //!< Reads a table from Lua
    static lua_State* newLuaContext(); //!< Returns a new Lua context
    static LuaTableElement getTableOnTop(lua_State* L, int key, int idx);
    static LuaTableElement getTableOnTop(lua_State* L, std::string key, int idx);
    static void closeContext(lua_State* L); //!< Close a Lua context
};

#endif
