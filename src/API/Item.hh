/*
** Item.hh for Bomberman in /home/raphy/Epitech/Tech_2/bomberman/src/API
**
** Made by raphael defreitas
** Login   <defrei_r@epitech.net>
**
** Started on  Tue Jun 03 11:52:41 2014 raphael defreitas
// Last update Fri Jun 13 23:20:19 2014 raphael defreitas
*/

#ifndef		ITEM_HH_
# define	ITEM_HH_

# include	<lua.hpp>
# include	<string>

# include	"GameObject.hh"
# include	"object/AGameObject.hh"
# include	"Lua/Script.hh"

using namespace Lua;

namespace API
{
  class Item : public GameObject
  {
  public:
    Item(AGameObject* go);
    ~Item(void);

    // Lua implementation
    static void registerScript(Script& script);
    static void registerMethods(Script& script);
  };
}

#endif /* !ITEM_HH_*/
