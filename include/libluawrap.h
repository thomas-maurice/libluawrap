#ifndef LUA_WRAP
#define LUA_WRAP

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

/**
  \file libluawrap.h
  \brief This file is the main header of the API
  
  \author Thomas Maurice
  \version 0.3
*/

/**
  \mainpage libluawrap documentation
  
  libluawrap is a C++ library designed to make more easy the interactions between
  C++ and Lua. With this lib it is more easy to export tables, datas and so on
  from C++ to Lua as well as reading data, such as complex tables, from Lua to C++.
  
  Here is a basic example to export variables to Lua
  \include basic_export.cpp
  
  Here is a basic example on how to read tables (for config file for example)
  \include readtable.cpp
*/

extern "C"
{
  #include <lua.h>
  #include <lauxlib.h>
  #include <lualib.h>
}

/** The current version of the API */
#define LIBLUAWRAP_VERSION 0.3

#include "libluawrap/lua_defs.h"
#include "libluawrap/lua_debug.h"
#include "libluawrap/lua_table.h"
#include "libluawrap/lua_number.h"
#include "libluawrap/lua_function.h"
#include "libluawrap/lua_bool.h"
#include "libluawrap/lua_string.h"
#include "libluawrap/lua_nil.h"
#include "libluawrap/lua_wrap.h"
#include "libluawrap/lua_table_element.h"

/**
  \brief Displays a simple message to warn of which version of the library you
  are using
*/
void print_luawrap_version();

	#if defined (linux)
		#define DllExport
	#elif defined (WIN32)
		#define DllExport __declspec(dllexport)
	#endif
	
	// Utilisé pour convertir l'objet "obj" de type quelconque en
	// un pointeur sur void "out"
	#define OBJ_TO_VOID(obj, out) void *out = (void*)obj;
	
	// Utilisé pour convertir le pointeur sur void "vd" en un objet
	// "obj" de type "type"
	#define VOID_TO_OBJ(vd, type, out) type *out = (type*)vd;
	
	#define CHECK_UDATA(Type,Func,Meta) \
	Type * Func(lua_State * L) \
	{\
    void *ud = luaL_checkudata(L, 1, Meta);\
    luaL_argcheck(L, ud != NULL, 1, std::string(std::string(Meta)+ "expected").c_str());\
    return (Type*)ud;\
  }
  
  #define CHECK_UDATA_H(Type,Func) \
	Type * Func(lua_State * L);

#endif
