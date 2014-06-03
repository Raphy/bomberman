//
// Player.cpp for Bomberman in /home/raphy/Epitech/Tech_2/bomberman/src/API
// 
// Made by raphael defreitas
// Login   <defrei_r@epitech.net>
// 
// Started on  Tue Jun  3 12:02:27 2014 raphael defreitas
// Last update Tue Jun  3 12:19:26 2014 raphael defreitas
//

#include	<string>

#include	"GameObject.hh"
#include	"Player.hh"

using namespace API;

Player::Player(const std::string& name, float x, float y) :
  GameObject::GameObject("Player", x, y), _name(name)
{
}

Player::~Player(void)
{
}

const std::string& Player::getName(void) const
{
  return this->_name;
}
