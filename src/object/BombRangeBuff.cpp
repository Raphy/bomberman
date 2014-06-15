//
// BombRangeBuff.cpp for Bomberman in /home/raphy/Epitech/Tech_2/bomberman/src/object
// 
// Made by raphael defreitas
// Login   <defrei_r@epitech.net>
// 
// Started on  Sat Jun 14 01:33:58 2014 raphael defreitas
// Last update Sun Jun 15 01:39:52 2014 raphael defreitas
//

#include	"APlayer.hh"
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
  this->scale(glm::vec3(0.75, 0.75, 0.75));
  return this->setTexture(ResourcesPath::asset("textures/range.tga"));
}


void BombRangeBuff::update(gdl::Clock const &clock, gdl::Input &input)
{
}

void BombRangeBuff::onCollision(AGameObject& obj)
{
  if (obj.getType() == "ia" || obj.getType() == "player1" || obj.getType() == "player2")
    {
      APlayer* player = static_cast<APlayer*>(&obj);
      if (player->getBombRange() < 5)
        player->addBombRange();
      this->die();
    }
}
