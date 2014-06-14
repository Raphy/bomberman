//
// GameObject.cpp for Bomberman in /home/raphy/Epitech/Tech_2/bomberman/src/API
// 
// Made by raphael defreitas
// Login   <defrei_r@epitech.net>
// 
// Started on  Tue Jun  3 11:55:16 2014 raphael defreitas
// Last update Sat Jun 14 03:02:01 2014 raphael defreitas
//

#include	<lua.hpp>
#include	<string>

#include	"GameObject.hh"
#include	"object/AGameObject.hh"
#include	"Lua/Script.hh"
#include	"Lua/VirtualMachine.hh"

using namespace API;
using namespace Lua;

GameObject::GameObject(AGameObject* go) :
  _type("GameObject"), _go(go)
{
}

GameObject::~GameObject(void)
{
}

const std::string& GameObject::getType(void) const
{
  return this->_type;
}

std::tuple<double, double> GameObject::getPosition(void) const
{
  return this->_go->getPosition();
}

AGameObject* GameObject::getAGameObject(void)
{
  return this->_go;
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
      {"getPosition", GameObject::getPosition},
      {"getSpeed", GameObject::getSpeed},
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

int GameObject::getPosition(lua_State* L)
{
  VirtualMachine vm(L);
  GameObject* udata = vm.toClass<GameObject>();
  std::tuple<double, double> position = udata->getPosition();
  lua_pushnumber(L, std::get<0>(position));
  lua_pushnumber(L, std::get<1>(position));
  return 2;
}

int GameObject::getSpeed(lua_State* L)
{
  VirtualMachine vm(L);
  GameObject* udata = vm.toClass<GameObject>();
  lua_pushnumber(L, udata->getSpeed());
  return 1;
}
