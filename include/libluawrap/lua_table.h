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

#ifndef LUA_TABLE_WRAP
#define LUA_TABLE_WRAP
#include <lua_defs.h>

class LuaTable
{
  public:
    LuaTable(std::string t_name = "");

    void push(lua_State *L); // Register and put onto the stack
    void globalize(lua_State *L,std::string name); // Register and set as global variable

    void setMetatable(std::string p_metatable);
    void setMetatable(LuaTable meta);

    void addField_Table(std::string name, LuaTable *table);
    void addField_Function(std::string name, LuaFunction *func);
    void addField_Number(std::string name, LuaNumber num);
    void addField_Number(std::string name, double num);
    void addField_Boolean(std::string name, LuaBoolean b);
    void addField_Boolean(std::string name, bool b);
    void addField_String(std::string name, std::string str);
    void addField_String(std::string name, LuaString str);
    void addField_Nil(std::string name, LuaNil nil);
    void addField_Nil(std::string name);

    void addIndex_Table(int index, LuaTable *table);
    void addIndex_Function(int index, LuaFunction *func);
    void addIndex_Number(int index, LuaNumber num);
    void addIndex_Number(int index, double num);
    void addIndex_Boolean(int index, LuaBoolean b);
    void addIndex_Boolean(int index, bool b);
    void addIndex_String(int index, std::string str);
    void addIndex_String(int index, LuaString str);
    void addIndex_Nil(int index, LuaNil nil);
    void addIndex_Nil(int index);

    std::string getName();

  protected:
    std::string metatable;
    std::string table_name;

    std::vector<LuaTableField_Table> tables;
    std::vector<LuaTableField_String> strings;
    std::vector<LuaTableField_Number> numbers;
    std::vector<LuaTableField_Function> functions;
    std::vector<LuaTableField_Boolean> booleans;
    std::vector<LuaTableField_Nil> nils;

    std::vector<LuaTableIndex_Table> i_tables;
    std::vector<LuaTableIndex_String> i_strings;
    std::vector<LuaTableIndex_Number> i_numbers;
    std::vector<LuaTableIndex_Function> i_functions;
    std::vector<LuaTableIndex_Boolean> i_booleans;
    std::vector<LuaTableIndex_Nil> i_nils;
};

#endif
