/*
** BombCapacityBuff.hh for Bomberman in /home/raphy/Epitech/Tech_2/bomberman/src/API
**
** Made by raphael defreitas
** Login   <defrei_r@epitech.net>
**
** Started on  Tue Jun 03 11:52:41 2014 raphael defreitas
// Last update Sun Jun 15 02:03:29 2014 raphael defreitas
*/

#ifndef		API_BOMBCAPACITYBUFF_HH_
# define	API_BOMBCAPACITYBUFF_HH_

# include	<lua.hpp>
# include	<string>

# include	"Item.hh"
# include	"object/BombCapacityBuff.hh"
# include	"Lua/Script.hh"

using namespace Lua;

namespace API
{
  class BombCapacityBuff : public Item
  {
  public:
    BombCapacityBuff(::BombCapacityBuff* buff);
    ~BombCapacityBuff(void);

    // Lua implementation
    static void registerScript(Script& script);
    static void registerMethods(Script& script);
  };
}

#endif /* !API_BOMBCAPACITYBUFF_HH_*/
