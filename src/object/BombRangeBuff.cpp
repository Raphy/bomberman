//
// BombRangeBuff.cpp for Bomberman in /home/raphy/Epitech/Tech_2/bomberman/src/object
// 
// Made by raphael defreitas
// Login   <defrei_r@epitech.net>
// 
// Started on  Sat Jun 14 01:33:58 2014 raphael defreitas
// Last update Sat Jun 14 02:56:17 2014 raphael defreitas
//

#include	"BombRangeBuff.hh"
#include	"ResourcesPath.hh"

std::string const BombRangeBuff::Tag = "bomb_range_buff";

BombRangeBuff::BombRangeBuff() :
  AItem("bomb_range_buff")
{
}

BombRangeBuff::~BombRangeBuff()
{
}

bool BombRangeBuff::initialize()
{
  this->setSpeed(0);
  return this->setTexture(ResourcesPath::asset("textures/wall.tga"));
}


void BombRangeBuff::update(gdl::Clock const &clock, gdl::Input &input)
{
}

void BombRangeBuff::onCollision(AGameObject& obj)
{

}
