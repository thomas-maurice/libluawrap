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
#include <lua_function.h>

#include <vector>

/**
  \file lua_table_element.h
  \author Thomas Maurice
  
  \class LuaTableElement
  \brief Lua Table Elements and therefore recursive tables.
  
  Is a new version of the LuaTable class. This one is much more better in the
  way that it is bidirectional for the simple types such as Numbers, Strings,
  Booleans and Tables and unidirectionnal (C++ -> Lua) for the function. This is
  therefore the best class to read from Lua configuration files using the LuaWrap::readTableFromLua
  function.
*/

enum luaTableElementTypes {NUMBER, STRING, BOOLEAN, NIL, TABLE, FUNCTION}; //!< Defines the type of the table elements

class LuaTableElement
{
  public:
    LuaTableElement(); //!< Simple constructor
    LuaTableElement(std::string pkey); //!< Constructor with a 'key'
    LuaTableElement(int pindex); //!< Constructor with an index
    
    void dump(); //!< Displays the table recursively starting from the current node
    
    void setIndex(int i); //!< Changes the index
    void setKey(std::string k); //!< Changes the key
    
    void addChildren(LuaTableElement e); //!< Adds a children to the curent table
    
    void set(LuaNumber num); //!< Changes the value to a Number
    void set(LuaString str); //!< Changes the value to a String 
    void set(LuaBoolean b); //!< Changes the value to a Boolean 
    void set(LuaNil n); //!< Changes the value to Nil
    void set(LuaFunction f); //!< Changes the value to a Function
    
    void setNil(); //!< Sets the value to nil
    
    void set(double num); //!< Sets the value to a Number
    void set(int num); //!< Sets the value to a Number
    void set(float num); //!< Sets the value to a Number
    void set(std::string str); //!< Sets the value to a String
    void set(char* str); //!< Sets the value to a String
    void set(bool b); //!< Sets the value to a Boolean
    void set(int (*f)(lua_State*)); //!< Sets the value to a Function
    
    std::string toString(); //!< Exports to string
    double toNumber(); //!< Exports to number
    bool toBoolean(); //!< Export to boolean
    int (* toFunction(void))(lua_State*); //!< Exports to function
    
    void push(lua_State* L); //!< Pushes the table recursively on the top of the stack
    void globalize(lua_State* L); //!< Registers the table in a Lua context
    
    int getType(); //!< Returns the type like defined in the lua_table_element.h enum
    bool isNil(); //!< Returns true if nil
    std::string getKey(); //!< Returns the key
    int getIndex(); //!< Returns the index
    bool getIsInArray(); //!< Returns true if is part of a array
    
    std::vector<LuaTableElement> getChildren(); //!< Returns the children list
    
    bool elementExists(std::string element); //!< Returns true if the subelement exists
    
    bool elementIsNil(std::string element); //!< Returns true if the subelement is nil
    bool elementIsString(std::string element); //!< Returns true if the subelement is a string
    bool elementIsNumber(std::string element); //!< Returns true if the subelement is a number
    bool elementIsBoolean(std::string element); //!< Returns true if the subelement is a boolean
    bool elementIsTable(std::string element); //!< Returns true if the subelement is a table
    bool elementIsFunction(std::string element); //!< Returns true if the subelement is a function
    
    LuaTableElement *getElement(std::string element); //!< Returns a pointer on the element
    
  private:
    std::vector<LuaTableElement> children; //!< Children list
    std::string key; //!< The key
    int index; //!< The index
    bool is_in_array; //!< Are we in an array ?
    
    int type; //!< Type
    
    double double_value;
    bool bool_value;
    int (*func_value)(lua_State*);
    std::string string_value;
};

#endif
