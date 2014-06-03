//
// Player.cpp for Bomberman in /home/raphy/Epitech/Tech_2/bomberman/src/API
// 
// Made by raphael defreitas
// Login   <defrei_r@epitech.net>
// 
// Started on  Tue Jun  3 12:02:27 2014 raphael defreitas
// Last update Tue Jun  3 12:22:59 2014 raphael defreitas
//

#include	<string>

#include	"Me.hh"
#include	"Player.hh"

using namespace API;

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
  return true;
}

bool Me::moveDown(void)
{
  // ToDo: Perfom this action
  return true;
}

bool Me::moveLeft(void)
{
  // ToDo: Perfom this action
  return true;
}

bool Me::moveRight(void)
{
  // ToDo: Perfom this action
  return true;
}

bool Me::putBomb(void)
{
  // ToDo: Perfom this action
  return true;
}
