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

#ifndef LUA_STRING_WRAP
#define LUA_STRING_WRAP
#include <lua_defs.h>

class LuaString
{
  public:
    LuaString(std::string str = "");
    void set(std::string s);
    std::string get();
    
    void globalize(lua_State* L, std::string name);
    void push(lua_State* L);
    
    bool getFromLua(lua_State* L, std::string varname);
    
  protected:
    std::string value;
};

#endif
