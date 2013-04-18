#include <lua_wrap.h>
#include <lua_table_element.h>

using namespace std;
static LuaTableElement getTableOnTop(lua_State* L, int key, int idx);
static LuaTableElement getTableOnTop(lua_State* L, std::string key, int idx);

bool LuaWrap::isNil(lua_State* L, std::string varname)
{
  lua_getglobal(L, varname.c_str());
  if(lua_isnil(L, -1))
    return true;
  return false;
}

static LuaTableElement getTableOnTop(lua_State* L, std::string key, int idx) {
  LuaTableElement result(key);

  if(lua_isnil(L, -1))
    return result;

  lua_pushnil(L);

  while(lua_next(L, idx-2)) {
    LuaTableElement element;
    bool valid_key = true;
    bool string_key = false;
    string skey = "";
    int ikey = 0;
    
    if(lua_isnumber(L, idx-2)) { // Numeric key
      int k = (int)lua_tonumber(L, idx-2);
      element.setIndex(k);
      ikey = k;
    }
    else if(lua_isstring(L, idx-2)) { // string key
      std::string k = lua_tostring(L, idx-2);
      element.setKey(k);
      string_key = true;
      skey = k;
    } else {
      valid_key = false;
    }
    
    if(valid_key) {
      if(lua_isnumber(L, idx-1)) {
        element.set(lua_tonumber(L, idx-1));
      } else if(lua_isstring(L, idx-1)) {
        element.set(string(lua_tostring(L, idx-1)));
      } else if(lua_isboolean(L, idx-1)) {
        element.set(lua_toboolean(L, idx-1));
        cout << lua_tostring(L, idx-1) << endl;
      } else if(lua_istable(L, idx-1)) {
        if(string_key)
          element = getTableOnTop(L, skey, idx);
        else
          element = getTableOnTop(L, ikey, idx);
      }
      result.addChildren(element);
    }
    
    lua_pop(L, 1); // Pops the key
  }
  return result;
}

static LuaTableElement getTableOnTop(lua_State* L, int key, int idx) {
  LuaTableElement result(key);

  if(lua_isnil(L, -1))
    return result;

  lua_pushnil(L);

  while(lua_next(L, idx-2)) {
    LuaTableElement element;
    bool valid_key = true;
    bool string_key = false;
    string skey = "";
    int ikey = 0;
    
    if(lua_isnumber(L, idx-2)) { // Numeric key
      int k = (int)lua_tonumber(L, idx-2);
      element.setIndex(k);
      ikey = k;
    }
    else if(lua_isstring(L, idx-2)) { // string key
      std::string k = lua_tostring(L, idx-2);
      element.setKey(k);
      string_key = true;
      skey = k;
    } else {
      valid_key = false;
    }
    
    if(valid_key) {
      if(lua_isnumber(L, idx-1)) {
        element.set(lua_tonumber(L, idx-1));
      } else if(lua_isstring(L, idx-1)) {
        element.set(string(lua_tostring(L, idx-1)));
      } else if(lua_isboolean(L, idx-1)) {
        element.set(lua_toboolean(L, idx-1));
        cout << lua_tostring(L, idx-1) << endl;
      } else if(lua_istable(L, idx-1)) {
        if(string_key)
          element = getTableOnTop(L, skey, idx);
        else
          element = getTableOnTop(L, ikey, idx);
      }
      result.addChildren(element);
    }
    
    lua_pop(L, 1); // Pops the key
  }
  return result;
}

LuaTableElement LuaWrap::readTableFromLua(lua_State *L, std::string var) {
  LuaTableElement result(var);
  lua_getglobal(L, var.c_str());
  if(lua_isnil(L, -1))
    return result;
    
  lua_pushnil(L);

  while(lua_next(L, -2)) {
    LuaTableElement element;
    bool valid_key = true;
    bool string_key = false;
    string skey = "";
    int ikey = 0;
    
    if(lua_isnumber(L, -2)) { // Numeric key
      int k = (int)lua_tonumber(L, -2);
      element.setIndex(k);
      ikey = k;
    }
    else if(lua_isstring(L, -2)) { // string key
      std::string k = lua_tostring(L, -2);
      element.setKey(k);
      string_key = true;
      skey = k;
    } else {
      valid_key = false;
    }
    
    if(valid_key) {
      if(lua_isnumber(L, -1)) {
        element.set(lua_tonumber(L, -1));
      } else if(lua_isstring(L, -1)) {
        element.set(lua_tostring(L, -1));
      } else if(lua_isboolean(L, -1)) {
        element.set(lua_toboolean(L, -1));
      } else if(lua_istable(L, -1)) {
        if(string_key)
          element = getTableOnTop(L, skey, 0);
        else
          element = getTableOnTop(L, ikey, 0);
      }
      result.addChildren(element);
      
    }
    
    lua_pop(L, 1); // Pops the key
  }
  lua_pop(L, 1); // Pops the table
  return result;
}
