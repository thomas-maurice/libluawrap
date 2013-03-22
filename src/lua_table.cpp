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
#include <lua_table.h>
#include <lua_number.h>
#include <lua_function.h>
#include <lua_bool.h>
#include <lua_string.h>
#include <lua_nil.h>

using namespace std;

LuaTable::LuaTable(std::string name)
{
  table_name = name;
}

void LuaTable::globalize(lua_State *L, std::string name)
{
  push(L);
  lua_setglobal(L, name.c_str());
}

void LuaTable::push(lua_State *L)
{
  luaL_newmetatable(L, table_name.c_str());
  
  if(metatable != "") {
  	lua_pushstring(L, "__index");
    luaL_getmetatable(L, metatable.c_str());
    lua_settable(L, -3);
  }
  
  // Enregistrement des champs string
  for(unsigned int i = 0; i < strings.size(); i++) {
    lua_pushstring(L, strings.at(i).name.c_str());
    lua_pushstring(L, strings.at(i).value.c_str());
    lua_settable(L, -3);
  }
  
  // Enregistrement des champs number
  for(unsigned int i = 0; i < numbers.size(); i++) {
    lua_pushstring(L, numbers.at(i).name.c_str());
    lua_pushnumber(L, numbers.at(i).value);
    lua_settable(L, -3);
  }
  
  // Enregistrement des champs booleens
  for(unsigned int i = 0; i < booleans.size(); i++) {
    lua_pushstring(L, booleans.at(i).name.c_str());
    lua_pushboolean(L, booleans.at(i).value);
    lua_settable(L, -3);
  }
  
  // Enregistrement des champs nil
  for(unsigned int i = 0; i < nils.size(); i++) {
    lua_pushstring(L, nils.at(i).name.c_str());
    lua_pushnil(L);
    lua_settable(L, -3);
  }
  
  // Enregistrement des champs functions
  for(unsigned int i = 0; i < functions.size(); i++) {
    lua_pushstring(L, functions.at(i).name.c_str());
    lua_pushcfunction(L, functions.at(i).value->getFunction());
    lua_settable(L, -3);
  }
  
  // Enregistrement des champs table
  for(unsigned int i = 0; i < tables.size(); i++) {
    lua_pushstring(L, tables.at(i).name.c_str());
    tables.at(i).value->push(L);
    lua_settable(L, -3);
  }
  
  // Enregistrement des indexes string
  for(unsigned int i = 0; i < i_strings.size(); i++) {
    lua_pushnumber(L, i_strings.at(i).index);
    lua_pushstring(L, i_strings.at(i).value.c_str());
    lua_settable(L, -3);
  }
  
  // Enregistrement des indexes number
  for(unsigned int i = 0; i < i_numbers.size(); i++) {
    lua_pushnumber(L, i_numbers.at(i).index);
    lua_pushnumber(L, i_numbers.at(i).value);
    lua_settable(L, -3);
  }
  
  // Enregistrement des indexes booleens
  for(unsigned int i = 0; i < i_booleans.size(); i++) {
    lua_pushnumber(L, i_booleans.at(i).index);
    lua_pushboolean(L, i_booleans.at(i).value);
    lua_settable(L, -3);
  }
  
  // Enregistrement des indexes nil
  for(unsigned int i = 0; i < i_nils.size(); i++) {
    lua_pushnumber(L, i_nils.at(i).index);
    lua_pushnil(L);
    lua_settable(L, -3);
  }
  
  // Enregistrement des indexes functions
  for(unsigned int i = 0; i < i_functions.size(); i++) {
    lua_pushnumber(L, i_functions.at(i).index);
    lua_pushcfunction(L, i_functions.at(i).value->getFunction());
    lua_settable(L, -3);
  }
  
  // Enregistrement des indexes table
  for(unsigned int i = 0; i < i_tables.size(); i++) {
    lua_pushnumber(L, i_tables.at(i).index);
    i_tables.at(i).value->push(L);
    lua_settable(L, -3);
  }
}

void LuaTable::setMetatable(std::string p_metatable)
{
  metatable = p_metatable;
}

void LuaTable::setMetatable(LuaTable meta)
{
  metatable = meta.getName();
}

std::string LuaTable::getName()
{
  return table_name;
}

void LuaTable::addField_String(std::string name, std::string str)
{
  LuaTableField_String fs;
  fs.name = name;
  fs.value = str;
  
  strings.push_back(fs);
}

void LuaTable::addField_String(std::string name, LuaString str)
{
  LuaTableField_String fs;
  fs.name = name;
  fs.value = str.get();
  
  strings.push_back(fs);
}

void LuaTable::addField_Nil(std::string name, LuaNil nil)
{
  nil = nil;
  LuaTableField_Nil fn;
  fn.name = name;
  
  nils.push_back(fn);
}

void LuaTable::addField_Nil(std::string name)
{
  LuaTableField_Nil fn;
  fn.name = name;
  
  nils.push_back(fn);
}

void LuaTable::addField_Number(std::string name, LuaNumber num)
{
  LuaTableField_Number fn;
  fn.name = name;
  fn.value = num.getDouble();
  
  numbers.push_back(fn);
}

void LuaTable::addField_Number(std::string name, double num)
{
  LuaTableField_Number fn;
  fn.name = name;
  fn.value = num;
  
  numbers.push_back(fn);
}

void LuaTable::addField_Boolean(std::string name, LuaBoolean b)
{
  LuaTableField_Boolean fb;
  fb.name = name;
  fb.value = b.get();
  
  booleans.push_back(fb);
}

void LuaTable::addField_Boolean(std::string name, bool b)
{
  LuaTableField_Boolean fb;
  fb.name = name;
  fb.value = b;
  
  booleans.push_back(fb);
}

void LuaTable::addField_Table(std::string name, LuaTable *table)
{
  LuaTableField_Table ft;
  ft.name = name;
  ft.value = table;
  
  tables.push_back(ft);
}

void LuaTable::addField_Function(std::string name, LuaFunction *func)
{
  LuaTableField_Function ff;
  ff.name = name;
  ff.value = func;
  
  functions.push_back(ff);
}

// Les indexes

void LuaTable::addIndex_String(int index, std::string str)
{
  LuaTableIndex_String fs;
  fs.index = index;
  fs.value = str;
  
  i_strings.push_back(fs);
}

void LuaTable::addIndex_String(int index, LuaString str)
{
  LuaTableIndex_String fs;
  fs.index = index;
  fs.value = str.get();
  
  i_strings.push_back(fs);
}

void LuaTable::addIndex_Nil(int index, LuaNil nil)
{
  nil = nil;
  LuaTableIndex_Nil fn;
  fn.index = index;
  
  i_nils.push_back(fn);
}

void LuaTable::addIndex_Nil(int index)
{
  LuaTableIndex_Nil fn;
  fn.index = index;
  
  i_nils.push_back(fn);
}

void LuaTable::addIndex_Number(int index, LuaNumber num)
{
  LuaTableIndex_Number fn;
  fn.index = index;
  fn.value = num.getDouble();
  
  i_numbers.push_back(fn);
}

void LuaTable::addIndex_Number(int index, double num)
{
  LuaTableIndex_Number fn;
  fn.index = index;
  fn.value = num;
  
  i_numbers.push_back(fn);
}

void LuaTable::addIndex_Boolean(int index, LuaBoolean b)
{
  LuaTableIndex_Boolean fb;
  fb.index = index;
  fb.value = b.get();
  
  i_booleans.push_back(fb);
}

void LuaTable::addIndex_Boolean(int index, bool b)
{
  LuaTableIndex_Boolean fb;
  fb.index = index;
  fb.value = b;
  
  i_booleans.push_back(fb);
}

void LuaTable::addIndex_Table(int index, LuaTable *table)
{
  LuaTableIndex_Table ft;
  ft.index = index;
  ft.value = table;
  
  i_tables.push_back(ft);
}

void LuaTable::addIndex_Function(int index, LuaFunction *func)
{
  LuaTableIndex_Function ff;
  ff.index = index;
  ff.value = func;
  
  i_functions.push_back(ff);
}
