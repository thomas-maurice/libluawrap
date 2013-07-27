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
	\file macros.h
	\brief Definition of some useful macros
	\author Thomas Maurice
	\version 0.3
*/

#ifndef MACROS_HEADER
#define MACROS_HEADER

	#if defined (linux)
		#define DllExport
	#elif defined (WIN32)
		#define DllExport __declspec(dllexport)
	#endif
	
	/**
		\def OBJ_TO_VOID(obj, out)
		Convert an object into a pointer to void
	*/
	#define OBJ_TO_VOID(obj, out) void *out = (void*)obj;
	
	/**
		\def VOID_TO_OBJ(vd, type, out)
		Convert a pointer to void to a pointer to an object
	*/
	#define VOID_TO_OBJ(vd, type, out) type *out = (type*)vd;
	
	/**
		\def CHECK_UDATA(Type,Func,Meta)
		Creates a function that checks that the lua type is correct and return
		the good userdata pointer
	*/
	#define CHECK_UDATA(Type,Func,Meta) \
	Type * Func(lua_State * L, int i) \
	{\
    void *ud = luaL_checkudata(L, i, Meta);\
    luaL_argcheck(L, ud != NULL, i, std::string(std::string(Meta)+ "expected").c_str());\
    return (Type*)ud;\
  }
  
  /**
		\def CHECK_UDATA_H(Type,Func)
		Creates a function declaration for the macro above
	*/
  #define CHECK_UDATA_H(Type,Func) \
	Type * Func(lua_State * L, int i = 1);
	
#endif
