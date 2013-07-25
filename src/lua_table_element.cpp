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

/**
  Initializes a new LuaTableElement with a given key. The key is wether the name
  of the table if it will be registered as a table, or the key of the element in the
  table. For example, if the key is 'foo', if you globalize the table you can access its
  elements by ```foo.element``` but if this is an element within a table it shall be
  accessed with ```table.foo```
  
  By default, this element will be of type **TABLE**.
  
  \param[in] pkey The key of the element
*/
LuaTableElement::LuaTableElement(std::string pkey) {
  key = pkey;
  is_in_array = false;
  type = TABLE;
}

/**
  Initialize a new table (or table element, but by default it is considered as a table).
*/
LuaTableElement::LuaTableElement() {
  is_in_array = false;
  type = TABLE;
}

/**
  Initialize a new table (or table element, but by default it is considered as a table).
  With the index *pindex*. This is used to create and export arrays in Lua. You sould'nt
  use this for top-level tables.
  
  \param[in] pindex The index
*/
LuaTableElement::LuaTableElement(int pindex) {
  index = pindex;
  is_in_array = true;
  type = TABLE;
}

/**
  Returns the type of the element, the type is one of those defined in the enum luaTableElementTypes
*/
int LuaTableElement::getType() {
  return type;
}

/**
  Sets the value of the element as a numeric value
*/
void LuaTableElement::set(LuaNumber num) {
  type = NUMBER;
  double_value = num.get();
}
/**
  Sets the value of the element as a numeric value (overloaded)
*/
void LuaTableElement::set(double num) {
  type = NUMBER;
  double_value = num;
}
/**
  Sets the value of the element as a numeric value (overloaded)
*/
void LuaTableElement::set(int num) {
  type = NUMBER;
  double_value = num;
}
/**
  Sets the value of the element as a numeric value (overloaded)
*/
void LuaTableElement::set(float num) {
  type = NUMBER;
  double_value = num;
}
/**
  Sets the value of the element as a function value (overloaded)
*/
void LuaTableElement::set(int (*f)(lua_State*)) {
  type = FUNCTION;
  func_value = f;
}

/**
  Sets the value of the element as a function value
*/
void LuaTableElement::set(LuaFunction f) {
  type = FUNCTION;
  func_value = f.getFunction();
}

/**
  Sets the value of the element as a string value
*/
void LuaTableElement::set(LuaString str) {
  type = STRING;
  string_value = str.get();
}
/**
  Sets the value of the element as a string value (overloaded)
*/
void LuaTableElement::set(std::string str) {
  type = STRING;
  string_value = str;
}
/**
  Sets the value of the element as a string value (overloaded)
*/
void LuaTableElement::set(char* str) {
  type = STRING;
  string_value = string(str);
}
/**
  Sets the value of the element as a boolean value
*/
void LuaTableElement::set(LuaBoolean b) {
  type = BOOLEAN;
  bool_value = b.get();
}
/**
  Sets the value of the element as a boolean value (overloaded)
*/
void LuaTableElement::set(bool b) {
  type = BOOLEAN;
  bool_value = b;
}
/**
  Sets the value of the element as a nil value
*/
void LuaTableElement::set(LuaNil n) {
  type = NIL;
}
/**
  Add a children to the LuaTableElement. The type will be changed to **TABLE**. Every
  element added will be a subelement of a table. For example if the base table is named
  'foo' and the element we add is 'bar', it will be accessed by foo.bar in Lua.
  
  \param[in] e The element to add
*/
void LuaTableElement::addChildren(LuaTableElement e) {
  type = TABLE;
  children.push_back(e);
}

/**
  Add a children named function to the LuaTableElement. The type will be changed to
  **TABLE**. Every element added will be a subelement of a table. For example
  if the base table is named 'foo' and the element we add is 'bar', it will
  be accessed by foo.bar in Lua.
  
  \param[in] f a pointer on the function
  \param[in] name The name of the function
*/
void LuaTableElement::addChildren(int (*f)(lua_State*), std::string name) {
  LuaTableElement e(name);
  e.set(f);
  addChildren(e);
}

/**
  Add a children named string to the LuaTableElement. The type will be changed to
  **TABLE**. Every element added will be a subelement of a table. For example
  if the base table is named 'foo' and the element we add is 'bar', it will
  be accessed by foo.bar in Lua.
  
  \param[in] s the string
  \param[in] name The name of the function
*/
void LuaTableElement::addChildren(std::string s, std::string name) {
  LuaTableElement e(name);
  e.set(s);
  addChildren(e);
}

/**
  Add a children named integer to the LuaTableElement. The type will be changed to
  **TABLE**. Every element added will be a subelement of a table. For example
  if the base table is named 'foo' and the element we add is 'bar', it will
  be accessed by foo.bar in Lua.
  
  \param[in] i the integer
  \param[in] name The name of the function
*/
void LuaTableElement::addChildren(int i, std::string name) {
  LuaTableElement e(name);
  e.set(i);
  addChildren(e);
}

/**
  Add a children named double to the LuaTableElement. The type will be changed to
  **TABLE**. Every element added will be a subelement of a table. For example
  if the base table is named 'foo' and the element we add is 'bar', it will
  be accessed by foo.bar in Lua.
  
  \param[in] d the double
  \param[in] name The name of the function
*/
void LuaTableElement::addChildren(double d, std::string name) {
  LuaTableElement e(name);
  e.set(d);
  addChildren(e);
}

/**
  Add a children named float to the LuaTableElement. The type will be changed to
  **TABLE**. Every element added will be a subelement of a table. For example
  if the base table is named 'foo' and the element we add is 'bar', it will
  be accessed by foo.bar in Lua.
  
  \param[in] f the float
  \param[in] name The name of the function
*/
void LuaTableElement::addChildren(float f, std::string name) {
  LuaTableElement e(name);
  e.set(f);
  addChildren(e);
}

/**
  Add a children named boolean to the LuaTableElement. The type will be changed to
  **TABLE**. Every element added will be a subelement of a table. For example
  if the base table is named 'foo' and the element we add is 'bar', it will
  be accessed by foo.bar in Lua.
  
  \param[in] b the boolean
  \param[in] name The name of the function
*/
void LuaTableElement::addChildren(bool b, std::string name) {
  LuaTableElement e(name);
  e.set(b);
  addChildren(e);
}

/**
  Registers the table recursively. The name of the top-level table is its key.
  
  \param[in, out] L The lua context
*/
void LuaTableElement::globalize(lua_State* L) {
  push(L);
  lua_setglobal(L, key.c_str());
}

/**
  Returns the key of the table
*/
std::string LuaTableElement::getKey() {
  return key;
}

/**
  Returns the index of the table
*/
int LuaTableElement::getIndex() {
  return index;
}

/**
  Returns true if the table is an array
*/
bool LuaTableElement::getIsInArray() {
  return is_in_array;
}

/**
  Changes the index
*/
void LuaTableElement::setIndex(int i) {
  index = i;
  is_in_array = true;
}

/**
  Changes the key
*/
void LuaTableElement::setKey(std::string k) {
  key = k;
  is_in_array = false;
}

/**
  Returns a vector cointaining all the children elements of the table
*/
std::vector<LuaTableElement> LuaTableElement::getChildren() {
  return children;
}

/**
  Returns true if the element is nil
*/
bool LuaTableElement::isNil() {
  if(type == NIL) {
    return true;
  }
  
  return false;
}

/**
  Return the string value of the element, if the element is not a string, "" will be returned
*/
std::string LuaTableElement::toString() {
  if(type == STRING)
    return string_value;
  
  return "";
}

/**
  Returns the number value of the element, if it's not a number, 0 will be returned
*/
double LuaTableElement::toNumber() {
  if(type == NUMBER)
    return double_value;
  return 0;
}

/**
  Returns the boolean value of the function, if it's not a boolean, false will be returned
*/
bool LuaTableElement::toBoolean() {
  if(type == BOOLEAN)
    return bool_value;
  return false;
}

/**
  Returns a pointer on the function value of the element. If it's not a function, then NULL will be returned.
*/
int (*LuaTableElement::toFunction(void))(lua_State*) {
  if(type == FUNCTION)
    return func_value;
  return NULL;
}

/**
  Sets the element as nil
*/
void LuaTableElement::setNil() {
  type = NIL;
}

/**
  Returns true if the subelement is nil. The subelement is an element of a table.
  The root table is the element calling this methods, and all the sub elements are
  separated by dots. So if you have a root table 'foo' containing the table 'bar'
  containing the element 'baz' and if you want to test the value of 'baz' you will
  call ```foo.elementIsNil("bar.baz");```
  
  \param[in] element The element you want to test
*/
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
  
  if(cur_elem == "") {
    if(type == NIL)
      return true;
    else
      return false;
  }
  
  for(unsigned int i = 0; i < children.size(); i++) {
    if(cur_elem == children.at(i).getKey()) {
      return children.at(i).elementIsNil(sub_elem);
    }
  }

  return true;
}

/**
  Returns true if the subelement is a string. The subelement is an element of a table.
  The root table is the element calling this methods, and all the sub elements are
  separated by dots. So if you have a root table 'foo' containing the table 'bar'
  containing the element 'baz' and if you want to test the value of 'baz' you will
  call ```foo.elementIsString("bar.baz");```
  
  \param[in] element The element you want to test
*/
bool LuaTableElement::elementIsString(std::string element) {
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
  
  if(cur_elem == "") {
    if(type == STRING)
      return true;
    else
      return false;
  }
  
  for(unsigned int i = 0; i < children.size(); i++) {
    if(cur_elem == children.at(i).getKey()) {
      return children.at(i).elementIsString(sub_elem);
    }
  }

  return false;
}

/**
  Returns true if the subelement is a function. The subelement is an element of a table.
  The root table is the element calling this methods, and all the sub elements are
  separated by dots. So if you have a root table 'foo' containing the table 'bar'
  containing the element 'baz' and if you want to test the value of 'baz' you will
  call ```foo.elementIsFunction("bar.baz");```
  
  \param[in] element The element you want to test
*/
bool LuaTableElement::elementIsFunction(std::string element) {
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
  
  if(cur_elem == "") {
    if(type == FUNCTION)
      return true;
    else
      return false;
  }
  
  for(unsigned int i = 0; i < children.size(); i++) {
    if(cur_elem == children.at(i).getKey()) {
      return children.at(i).elementIsFunction(sub_elem);
    }
  }

  return false;
}

/**
  Returns true if the subelement is a number. The subelement is an element of a table.
  The root table is the element calling this methods, and all the sub elements are
  separated by dots. So if you have a root table 'foo' containing the table 'bar'
  containing the element 'baz' and if you want to test the value of 'baz' you will
  call ```foo.elementIsNumber("bar.baz");```
  
  \param[in] element The element you want to test
*/
bool LuaTableElement::elementIsNumber(std::string element) {
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
  
  if(cur_elem == "") {
    if(type == NUMBER)
      return true;
    else
      return false;
  }
  
  for(unsigned int i = 0; i < children.size(); i++) {
    if(cur_elem == children.at(i).getKey()) {
      return children.at(i).elementIsNumber(sub_elem);
    }
  }

  return false;
}

/**
  Returns true if the subelement is a boolean. The subelement is an element of a table.
  The root table is the element calling this methods, and all the sub elements are
  separated by dots. So if you have a root table 'foo' containing the table 'bar'
  containing the element 'baz' and if you want to test the value of 'baz' you will
  call ```foo.elementIsBoolean("bar.baz");```
  
  \param[in] element The element you want to test
*/
bool LuaTableElement::elementIsBoolean(std::string element) {
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
  
  if(cur_elem == "") {
    if(type == BOOLEAN)
      return true;
    else
      return false;
  }
  
  for(unsigned int i = 0; i < children.size(); i++) {
    if(cur_elem == children.at(i).getKey()) {
      return children.at(i).elementIsBoolean(sub_elem);
    }
  }

  return false;
}

bool LuaTableElement::elementIsTable(std::string element) {
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
  
  if(cur_elem == "") {
    if(type == TABLE)
      return true;
    else
      return false;
  }
  
  for(unsigned int i = 0; i < children.size(); i++) {
    if(cur_elem == children.at(i).getKey()) {
      return children.at(i).elementIsTable(sub_elem);
    }
  }

  return false;
}

/**
  Returns true if the subelement exists. The subelement is an element of a table.
  The root table is the element calling this methods, and all the sub elements are
  separated by dots. So if you have a root table 'foo' containing the table 'bar'
  containing the element 'baz' and if you want to test the value of 'baz' you will
  call ```foo.elementExists("bar.baz");```
  
  \param[in] element The element you want to test
*/
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

/**
  Returns a pointer on the requested element. If the element does not exist, then
  NULL shall be returned.
  
  \param[in] element The element you want to test
*/
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

/**
  Prints the table and all its subtables
*/
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
    case NIL:
        cout << " Nil:" << key;
        break;
    case FUNCTION:
        cout << " Function:" << key;
        break;
    }
  }
}

/**
  Pushes the table AND all the subelements/subtables on the top of the stack. This
  is used to return from Lua functions. To globalize a table into a Lua context you
  should use LuaTableElement::globalize
  
  **DO NOT** use this function to globalize a LuaTableElement which is not included in
  a table, this will make your program to segfault.
  
  \param[in] L The Lua context
  
  \todo Protect the function against single variables not included in a table.
*/
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
      case FUNCTION:
        lua_pushcfunction(L, func_value);
        break; 
    }
    // Let's register it
    lua_settable(L, -3);
  }
}
