/*
** Fire.hh for Bomberman in /home/raphy/Epitech/Tech_2/bomberman/src/API
**
** Made by raphael defreitas
** Login   <defrei_r@epitech.net>
**
** Started on  Tue Jun 03 11:52:41 2014 raphael defreitas
// Last update Sun Jun 15 21:30:45 2014 raphael defreitas
*/

#ifndef		API_FIRE_HH_
# define	API_FIRE_HH_

# include	<lua.hpp>
# include	<string>

# include	"GameObject.hh"
# include	"object/Fire.hh"
# include	"Lua/Script.hh"

using namespace Lua;

namespace API
{
  class Fire : public GameObject
  {
  public:
    Fire(::Fire* fire);
    ~Fire(void);

    // Lua implementation
    static void registerScript(Script& script);
    static void registerMethods(Script& script);
  };
}

#endif /* !API_FIRE_HH_*/
