//
// MyLuaClass.hpp for test in /home/raphy/Epitech/Tech_2/bomberman/src/Lua
// 
// Made by raphael defreitas
// Login   <defrei_r@epitech.net>
// 
// Started on  Tue May 27 22:42:13 2014 raphael defreitas
// Last update Wed May 28 01:29:28 2014 raphael defreitas
//

#include	<assert.h>
#include	<iostream>
#include	<lua.hpp>
#include	<string>

#include	"Script.hh"
using namespace Lua;

class MyLuaClass
{
public:
  MyLuaClass(const std::string& msg) : _msg(msg) {}
  ~MyLuaClass(void) {}

  void printMsg(void) const { std::cout << _msg << std::endl; }

  const std::string& getMsg(void) const { return _msg; }
  void setMsg(const std::string& msg) { _msg = msg; }

  static int luaPrintMsg(lua_State* L)
  {
    Script script(L);

    if (lua_gettop(script.getState()) != 1)
      {
	script.setError("Prototype MyLuaClass::printMsg(void)");
	return (-1);
      }

    MyLuaClass* obj = script.getClass<MyLuaClass>("MyLuaClass");
    obj->printMsg();

    return (0);
  }

  static int luaSetMsg(lua_State* L)
  {
    Script script(L);

    if (lua_gettop(script.getState()) != 2)
      {
	script.setError("Prototype MyLuaClass::setMsg(string)");
	return (-1);
      }

    MyLuaClass* obj = script.getClass<MyLuaClass>("MyLuaClass");
    obj->setMsg(std::string(luaL_checkstring(script.getState(), 2)));

    return (0);
  }

  static void luaRegister(lua_State* L)
  {
    luaL_newmetatable(L, "MyLuaClass");
    int metatable = lua_gettop(L);
    std::cout << "metatable: " << metatable << std::endl;
    lua_pushvalue(L, -1);
    lua_setfield(L, -2, "__index");

    /*lua_pushcfunction(L, &MyLuaClass::luaNew);
      lua_setfield(L,-2, "new");*/

    lua_pushcfunction(L, &MyLuaClass::luaPrintMsg);
    lua_setfield(L,-2, "printMsg");

    lua_pushcfunction(L, &MyLuaClass::luaSetMsg);
    lua_setfield(L,-2, "setMsg");

  }

protected:
  std::string _msg;
};

