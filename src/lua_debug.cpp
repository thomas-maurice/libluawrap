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

#include <lua_debug.h>

void stackDump(lua_State *L)
{
  int i;
  int top = lua_gettop(L);
  for (i = 1; i <= top; i++) {  /* repeat for each level */
    int t = lua_type(L, i);
    switch (t) {
    
      case LUA_TSTRING:  /* strings */
        printf("`%s'", lua_tostring(L, i));
        break;
    
      case LUA_TBOOLEAN:  /* booleans */
        printf(lua_toboolean(L, i) ? "true" : "false");
        break;
    
      case LUA_TNUMBER:  /* numbers */
        printf("%g", lua_tonumber(L, i));
        break;
    
      default:  /* other values */
        printf("%s", lua_typename(L, t));
        break;
    }
    printf("  ");  /* put a separator */
  }
  printf("\n");  /* end the listing */
}
