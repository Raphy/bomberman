//
// AItem.hh for Bomberman in /home/raphy/Epitech/Tech_2/bomberman/src/object
// 
// Made by raphael defreitas
// Login   <defrei_r@epitech.net>
// 
// Started on  Sat Jun 14 01:19:37 2014 raphael defreitas
// Last update Sat Jun 14 01:36:46 2014 raphael defreitas
//

#ifndef		AITEM_HH_
# define	AITEM_HH_

# include	"ACube.hh"

class AItem : public ACube
{
public:
  virtual ~AItem();

  virtual void onCollision(AGameObject& obj) = 0;

  virtual void update(gdl::Clock const &clock, gdl::Input & input) = 0;
  virtual bool initialize() = 0;

  static std::string const Tag;
protected:
  AItem(const std::string& tag = "item");
};
#endif   /* ITEM_HH_ */
