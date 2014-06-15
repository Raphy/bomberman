//
// BombCapacityBuff.hh for Bomberman in /home/raphy/Epitech/Tech_2/bomberman/src/object
// 
// Made by raphael defreitas
// Login   <defrei_r@epitech.net>
// 
// Started on  Sat Jun 14 01:27:26 2014 raphael defreitas
// Last update Sun Jun 15 01:45:50 2014 raphael defreitas
//

#ifndef		BOMBRANGECAPACITY_HH_
# define	BOMBRANGECAPACITY_HH_

#include "AItem.hh"

class BombCapacityBuff: public AItem
{
public:
  static std::string const Tag;

  BombCapacityBuff();
  virtual ~BombCapacityBuff();
  virtual void update(gdl::Clock const& clock, gdl::Input& input);
  virtual bool initialize();
  virtual void onCollision(AGameObject& obj);
};

#endif /* BOMBRANGECAPACITY_HH_ */

