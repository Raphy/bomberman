//
// BombRangeBuff.hh for Bomberman in /home/raphy/Epitech/Tech_2/bomberman/src/object
// 
// Made by raphael defreitas
// Login   <defrei_r@epitech.net>
// 
// Started on  Sat Jun 14 01:27:26 2014 raphael defreitas
// Last update Sat Jun 14 02:56:43 2014 raphael defreitas
//

#ifndef		BOMBRANGEBUFF_HH_
# define	BOMBRANGEBUFF_HH_

#include "AItem.hh"

class BombRangeBuff: public AItem
{
public:
  static std::string const Tag;

  BombRangeBuff();
  virtual ~BombRangeBuff();
  virtual void update(gdl::Clock const& clock, gdl::Input& input);
  virtual bool initialize();
  virtual void onCollision(AGameObject& obj);
};

#endif /* BOMBRANGEBUFF_HH_ */

