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

#ifndef LUA_FUNCTION_WRAP
#define LUA_FUNCTION_WRAP
#include <lua_defs.h>

class LuaFunction
{
  public:
    LuaFunction(std::string n = "");
    
    void setName(std::string n);
    void setFunction(int (*f)(lua_State*));
    
    std::string getName();
    int (* getFunction(void))(lua_State*);
    
    void globalize(lua_State* L);
    void globalize(lua_State* L, std::string n);
    void push(lua_State* L);
    
  protected:
    int (*func)(lua_State*);
    std::string name;
    
};

#endif
