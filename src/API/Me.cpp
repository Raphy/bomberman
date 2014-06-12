//
// Player.cpp for Bomberman in /home/raphy/Epitech/Tech_2/bomberman/src/API
// 
// Made by raphael defreitas
// Login   <defrei_r@epitech.net>
// 
// Started on  Tue Jun  3 12:02:27 2014 raphael defreitas
// Last update Thu Jun 12 20:24:23 2014 raphael defreitas
//

#include	<lua.hpp>
#include	<string>

#include	"object/IA.hh"
#include	"Lua/Script.hh"
#include	"Lua/VirtualMachine.hh"
#include	"Me.hh"
#include	"Player.hh"

using namespace API;
using namespace Lua;

Me::Me(IA* ia) :
  Player(ia), _ia(ia)
{
  this->_type = "Me";
}

Me::~Me(void)
{
}

void Me::moveUp(void)
{
  this->_ia->goOneCaseUp();
}

void Me::moveDown(void)
{
  this->_ia->goOneCaseDown();
}

void Me::moveLeft(void)
{
  this->_ia->goOneCaseLeft();
}

void Me::moveRight(void)
{
  this->_ia->goOneCaseRight();
}

void Me::putBomb(void)
{
  // ToDo: Perfom this action
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
  udata->moveUp();
  return 0;
}

int Me::moveDown(lua_State* L)
{
  VirtualMachine vm(L);
  Me* udata = vm.toClass<Me>();
  udata->moveDown();
  return 0;
}

int Me::moveLeft(lua_State* L)
{
  VirtualMachine vm(L);
  Me* udata = vm.toClass<Me>();
  udata->moveLeft();
  return 0;
}

int Me::moveRight(lua_State* L)
{
  VirtualMachine vm(L);
  Me* udata = vm.toClass<Me>();
  udata->moveRight();
  return 0;
}

int Me::putBomb(lua_State* L)
{
  VirtualMachine vm(L);
  Me* udata = vm.toClass<Me>();
  udata->putBomb();
  return 0;
}

