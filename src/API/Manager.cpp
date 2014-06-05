//
// Manager.cpp for Bomberman in /home/raphy/Epitech/Tech_2/bomberman/src/API
// 
// Made by raphael defreitas
// Login   <defrei_r@epitech.net>
// 
// Started on  Thu Jun  5 10:41:01 2014 raphael defreitas
// Last update Thu Jun  5 12:44:58 2014 raphael defreitas
//

#include	"Lua/Script.hh"
#include	"Manager.hh"

using namespace API;
using namespace Lua;

Manager Manager::_instance = Manager();

Manager& Manager::getInstance(void)
{
  return _instance;
}

bool Manager::registerScript(Script& script)
{
  
  return true;
}

Manager::Manager(void)
{
}

Manager::~Manager(void)
{
}


