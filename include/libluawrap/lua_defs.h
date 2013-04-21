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

#ifndef LUA_DEFINITIONS
#define LUA_DEFINITIONS

#define NUMBER_INT 0
#define NUMBER_DOUBLE 1

extern "C"
{
  #include <lua.h>
  #include <lauxlib.h>
  #include <lualib.h>
}


#include <iostream>
#include <sstream>
#include <vector>
#include <lua_debug.h>

#if defined (WIN32)
    #define DllExport __declspec(dllexport)
#else
    #define DllExport
#endif

class DllExport LuaString;
class DllExport LuaNumber;
class DllExport LuaTable;
class DllExport LuaBoolean;
class DllExport LuaFunction;
class DllExport LuaString;
class DllExport LuaNil;
class DllExport LuaTableElement;

/*! \cond PRIVATE */

struct LuaTableField_Nil {
  std::string name;
};

struct LuaTableField_String {
  std::string name;
  std::string value;
};

struct LuaTableField_Number {
  std::string name;
  int value;
};

struct LuaTableField_Boolean {
  std::string name;
  bool value;
};

struct LuaTableField_Table {
  std::string name;
  LuaTable *value;
};

struct LuaTableField_Function {
  std::string name;
  LuaFunction *value;
};

struct LuaTableIndex_Nil {
  int index;
};

struct LuaTableIndex_String {
  int index;
  std::string value;
};

struct LuaTableIndex_Number {
  int index;
  int value;
};

struct LuaTableIndex_Boolean {
  int index;
  bool value;
};

struct LuaTableIndex_Table {
  int index;
  LuaTable *value;
};

struct LuaTableIndex_Function {
  int index;
  LuaFunction *value;
};

/*! \endcond */

#endif
