//
// BombCapacityBuff.cpp for Bomberman in /home/raphy/Epitech/Tech_2/bomberman/src/object
// 
// Made by raphael defreitas
// Login   <defrei_r@epitech.net>
// 
// Started on  Sat Jun 14 01:33:58 2014 raphael defreitas
// Last update Sun Jun 15 01:46:06 2014 raphael defreitas
//

#include	"APlayer.hh"
#include	"BombCapacityBuff.hh"
#include	"ResourcesPath.hh"

std::string const BombCapacityBuff::Tag = "bomb_capacity_buff";

BombCapacityBuff::BombCapacityBuff() :
  AItem("bomb_range_buff")
{
}

BombCapacityBuff::~BombCapacityBuff()
{
}

bool BombCapacityBuff::initialize()
{
  this->scale(glm::vec3(0.75, 0.75, 0.75));
  return this->setTexture(ResourcesPath::asset("textures/capacity.tga"));
}


void BombCapacityBuff::update(gdl::Clock const &clock, gdl::Input &input)
{
}

void BombCapacityBuff::onCollision(AGameObject& obj)
{
  if (obj.getType() == "ia" || obj.getType() == "player1" || obj.getType() == "player2")
    {
      APlayer* player = static_cast<APlayer*>(&obj);
      if (player->getBombCapacity() < 5)
        player->addBombCapacity();
      this->die();
    }
}
