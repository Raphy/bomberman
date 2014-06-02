//
// Me.cpp for bomberman in 
// 
// Made by raphael defreitas
// Login   <defrei_r@epitech.net>
// 
// Started on  Mon May 26 17:51:39 2014 raphael defreitas
// Last update Wed May 28 18:03:36 2014 raphael defreitas
//

#include	<string>

#include	"Lua/lua.hpp"
#include	"Lua/Script.hh"
#include	"Me.hh"

using namespace API;

Me::Me(const std::string& name, float x, float y) :
  _name(name), _position_x(x), _position_y(y)
{
}

Me::~Me(void)
{
}

bool Me::moveUp(void)
{
  return false;
}

bool Me::moveDown(void)
{
  return true;
}

bool Me::moveLeft(void)
{
  return true;
}

bool Me::moveRight(void)
{
  return true;
}

bool Me::putBomb(void)
{
  return true;
}

const std::string& Me::getName(void) const
{
  return this->_name;
}

int Me::getPositionX(void) const
{
  return this->_position_x;
}

int Me::getPositionY(void) const
{
  return this->_position_y;
}

/*
** Lua implementation
*/
void Me::luaRegister(Lua::Script& script)
{
  // Registering the class name
  luaL_newmetatable(script.getState(), "Me");
  lua_pushvalue(script.getState(), -1);

  // Registering the __index
  lua_setfield(script.getState(), -2, "__index");

  // Registering the method Me::getName()
  lua_pushcfunction(script.getState(), &Me::getName);
  lua_setfield(script.getState(), -2, "getName");

  // Registering the method Me::getPositionX()
  lua_pushcfunction(script.getState(), &Me::getPositionX);
  lua_setfield(script.getState(), -2, "getPositionX");

  // Registering the method Me::getPositionY()
  lua_pushcfunction(script.getState(), &Me::getPositionY);
  lua_setfield(script.getState(), -2, "getPositionY");

  // Registering the method Me::moveUp()
  lua_pushcfunction(script.getState(), &Me::moveUp);
  lua_setfield(script.getState(), -2, "moveUp");

  // Registering the method Me::moveDown()
  lua_pushcfunction(script.getState(), &Me::moveDown);
  lua_setfield(script.getState(), -2, "moveDown");

  // Registering the method Me::moveLeft()
  lua_pushcfunction(script.getState(), &Me::moveLeft);
  lua_setfield(script.getState(), -2, "moveLeft");

  // Registering the method Me::moveRight()
  lua_pushcfunction(script.getState(), &Me::moveRight);
  lua_setfield(script.getState(), -2, "moveRight");

  // Registering the method Me::putBomb()
  lua_pushcfunction(script.getState(), &Me::putBomb);
  lua_setfield(script.getState(), -2, "putBomb");
}

int Me::getName(lua_State* L)
{
  Lua::Script script(L);

  if (lua_gettop(script.getState()) != 1)
    {
      script.setError("Prototype Me::getName(void)");
      return (-1);
    }

  Me* obj = script.getClass<Me>("Me");
  lua_pushstring(script.getState(), obj->getName().c_str());
  return (1);
}

int Me::getPositionX(lua_State* L)
{
  Lua::Script script(L);

  if (lua_gettop(script.getState()) != 1)
    {
      script.setError("Prototype Me::getPositionX(void)");
      return (-1);
    }

  Me* obj = script.getClass<Me>("Me");
  lua_pushnumber(script.getState(), (lua_Number)obj->getPositionX());
  return (1);
}

int Me::getPositionY(lua_State* L)
{
  Lua::Script script(L);

  if (lua_gettop(script.getState()) != 1)
    {
      script.setError("Prototype Me::getPositionY(void)");
      return (-1);
    }

  Me* obj = script.getClass<Me>("Me");
  lua_pushnumber(script.getState(), obj->getPositionY());
  return (1);
}

int Me::moveUp(lua_State* L)
{
  Lua::Script script(L);

  if (lua_gettop(script.getState()) != 1)
    {
      script.setError("Prototype Me::moveUp(void)");
      return (-1);
    }

  Me* obj = script.getClass<Me>("Me");
  if (obj->moveUp())
    lua_pushboolean(script.getState(), 1);
  else
    lua_pushboolean(script.getState(), 0);
  return (1);
}

int Me::moveDown(lua_State* L)
{
  Lua::Script script(L);

  if (lua_gettop(script.getState()) != 1)
    {
      script.setError("Prototype Me::moveDown(void)");
      return (-1);
    }

  Me* obj = script.getClass<Me>("Me");
  if (obj->moveDown())
    lua_pushboolean(script.getState(), 1);
  else
    lua_pushboolean(script.getState(), 0);
  return (1);
}

int Me::moveLeft(lua_State* L)
{
  Lua::Script script(L);

  if (lua_gettop(script.getState()) != 1)
    {
      script.setError("Prototype Me::moveLeft(void)");
      return (-1);
    }

  Me* obj = script.getClass<Me>("Me");
  if (obj->moveLeft())
    lua_pushboolean(script.getState(), 1);
  else
    lua_pushboolean(script.getState(), 0);
  return (1);
}

int Me::moveRight(lua_State* L)
{
  Lua::Script script(L);

  if (lua_gettop(script.getState()) != 1)
    {
      script.setError("Prototype Me::moveRight(void)");
      return (-1);
    }

  Me* obj = script.getClass<Me>("Me");
  if (obj->moveRight())
    lua_pushboolean(script.getState(), 1);
  else
    lua_pushboolean(script.getState(), 0);
  return (1);
}

int Me::putBomb(lua_State* L)
{
  Lua::Script script(L);

  if (lua_gettop(script.getState()) != 1)
    {
      script.setError("Prototype Me::putBomb(void)");
      return (-1);
    }

  Me* obj = script.getClass<Me>("Me");
  if (obj->putBomb())
    lua_pushboolean(script.getState(), 1);
  else
    lua_pushboolean(script.getState(), 0);
  return (1);
}
