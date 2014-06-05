//
// GameObject.cpp for Bomberman in /home/raphy/Epitech/Tech_2/bomberman/src/API
// 
// Made by raphael defreitas
// Login   <defrei_r@epitech.net>
// 
// Started on  Tue Jun  3 11:55:16 2014 raphael defreitas
// Last update Thu Jun  5 12:54:26 2014 raphael defreitas
//

#include	<string>

#include	"GameObject.hh"

using namespace API;

GameObject::GameObject(const std::string& type, float x, float y) :
  _type(type), _x(x), _y(y)
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
  registerClass(script);
  registerClassMethods(script);
}

void GameObject::registerClass(Script& script)
{
}

void GameObject::registerClassMethods(Script& script)
{
}

int GameObject::getType(lua_State* L)
{
  return 0;
}

int GameObject::getX(lua_State* L)
{
  return 0;
}

int GameObject::setX(lua_State* L)
{
  return 0;
}

int GameObject::getY(lua_State* L)
{
  return 0;
}

int GameObject::setY(lua_State* L)
{
  return 0;
}
