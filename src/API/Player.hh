/*
** Player.hh for Bomberman in /home/raphy/Epitech/Tech_2/bomberman/src/API
**
** Made by raphael defreitas
** Login   <defrei_r@epitech.net>
**
** Started on  Tue Jun 03 11:52:41 2014 raphael defreitas
// Last update Fri Jun 13 21:41:40 2014 raphael defreitas
*/

#ifndef		PLAYER_HH_
# define	PLAYER_HH_

# include	<lua.hpp>
# include	<string>

# include	"GameObject.hh"
# include	"object/IA.hh"
# include	"object/Marvin.hh"
# include	"Lua/Script.hh"

using namespace Lua;

namespace API
{
  class Player : public GameObject
  {
  public:
    Player(Marvin* marvin);
    Player(IA* ia);
    ~Player(void);

    const std::string& getName(void) const;

    // Lua implementation
    static void registerScript(Script& script);
    static void registerMethods(Script& script);

  protected:
    Marvin* _marvin;
    IA* _ia;
  };
}

#endif /* !PLAYER_HH_*/
