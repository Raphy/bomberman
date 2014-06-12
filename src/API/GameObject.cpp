//
// GameObject.cpp for Bomberman in /home/raphy/Epitech/Tech_2/bomberman/src/API
// 
// Made by raphael defreitas
// Login   <defrei_r@epitech.net>
// 
// Started on  Tue Jun  3 11:55:16 2014 raphael defreitas
// Last update Wed Jun 11 23:57:03 2014 raphael defreitas
//

#include	<lua.hpp>
#include	<string>

#include	"GameObject.hh"
#include	"Lua/Script.hh"
#include	"Lua/VirtualMachine.hh"

using namespace API;
using namespace Lua;

GameObject::GameObject(float x, float y) :
  _type("GameObject"), _x(x), _y(y)
{
}

GameObject::~GameObject(void)
{
}

const std::string& GameObject::getType(void) const
{
  return this->_type;
}

float GameObject::getX(void) const
{
  return this->_x;
}

float GameObject::getY(void) const
{
  return this->_y;
}

void GameObject::registerScript(Script& script)
{
  luaL_newmetatable(script.getVirtualMachine().getState(), "luaL_GameObject");
  GameObject::registerMethods(script);
  lua_pushvalue(script.getVirtualMachine().getState(), -1);
  lua_setfield(script.getVirtualMachine().getState(), -1, "__index");
  lua_setglobal(script.getVirtualMachine().getState(), "GameObject");
}

void GameObject::registerMethods(Script& script)
{
  luaL_Reg methods[] =
    {
      {"getType", GameObject::getType},
      {"getX", GameObject::getX},
      {"getY", GameObject::getY},
      {"getPosition", GameObject::getPosition},
      {NULL, NULL}
    };
  luaL_setfuncs(script.getVirtualMachine().getState(), methods, 0);
}

int GameObject::getType(lua_State* L)
{
  VirtualMachine vm(L);
  GameObject* udata = vm.toClass<GameObject>();
  lua_pushstring(L, udata->getType().c_str());
  return 1;
}

int GameObject::getX(lua_State* L)
{
  VirtualMachine vm(L);
  GameObject* udata = vm.toClass<GameObject>();
  lua_pushnumber(L, udata->getX());
  return 1;
}

int GameObject::getY(lua_State* L)
{
  VirtualMachine vm(L);
  GameObject* udata = vm.toClass<GameObject>();
  lua_pushnumber(L, udata->getY());
  return 1;
}

int GameObject::getPosition(lua_State* L)
{
  VirtualMachine vm(L);
  GameObject* udata = vm.toClass<GameObject>();
  lua_pushnumber(L, udata->getX());
  lua_pushnumber(L, udata->getY());
  return 2;
}
