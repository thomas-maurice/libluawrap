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

/**
   Creates a new LuaString variable initialized with the given value. If
   no value is provided, than it will be assumed to be "".
   
   \param[in] str The initial value of the string
   
*/
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

/**
  Pushes the value of the string on the top of the Luya stack. This action is
  performed when you want to return a value in a lua function, first you push all
  the return values on the stack then the function returns the number of pushed
  values.
  
  \param[in, out] L The used Lua context
*/
void LuaString::push(lua_State* L)
{
	lua_pushstring(L, value.c_str());
}

/**
  Globalize the value into the Lua context. This is used to 'register' variables,
  for exemple if you want to have a variable named "foo" in your lua context, just
  call ```str.globalize(L, "foo");``` Please not that if the value is modified
  in the Lua context, it won't be modified in the C++ context.
  
  \param[in, out] L The lua context
  \param[in] name The name you register your variable under
*/
void LuaString::globalize(lua_State* L, std::string name)
{
  lua_pushstring(L, value.c_str());
  lua_setglobal(L, name.c_str());
}

/**
  Loads the value from the Lua context into the variable. If the value exists, this
  function will return true, false otherwise. The value will be stored into the object.
  
  \param[in, out] L The lua context
  \param[in] varname The name of the variable to load
*/
bool LuaString::getFromLua(lua_State* L, std::string varname)
{
  lua_getglobal(L, varname.c_str());
  if(!lua_isstring(L,-1))
    return false;
  
  value = lua_tostring(L, -1);
  return true;
}
