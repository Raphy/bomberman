/*
** Me.hh for Bomberman in /home/raphy/Epitech/Tech_2/bomberman/src/API
**
** Made by raphael defreitas
** Login   <defrei_r@epitech.net>
**
** Started on  Tue Jun 03 11:52:41 2014 raphael defreitas
// Last update Thu Jun 12 00:53:12 2014 raphael defreitas
*/

#ifndef		ME_HH_
# define	ME_HH_

# include	<string>

# include	"Lua/Script.hh"
# include	"Player.hh"

using namespace Lua;

namespace API
{
  class Me : public Player
  {
  public:
    Me(const std::string& name, float x, float y);
    ~Me(void);

    virtual size_t size(void) const { return sizeof(*this); }

    bool moveUp(void);
    bool moveDown(void);
    bool moveLeft(void);
    bool moveRight(void);
    bool putBomb(void);

    // Lua implementation
    static void registerScript(Script& script);
    static void registerMethods(Script& script);
    static int ctor(lua_State* L);
    static int dtor(lua_State* L);
    static int moveUp(lua_State* L);
    static int moveDown(lua_State* L);
    static int moveLeft(lua_State* L);
    static int moveRight(lua_State* L);
    static int putBomb(lua_State* L);
  };
}

#endif /* !ME_HH_*/
