//
// VirtualMachine.cpp for Bomberman in /home/raphy/Epitech/Tech_2/bomberman/src/Lua
// 
// Made by raphael defreitas
// Login   <defrei_r@epitech.net>
// 
// Started on  Tue Jun  3 11:49:12 2014 raphael defreitas
// Last update Thu Jun  5 14:04:10 2014 raphael defreitas
//

#include	<lua.hpp>
#include	<string>

#include	"VirtualMachine.hh"

using namespace Lua;

VirtualMachine::VirtualMachine(void)
{
  this->_state = luaL_newstate();
  if (!this->_state)
    throw new std::exception(); // Exception: LuaInterpreterException
  luaL_openlibs(this->_state);
}

VirtualMachine::~VirtualMachine(void)
{
  if (this->_state)
    lua_close(this->_state);
}

lua_State* VirtualMachine::getState(void)
{
  return this->_state;
}

std::string VirtualMachine::getError(void)
{
  return (std::string(lua_tostring(this->_state, lua_gettop(this->_state))));
}

void VirtualMachine::setError(const std::string& error)
{
  luaL_error(this->_state, error.c_str());
}

bool VirtualMachine::loadFile(const std::string& filename)
{
  return luaL_loadfile(this->_state, filename.c_str()) == LUA_OK;
}

bool VirtualMachine::execute(void)
{
  return lua_pcall(this->_state, 0, LUA_MULTRET, 0) == LUA_OK;
}

bool VirtualMachine::call(const std::string& name)
{
  lua_getglobal(this->_state, name.c_str());
  return lua_pcall(this->_state, 0, 0, 0) == LUA_OK;
}

bool VirtualMachine::_variableExists(const std::string& name)
{
  int level = 0;
  std::string var = "";

  for(unsigned int i = 0; i < name.size(); i++)
    {
      if(name.at(i) == '.')
        {
          if(level == 0)
            lua_getglobal(this->_state, var.c_str());
          else
            lua_getfield(this->_state, -1, var.c_str());

          if(lua_isnil(this->_state, -1))
            return false;

          var = "";
          level++;
        }
      else
        var += name.at(i);
    }

  if(level == 0)
    lua_getglobal(this->_state, var.c_str());
  else
    lua_getfield(this->_state, -1, var.c_str());
  if(lua_isnil(this->_state, -1))
    return false;

  return true;
}

/*void VirtualMachine::_cleanStack()
{
  lua_pop(this->_state, lua_gettop(this->_state));
  }*/
