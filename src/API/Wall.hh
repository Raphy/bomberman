/*
** Wall.hh for Bomberman in /home/raphy/Epitech/Tech_2/bomberman/src/API
**
** Made by raphael defreitas
** Login   <defrei_r@epitech.net>
**
** Started on  Tue Jun 03 11:52:41 2014 raphael defreitas
// Last update Sun Jun 15 01:58:25 2014 raphael defreitas
*/

#ifndef		API_WALL_HH_
# define	API_WALL_HH_

# include	<lua.hpp>
# include	<string>

# include	"GameObject.hh"
# include	"object/Wall.hh"
# include	"Lua/Script.hh"

using namespace Lua;

namespace API
{
  class Wall : public GameObject
  {
  public:
    Wall(::Wall* wall);
    ~Wall(void);

    // Lua implementation
    static void registerScript(Script& script);
    static void registerMethods(Script& script);

  protected:
    ::Wall* _wall;
  };
}

#endif /* !API_WALL_HH_*/
