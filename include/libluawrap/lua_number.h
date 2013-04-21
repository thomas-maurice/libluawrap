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

#ifndef LUA_NUMBER_WRAP
#define LUA_NUMBER_WRAP
#include <lua_defs.h>

/**
  \file lua_number.h
  \author Thomas Maurice
  
  \class LuaNumber
  \brief Lua Numbers
  
  This class is used to exchange numeric variables between C++ and Lua.
*/

class LuaNumber
{
  public:
    LuaNumber(double v = 0); //!< Creates a LuaNumber with a given value
    void set(double v); //!< Changes the value
    
    long getInt(); //!< Returns the value as an integer
    double getDouble(); //!< Returns the value as a double
    double get(); //!< Returns the value (double by default)
    
    void globalize(lua_State* L, std::string name); //!< Registers the variable in the Lua context
    void push(lua_State* L); //!< Pushes the variable on the top of the stack
    
    bool getFromLua(lua_State* L, std::string varname); //!< Reads the value from Lua
    
  private:
    double value;
    int type;
    
};

#endif
