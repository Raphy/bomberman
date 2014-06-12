//
// Player.cpp for Bomberman in /home/raphy/Epitech/Tech_2/bomberman/src/API
// 
// Made by raphael defreitas
// Login   <defrei_r@epitech.net>
// 
// Started on  Tue Jun  3 12:02:27 2014 raphael defreitas
// Last update Wed Jun 11 21:05:38 2014 raphael defreitas
//

#include	<lua.hpp>
#include	<string>

#include	"Lua/Script.hh"
#include	"Lua/VirtualMachine.hh"
#include	"Me.hh"
#include	"Player.hh"

using namespace API;
using namespace Lua;

Me::Me(const std::string& name, float x, float y) :
  Player(name, x, y)
{
  this->_type = "Me";
}

Me::~Me(void)
{
}

bool Me::moveUp(void)
{
  // ToDo: Perfom this action
  this->_y -= 1;
  return true;
}

bool Me::moveDown(void)
{
  // ToDo: Perfom this action
  this->_y += 1;
  return true;
}

bool Me::moveLeft(void)
{
  // ToDo: Perfom this action
  this->_x -= 1;
  return true;
}

bool Me::moveRight(void)
{
  // ToDo: Perfom this action
  this->_x += 1;
  return true;
}

bool Me::putBomb(void)
{
  // ToDo: Perfom this action
  return false;
}

void Me::registerScript(Script& script)
{
  luaL_newmetatable(script.getVirtualMachine().getState(), "luaL_Me");
  Me::registerMethods(script);
  lua_pushvalue(script.getVirtualMachine().getState(), -1);
  lua_setfield(script.getVirtualMachine().getState(), -1, "__index");
  lua_setglobal(script.getVirtualMachine().getState(), "Me");
}

void Me::registerMethods(Script& script)
{
  Player::registerMethods(script);
  luaL_Reg methods[] =
    {
      {"moveUp", Me::moveUp},
      {"moveDown", Me::moveDown},
      {"moveLeft", Me::moveLeft},
      {"moveRight", Me::moveRight},
      {"putBomb", Me::putBomb},
      {NULL, NULL}
    };
  luaL_setfuncs(script.getVirtualMachine().getState(), methods, 0);
}

int Me::moveUp(lua_State* L)
{
  VirtualMachine vm(L);
  Me* udata = vm.toClass<Me>();
  lua_pushboolean(vm.getState(), udata->moveUp() ? 1 : 0);
  return 1;
}

int Me::moveDown(lua_State* L)
{
  VirtualMachine vm(L);
  Me* udata = vm.toClass<Me>();
  lua_pushboolean(L, udata->moveDown() ? 1 : 0);
  return 1;
}

int Me::moveLeft(lua_State* L)
{
  VirtualMachine vm(L);
  Me* udata = vm.toClass<Me>();
  lua_pushboolean(L, udata->moveLeft() ? 1 : 0);
  return 1;
}

int Me::moveRight(lua_State* L)
{
  VirtualMachine vm(L);
  Me* udata = vm.toClass<Me>();
  lua_pushboolean(L, udata->moveRight() ? 1 : 0);
  return 1;
}

int Me::putBomb(lua_State* L)
{
  VirtualMachine vm(L);
  Me* udata = vm.toClass<Me>();
  lua_pushboolean(L, udata->putBomb() ? 1 : 0);
  return 1;
}

