//
// SpeedBuff.hh for Bomberman in /home/raphy/Epitech/Tech_2/bomberman/src/object
// 
// Made by raphael defreitas
// Login   <defrei_r@epitech.net>
// 
// Started on  Sat Jun 14 01:27:26 2014 raphael defreitas
// Last update Sat Jun 14 01:37:51 2014 raphael defreitas
//

#ifndef		SPEEDBUFF_HH_
# define	SPEEDBUFF_HH_

#include "AItem.hh"

class SpeedBuff: public AItem
{
public:
  static std::string const Tag;

  SpeedBuff();
  virtual ~SpeedBuff();
  virtual void update(gdl::Clock const& clock, gdl::Input& input);
  virtual bool initialize();
  virtual void onCollision(AGameObject& obj);
};

#endif /* SPEEDBUFF_HH_ */

