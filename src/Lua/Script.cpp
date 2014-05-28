//
// Script.cpp for Bomberman in /home/raphy/Epitech/Tech_2/bomberman/src/Lua
// 
// Made by raphael defreitas
// Login   <defrei_r@epitech.net>
// 
// Started on  Tue May 27 17:59:35 2014 raphael defreitas
// Last update Wed May 28 00:17:20 2014 raphael defreitas
//

#include	<exception>
#include	<lua.hpp>
#include	<string>

#include	"Script.hh"

using namespace Lua;

Script::Script(const std::string& filename) :
  _filename(filename), _close(true)
{
  this->_state = luaL_newstate();
  if (!this->_state)
    throw new std::exception();
  luaL_openlibs(this->_state);
}

Script::Script(lua_State* state) :
  _state(state), _filename("unknown"), _close(false)
{
  if (!this->_state)
    throw new std::exception();
}

Script::~Script(void)
{
  if (this->_state && this->_close)
    lua_close(this->_state);
}

lua_State* Script::getState()
{
  return (this->_state);
}

const std::string& Script::getFilename(void) const
{
  return (this->_filename);
}

std::string Script::getError(void)
{
  return (std::string(lua_tostring(this->_state, lua_gettop(this->_state))));
}

void Script::setError(const std::string& msg)
{
  luaL_error(this->_state, msg.c_str());
}

bool Script::run(void)
{
  if (luaL_loadfile(this->_state, this->_filename.c_str()) || lua_pcall(this->_state, 0, 0, 0))
    return (false);
  return (true);
}

bool Script::_variableExists(const std::string& name)
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

void Script::_clean()
{
  int n = lua_gettop(this->_state);
  lua_pop(this->_state, n);
}
