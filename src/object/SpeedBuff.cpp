//
// SpeedBuff.cpp for Bomberman in /home/raphy/Epitech/Tech_2/bomberman/src/object
// 
// Made by raphael defreitas
// Login   <defrei_r@epitech.net>
// 
// Started on  Sat Jun 14 01:33:58 2014 raphael defreitas
// Last update Sat Jun 14 01:41:12 2014 raphael defreitas
//

#include	"SpeedBuff.hh"
#include	"ResourcesPath.hh"

std::string const SpeedBuff::Tag = "speed_buff";

SpeedBuff::SpeedBuff() :
  AItem("speed_buff")
{
}

SpeedBuff::~SpeedBuff()
{
}

bool SpeedBuff::initialize()
{
  this->setSpeed(0);
  return this->setTexture(ResourcesPath::asset("textures/wall.tga"));
}


void SpeedBuff::update(gdl::Clock const &clock, gdl::Input &input)
{
}

void SpeedBuff::onCollision(AGameObject& obj)
{

}
