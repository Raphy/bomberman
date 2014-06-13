/*
** Bomb.hh for Bomberman in /home/raphy/Epitech/Tech_2/bomberman/src/API
**
** Made by raphael defreitas
** Login   <defrei_r@epitech.net>
**
** Started on  Tue Jun 03 11:52:41 2014 raphael defreitas
// Last update Fri Jun 13 23:37:00 2014 raphael defreitas
*/

#ifndef		BOMB_HH_
# define	BOMB_HH_

# include	<lua.hpp>
# include	<string>

# include	"Item.hh"
# include	"object/Bomb.hh"
# include	"Lua/Script.hh"

using namespace Lua;

namespace API
{
  class Bomb : public Item
  {
  public:
    Bomb(::Bomb* bomb);
    ~Bomb(void);

    double getTime(void) const;

    // Lua implementation
    static void registerScript(Script& script);
    static void registerMethods(Script& script);
    static int getTime(lua_State* L);

  protected:
    ::Bomb* _bomb;
  };
}

#endif /* !BOMB_HH_*/
