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

#ifndef LUA_BOOLEAN_WRAP
#define LUA_BOOLEAN_WRAP
#include <lua_defs.h>

/**
  \file lua_bool.h
  \author Thomas Maurice
  
  \class LuaBoolean
  \brief This class represents a Lua boolean
  
  This class is used to exchange boolean variables between C++ and Lua.
  You can push them into a lua context as well as reading them from a lua context.
*/

class LuaBoolean
{
  public:
    LuaBoolean(bool b = true); //!< Creates a LuaBoolean variable
    void set(bool b); //!< Changes the value of the variable
    bool get(); //!< Returns the current value of the variable
    void push(lua_State* L); //!< Pushes the value of the boolean onto the lua stack
    
    void globalize(lua_State* L, std::string name); //!< Register the value of the boolean within a lua context with the given name
    
    bool getFromLua(lua_State* L, std::string varname); //!< Loads a value in the variable from the one existing in lua
    
  protected:
    bool value; //!< The value of the boolean
};

#endif
