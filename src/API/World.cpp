//
// World.cpp for bomberman in 
// 
// Made by raphael defreitas
// Login   <defrei_r@epitech.net>
// 
// Started on  Mon May 26 17:57:17 2014 raphael defreitas
// Last update Mon May 26 18:23:14 2014 raphael defreitas
//

#include	"Player.hh"
#include	"World.hh"

using namespace API;

World::World(void)
{

}

World::~World(void)
{

}

std::list<Player>& World::getPlayers(void)
{
  return this->_players;
}
