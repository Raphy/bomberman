//
// Script.cpp for Bomberman in /home/raphy/Epitech/Tech_2/bomberman/src/Lua
// 
// Made by raphael defreitas
// Login   <defrei_r@epitech.net>
// 
// Started on  Tue Jun  3 12:35:19 2014 raphael defreitas
// Last update Tue Jun 10 22:48:39 2014 raphael defreitas
//

#include	<stdexcept>
#include	<string>

#include	"Script.hh"

using namespace Lua;

Script::Script(const std::string& filename)
{
  if (!this->_vm.loadFile(filename))
    throw new std::runtime_error("LuaScriptLoadingException: " + this->_vm.getError()); // Exception: LuaScriptLoadingException
}

Script::~Script(void)
{
}

VirtualMachine& Script::getVirtualMachine(void)
{
  return this->_vm;
}

bool Script::execute(void)
{
  return this->_vm.execute();
}

bool Script::initialization(void)
{
  return this->_vm.call("initialization");
}

bool Script::play(void)
{
  return this->_vm.call("play");
}
