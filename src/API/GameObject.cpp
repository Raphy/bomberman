//
// GameObject.cpp for Bomberman in /home/raphy/Epitech/Tech_2/bomberman/src/API
// 
// Made by raphael defreitas
// Login   <defrei_r@epitech.net>
// 
// Started on  Tue Jun  3 11:55:16 2014 raphael defreitas
// Last update Wed Jun 11 18:33:05 2014 raphael defreitas
//

#include	<lua.hpp>
#include	<string>

#include	"GameObject.hh"

using namespace API;

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

void GameObject::setX(float value)
{
  this->_x = value;
}

float GameObject::getY(void) const
{
  return this->_y;
}

void GameObject::setY(float value)
{
  this->_y = value;
}

void GameObject::registerScript(Script& script)
{
  luaL_newmetatable(script.getVirtualMachine().getState(), "luaL_GameObject");

  /*luaL_Reg meta[] =
    {
      {"new", GameObject::ctor},
      {"__gc", GameObject::dtor},
      {NULL, NULL}
    };
    luaL_setfuncs(script.getVirtualMachine().getState(), meta, 0);*/
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
      {"setX", GameObject::setX},
      {"getY", GameObject::getY},
      {"setY", GameObject::setY},
      {NULL, NULL}
    };
  luaL_setfuncs(script.getVirtualMachine().getState(), methods, 0);
}

int GameObject::ctor(lua_State* L)
{
  float x = luaL_checknumber(L, 2);
  float y = luaL_checknumber(L, 3);
  GameObject** udata = (GameObject**)lua_newuserdata(L, sizeof(GameObject*));
  *udata = new GameObject(x, y);
  luaL_getmetatable(L, "luaL_GameObject");
  lua_setmetatable(L, -2);
  return 1;
}

int GameObject::dtor(lua_State* L)
{
  GameObject* udata = *(GameObject**)lua_touserdata(L, 1);
  delete udata;
  return 0;
}

int GameObject::getType(lua_State* L)
{
  GameObject* udata = *(GameObject**)lua_touserdata(L, 1);
  lua_pushstring(L, udata->getType().c_str());
  return 1;
}

int GameObject::getX(lua_State* L)
{
  GameObject* udata = *(GameObject**)lua_touserdata(L, 1);
  lua_pushnumber(L, udata->getX());
  return 1;
}

int GameObject::setX(lua_State* L)
{
  GameObject* udata = *(GameObject**)lua_touserdata(L, 1);
  float x = luaL_checknumber(L, 2);
  udata->setX(x);
  return 1;
}

int GameObject::getY(lua_State* L)
{
  GameObject* udata = *(GameObject**)lua_touserdata(L, 1);
  lua_pushnumber(L, udata->getY());
  return 1;
}

int GameObject::setY(lua_State* L)
{
  GameObject* udata = *(GameObject**)lua_touserdata(L, 1);
  float y = luaL_checknumber(L, 2);
  udata->setY(y);
  return 0;
}
