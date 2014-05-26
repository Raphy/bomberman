//
// VirtualMachine.cpp for bomberman in /home/raphy/Epitech/Tech_2/bomberman/src/Lua
// 
// Made by raphael defreitas
// Login   <defrei_r@epitech.net>
// 
// Started on  Mon May 26 18:22:16 2014 raphael defreitas
// Last update Mon May 26 19:01:06 2014 raphael defreitas
//

#include	<exception>
#include	<lua.hpp>
#include	<string>

#include	"VirtualMachine.hh"

using namespace Lua;

VirtualMachine::VirtualMachine(void)
{
  this->_L = luaL_newstate();
  if (!this->_L)
    throw new std::exception();
}

VirtualMachine::VirtualMachine(lua_State* L)
{
  this->_L = L;
  if (!this->_L)
    throw new std::exception();
}


VirtualMachine::~VirtualMachine(void)
{
  lua_close(this->_L);
}


void VirtualMachine::loadLibraries(void)
{
  luaL_openlibs(this->_L);
}

std::string VirtualMachine::getError(void)
{
  std::string error("ERROR (to complete with   Stack<std::string>(this, -1))  ");

  error = lua_tostring(this->_L, -1);
  return error;
}

bool VirtualMachine::runFile(const std::string& filename)
{
  return (bool)!luaL_dofile(this->_L, filename.c_str());
}

bool VirtualMachine::runString(const std::string& str)
{
  return (bool)!luaL_dostring(this->_L, str.c_str());
}
