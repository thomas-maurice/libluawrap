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

#include <lua_function.h>

LuaFunction::LuaFunction(std::string n)
{
  name = n;
}
    
void LuaFunction::setName(std::string n)
{
  name = n;
}

void LuaFunction::push(lua_State* L)
{
	lua_pushcfunction(L, func);
}

void LuaFunction::setFunction(int (*f)(lua_State*))
{
  func = f;
}
    
std::string LuaFunction::getName()
{
  return name;
}

int (* LuaFunction::getFunction(void))(lua_State*)
{
  return func;
}
    
void LuaFunction::globalize(lua_State* L)
{
  lua_pushcfunction(L, func);
  lua_setglobal(L, name.c_str());
}

void LuaFunction::globalize(lua_State* L, std::string n)
{
  lua_pushcfunction(L, func);
  lua_setglobal(L, n.c_str());
}
    
