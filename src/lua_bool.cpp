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

#include <lua_bool.h>

/**
   Creates a new LuaBoolean variable initialized with the given value. If
   no value is provided, than it will be assumed to be true.
   
   \param[in] b The initial value of the boolean
   
*/
LuaBoolean::LuaBoolean(bool b)
{
  value = b;
}

/**
  Pushes the value of the boolean on the top of the Luya stack. This action is
  performed when you want to return a value in a lua function, first you push all
  the return values on the stack then the function returns the number of pushed
  values.
  
  \param[in, out] L The used Lua context
*/
void LuaBoolean::push(lua_State* L)
{
	lua_pushboolean(L, value);
}

/**
  Changes the value of the LuaBoolean
  
  \param[in] b The new value
*/
void LuaBoolean::set(bool b)
{
  value = b;
}

/**
  Returns the value of the boolean
  
  \return The value of the boolean
*/
bool LuaBoolean::get()
{
  return value;
}

/**
  Globalize the value into the Lua context. This is used to 'register' variables,
  for exemple if you want to have a variable named "foo" in your lua context, just
  call ```boolean.globalize(L, "foo");``` Please not that if the value is modified
  in the Lua context, it won't be modified in the C++ context.
  
  \param[in, out] L The lua context
  \param[in] name The name you register your variable under
*/
void LuaBoolean::globalize(lua_State* L, std::string name)
{
  lua_pushboolean(L, value);
  lua_setglobal(L, name.c_str());
}

/**
  Loads the value from the Lua context into the variable. If the value exists, this
  function will return true, false otherwise. The value will be stored into the object.
  
  \param[in, out] L The lua context
  \param[in] varname The name of the variable to load
*/
bool LuaBoolean::getFromLua(lua_State* L, std::string varname)
{
  lua_getglobal(L, varname.c_str());
  if(!lua_isboolean(L,-1))
    return false;
  
  value = lua_toboolean(L, -1);
  return true;
}
