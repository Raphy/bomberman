/*
** Box.hh for Bomberman in /home/raphy/Epitech/Tech_2/bomberman/src/API
**
** Made by raphael defreitas
** Login   <defrei_r@epitech.net>
**
** Started on  Tue Jun 03 11:52:41 2014 raphael defreitas
// Last update Sun Jun 15 01:59:05 2014 raphael defreitas
*/

#ifndef		API_BOX_HH_
# define	API_BOX_HH_

# include	<lua.hpp>
# include	<string>

# include	"GameObject.hh"
# include	"object/Box.hh"
# include	"Lua/Script.hh"

using namespace Lua;

namespace API
{
  class Box : public GameObject
  {
  public:
    Box(::Box* box);
    ~Box(void);

    // Lua implementation
    static void registerScript(Script& script);
    static void registerMethods(Script& script);

  protected:
    ::Box* _box;
  };
}

#endif /* !API_BOX_HH_*/
