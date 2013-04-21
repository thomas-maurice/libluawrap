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

#ifndef LUA_NIL_WRAP
#define LUA_NIL_WRAP
#include <lua_defs.h>

/**
  \file lua_nil.h
  \author Thomas Maurice
  
  \class LuaNil
  \brief The Nil value
  
  This class is used to implement a Nil value in the API. This is mainly used
  to push nil values on the top of the Lua stack.
*/

class LuaNil
{
  public:
    LuaNil(); //!< Creates a nil value
    
    void globalize(lua_State* L, std::string name); //!< Registers a Nil value
    void push(lua_State* L); //!< Pushes a Nil value on the top of the stack
    
  protected:
    
};

#endif
