/*
** SpeedBuff.hh for Bomberman in /home/raphy/Epitech/Tech_2/bomberman/src/API
**
** Made by raphael defreitas
** Login   <defrei_r@epitech.net>
**
** Started on  Tue Jun 03 11:52:41 2014 raphael defreitas
// Last update Sun Jun 15 01:59:53 2014 raphael defreitas
*/

#ifndef		API_SPEEDBUFF_HH_
# define	API_SPEEDBUFF_HH_

# include	<lua.hpp>
# include	<string>

# include	"Item.hh"
# include	"object/SpeedBuff.hh"
# include	"Lua/Script.hh"

using namespace Lua;

namespace API
{
  class SpeedBuff : public Item
  {
  public:
    SpeedBuff(::SpeedBuff* buff);
    ~SpeedBuff(void);

    // Lua implementation
    static void registerScript(Script& script);
    static void registerMethods(Script& script);
  };
}

#endif /* !API_SPEEDBUFF_HH_*/
