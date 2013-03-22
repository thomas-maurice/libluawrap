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

extern "C"
{
  #include <lua.h>
  #include <lauxlib.h>
  #include <lualib.h>
}

#include "libluawrap/lua_defs.h"
#include "libluawrap/lua_debug.h"
#include "libluawrap/lua_table.h"
#include "libluawrap/lua_number.h"
#include "libluawrap/lua_function.h"
#include "libluawrap/lua_bool.h"
#include "libluawrap/lua_string.h"
#include "libluawrap/lua_nil.h"
#include "libluawrap/lua_wrap.h"

void print_luawrap_version();

#endif
