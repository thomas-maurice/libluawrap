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

#include <lua_table_element.h>

using namespace std;

LuaTableElement::LuaTableElement(std::string pkey) {
  key = pkey;
  is_in_array = false;
  type = TABLE;
}

LuaTableElement::LuaTableElement() {
  is_in_array = false;
  type = TABLE;
}

LuaTableElement::LuaTableElement(int pindex) {
  index = pindex;
  is_in_array = true;
  type = TABLE;
}

int LuaTableElement::getType() {
  return type;
}

void LuaTableElement::set(LuaNumber num) {
  type = NUMBER;
  double_value = num.get();
}

void LuaTableElement::set(double num) {
  type = NUMBER;
  double_value = num;
}

void LuaTableElement::set(int num) {
  type = NUMBER;
  double_value = num;
}

void LuaTableElement::set(float num) {
  type = NUMBER;
  double_value = num;
}

void LuaTableElement::set(LuaString str) {
  type = STRING;
  string_value = str.get();
}

void LuaTableElement::set(std::string str) {
  type = STRING;
  string_value = str;
}

void LuaTableElement::set(char* str) {
  type = STRING;
  string_value = string(str);
}

void LuaTableElement::set(LuaBoolean b) {
  type = BOOLEAN;
  bool_value = b.get();
}

void LuaTableElement::set(bool b) {
  type = BOOLEAN;
  bool_value = b;
}

void LuaTableElement::set(LuaNil n) {
  type = NIL;
}

void LuaTableElement::addChildren(LuaTableElement e) {
  children.push_back(e);
}

void LuaTableElement::globalize(lua_State* L) {
  push(L);
  lua_setglobal(L, key.c_str());
}

std::string LuaTableElement::getKey() {
  return key;
}

int LuaTableElement::getIndex() {
  return index;
}

bool LuaTableElement::getIsInArray() {
  return is_in_array;
}

void LuaTableElement::setIndex(int i) {
  index = i;
  is_in_array = true;
}

void LuaTableElement::setKey(std::string k) {
  key = k;
  is_in_array = false;
}

std::vector<LuaTableElement> LuaTableElement::getChildren() {
  return children;
}

bool LuaTableElement::isNil() {
  if(type == NIL) {
    return true;
  }
  
  return false;
}

std::string LuaTableElement::toString() {
  if(type == STRING)
    return string_value;
  
  return "";
}

double LuaTableElement::toNumber() {
  if(type == NUMBER)
    return double_value;
  return 0;
}

bool LuaTableElement::toBoolean() {
  if(type == BOOLEAN)
    return bool_value;
  return false;
}

bool LuaTableElement::elementIsNil(std::string element) {
  string cur_elem;
  string sub_elem;
  
  if(element.find(".") == string::npos) {
    sub_elem = "";
    cur_elem = element;
  } else {
    int p = element.find(".");
    cur_elem = element.substr(0, p);
    sub_elem = element.substr(p+1, element.length()-1);
  }
  
  if(cur_elem == "" && type == NIL)
    return true;
  else
    return false;
  
  for(unsigned int i = 0; i < children.size(); i++) {
    if(cur_elem == children.at(i).getKey()) {
      return children.at(i).elementExists(sub_elem);
    }
  }
  
  return true;
}

bool LuaTableElement::elementExists(std::string element) {
  string cur_elem;
  string sub_elem;
  
  if(element.find(".") == string::npos) {
    sub_elem = "";
    cur_elem = element;
  } else {
    int p = element.find(".");
    cur_elem = element.substr(0, p);
    sub_elem = element.substr(p+1, element.length()-1);
  }
  
  if(cur_elem == "")
    return true;
  
  for(unsigned int i = 0; i < children.size(); i++) {
    if(cur_elem == children.at(i).getKey()) {
      return children.at(i).elementExists(sub_elem);
    }
  }
  
  return false;
}

LuaTableElement* LuaTableElement::getElement(std::string element) {
  string cur_elem;
  string sub_elem;
  
  if(element.find(".") == string::npos) {
    sub_elem = "";
    cur_elem = element;
  } else {
    int p = element.find(".");
    cur_elem = element.substr(0, p);
    sub_elem = element.substr(p+1, element.length()-1);
  }
  
  if(cur_elem == "")
    return this;
  
  for(unsigned int i = 0; i < children.size(); i++) {
    if(cur_elem == children.at(i).getKey()) {
      return children.at(i).getElement(sub_elem);
    }
  }
  
  return NULL;
}

void LuaTableElement::dump() {
  if(type == TABLE)
  {
    cout << " Table:" << key << "(";
    for(unsigned int i = 0; i < children.size(); i++) {
      children.at(i).dump();
    }
    cout << ")";
  }
  else {
    switch(type) {
      case NUMBER:
        cout << " Number:" << key << "=" << double_value;
        break;
      case BOOLEAN:
        cout << " Boolean:" << key << "=" << bool_value;
        break;
      case STRING:
        cout << " String:" << key << "=\"" << string_value << "\"";
        break;
    }
  }
}

void LuaTableElement::push(lua_State* L) {
  if(type == TABLE) {  // If we are a table
    luaL_newmetatable(L, key.c_str());
    lua_pushstring(L, "__index");
    luaL_getmetatable(L, key.c_str());
    lua_settable(L, -3);
    
    for(unsigned int i = 0; i < children.size(); i++) {
      children.at(i).push(L);
      if(children.at(i).getType() == TABLE) {
        lua_pop(L, 1);
        
        if(children.at(i).getIsInArray()) {
          lua_pushnumber(L, children.at(i).getIndex());
        } else {
          lua_pushstring(L, children.at(i).getKey().c_str());
        }
        
        luaL_getmetatable(L, children.at(i).getKey().c_str());
        lua_settable(L, -3);
      }
    }
  }
  else { // If we are a table element
    if(is_in_array) {
      lua_pushnumber(L, index);
    } else {
      lua_pushstring(L, key.c_str());
    }
    switch(type) {
      case NUMBER:
        lua_pushnumber(L, double_value);
        break;
      case STRING:
        lua_pushstring(L, string_value.c_str());
        break;
      case NIL:
        lua_pushnil(L);
        break;
      case BOOLEAN:
        lua_pushboolean(L, bool_value);
        break; 
    }
    // Let's register it
    lua_settable(L, -3);
  }
}
