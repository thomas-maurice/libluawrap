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
  \file lua_nil.cpp
  \author Thomas Maurice
  
  Implementation of the nil value
*/

#include <lua_nil.h>

/**
  Default constructor, very simple : does nothing. Just create a LuaNil object.
*/
LuaNil::LuaNil()
{

}

/**
  Pushes the nil value onto the top of the stack. This can be used to return arguments
  from a Lua function.
  
  \param[in, out] L The lua context
*/
void LuaNil::push(lua_State* L)
{
	lua_pushnil(L);
}

/**
  Globalizes a nil value with a given name within a Lua context.
  
  \param[in, out] L The lua context
  \param[in] name The name under which the variable shall be registered
*/
void LuaNil::globalize(lua_State* L, std::string name)
{
  lua_pushnil(L);
  lua_setglobal(L, name.c_str());
}
