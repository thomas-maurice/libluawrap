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

/**
  \file lua_function.h
  \author Thomas Maurice
  
  \class LuaFunction
  \brief This class represents a Lua function
  
  This class is used to exchange functions between C++ and Lua.
*/

class LuaFunction
{
  public:
    LuaFunction(std::string n = ""); //!< A constructor with the name of the function
    
    void setName(std::string n); //!< Changes the name of the function
    void setFunction(int (*f)(lua_State*)); //!< Changes the function pointer
    
    std::string getName(); //!< Returns the name of the function
    int (* getFunction(void))(lua_State*); //!< Returns the pointer on the function
    
    void globalize(lua_State* L); //!< Globalize the function with it's given name
    void globalize(lua_State* L, std::string n); //!< Globalize the function with a given name
    void push(lua_State* L); //!< Pushes the function onto the top of the Lua stack
    
  protected:
    int (*func)(lua_State*); //!< The pointer on the function
    std::string name; //!< The name of the function
    
};

#endif
