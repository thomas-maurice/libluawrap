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

#ifndef LUA_TABLE_ELEMENT_WRAP
#define LUA_TABLE_ELEMENT_WRAP
#include <lua_defs.h>

#include <lua_number.h>
#include <lua_string.h>
#include <lua_bool.h>
#include <lua_nil.h>

#include <vector>

enum {NUMBER, STRING, BOOLEAN, NIL, TABLE};


class LuaTableElement
{
  public:
    LuaTableElement();
    LuaTableElement(std::string pkey);
    LuaTableElement(int pindex);
    
    void dump();
    
    void setIndex(int i);
    void setKey(std::string k);
    
    void addChildren(LuaTableElement e);
    
    void set(LuaNumber num);
    void set(LuaString str);
    void set(LuaBoolean b);
    void set(LuaNil n);
    
    void set(double num);
    void set(int num);
    void set(float num);
    void set(std::string str);
    void set(char* str);
    void set(bool b);
    
    void push(lua_State* L);
    void globalize(lua_State* L);
    
    int getType();
    std::string getKey();
    int getIndex();
    bool getIsInArray();
    
  private:
    std::vector<LuaTableElement> children;
    std::string key;
    int index;
    bool is_in_array;
    
    int type;
    
    double double_value;
    bool bool_value;
    std::string string_value;
};

#endif
