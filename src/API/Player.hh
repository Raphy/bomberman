/*
** Player.hh for Bomberman in /home/raphy/Epitech/Tech_2/bomberman/src/API
**
** Made by raphael defreitas
** Login   <defrei_r@epitech.net>
**
** Started on  Tue Jun 03 11:52:41 2014 raphael defreitas
// Last update Thu Jun 12 00:53:17 2014 raphael defreitas
*/

#ifndef		PLAYER_HH_
# define	PLAYER_HH_

# include	<lua.hpp>
# include	<string>

# include	"GameObject.hh"
# include	"Lua/Script.hh"

using namespace Lua;

namespace API
{
  class Player : public GameObject
  {
  public:
    Player(const std::string& name, float x = 0, float y = 0);
    ~Player(void);

    virtual size_t size(void) const { return sizeof(*this); }
    const std::string& getName(void) const;

    // Lua implementation
    static void registerScript(Script& script);
    static void registerMethods(Script& script);
    static int ctor(lua_State* L);
    static int dtor(lua_State* L);
    static int getName(lua_State* L);

  protected:
    std::string _name;
  };
}

#endif /* !PLAYER_HH_*/
