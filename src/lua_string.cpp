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

#include <lua_string.h>

LuaString::LuaString(std::string str)
{
  value = str;
}

void LuaString::set(std::string str)
{
  value = str;
}
    
std::string LuaString::get()
{
  return value;
}

void LuaString::push(lua_State* L)
{
	lua_pushstring(L, value.c_str());
}

void LuaString::globalize(lua_State* L, std::string name)
{
  lua_pushstring(L, value.c_str());
  lua_setglobal(L, name.c_str());
}

bool LuaString::getFromLua(lua_State* L, std::string varname)
{
  lua_getglobal(L, varname.c_str());
  if(!lua_isstring(L,-1))
    return false;
  
  value = lua_tostring(L, -1);
  return true;
}
