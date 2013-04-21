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

#include <lua_number.h>

/**
  \param[in] v The initial value
*/
LuaNumber::LuaNumber(double v)
{
  value = v;
}

/**
  Registers the variable in a Lua context
  
  \param[in, out] L The lua context
  \param[in] name The name of the variable
*/
void LuaNumber::globalize(lua_State* L, std::string name)
{
  lua_pushnumber(L, value);
  lua_setglobal(L, name.c_str());
}

/**
  Pushes the variable on the top of the stack, this is used to return from Lua
  functions.
  
  \param[in] L The lua context
*/
void LuaNumber::push(lua_State* L)
{
	lua_pushnumber(L, value);
}

void LuaNumber::set(double v)
{
  value = v;
}
 
long LuaNumber::getInt()
{
  return (long)value;
}

double LuaNumber::getDouble()
{
  return value;
}

double LuaNumber::get()
{
	return value;
}

/**
  Loads the value from the Lua context into the variable. If the value exists, this
  function will return true, false otherwise. The value will be stored into the object.
  
  \param[in, out] L The lua context
  \param[in] varname The name of the variable to load
*/
bool LuaNumber::getFromLua(lua_State* L, std::string varname)
{
  lua_getglobal(L, varname.c_str());
  if(!lua_isnumber(L,-1))
    return false;
  
  value = lua_tonumber(L, -1);
  return true;
}
