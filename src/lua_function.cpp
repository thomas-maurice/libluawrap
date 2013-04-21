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

/**
  \file lua_function.cpp
  \author Thomas Maurice
*/

#include <lua_function.h>

/**
  Creates a function with the given name
  
  \param[in] n The name of the function
*/
LuaFunction::LuaFunction(std::string n)
{
  name = n;
}

/**
  Changes the name of the function
  
  \param[in] n The name of the function
*/
void LuaFunction::setName(std::string n)
{
  name = n;
}

/**
  Pushes the function on the top of the lua stack. This is used to return variables
  from a lua function. For more info, read the Lua documentation.
  
  \param[in, out] L The lua context
*/
void LuaFunction::push(lua_State* L)
{
	lua_pushcfunction(L, func);
}

/**
  Changes the pointer on the function. The function is a 'cfunction' according to
  Lua documentation.
  
  \param[in] f The function
*/
void LuaFunction::setFunction(int (*f)(lua_State*))
{
  func = f;
}

/**
  Returns the name of the function
  
  \return The name of the function
*/
std::string LuaFunction::getName()
{
  return name;
}

/**
  Returns the pointer on the function
  
  \return The pointer on the function
*/
int (*LuaFunction::getFunction(void))(lua_State*)
{
  return func;
}

/**
  Registers the function with it's default name.
  
  \param[in, out] L The lua context
*/
void LuaFunction::globalize(lua_State* L)
{
  lua_pushcfunction(L, func);
  lua_setglobal(L, name.c_str());
}

/**
  Registers the function with a custom name
  
  \param[in, out] L The lua context
  \param[in] n The name of the function
*/
void LuaFunction::globalize(lua_State* L, std::string n)
{
  lua_pushcfunction(L, func);
  lua_setglobal(L, n.c_str());
}
    
