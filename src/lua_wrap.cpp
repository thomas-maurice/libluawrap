#include <lua_wrap.h>

bool LuaWrap::isNil(lua_State* L, std::string varname)
{
  lua_getglobal(L, varname.c_str());
  if(lua_isnil(L, -1))
    return true;
  return false;
}
