//
// Player.cpp for bomberman in 
// 
// Made by raphael defreitas
// Login   <defrei_r@epitech.net>
// 
// Started on  Mon May 26 17:51:39 2014 raphael defreitas
// Last update Mon May 26 17:55:40 2014 raphael defreitas
//

#include	"Player.hh"

using namespace API;

Player::Player(void)
{

}

Player::~Player()
{

}

bool Player::moveUp(void)
{
  return true;
}

bool Player::moveDown(void)
{
  return true;
}

bool Player::moveLeft(void)
{
  return true;
}

bool Player::moveRight(void)
{
  return true;
}

bool Player::putBomb(void)
{
  return true;
}

const std::string& Player::getName(void) const
{
  return this->_name;
}

int Player::getPositionX(void) const
{
  return this->_position_x;
}

int Player::getPositionY(void) const
{
  return this->_position_y;
}
