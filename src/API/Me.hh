/*
** Me.hh for Bomberman in /home/raphy/Epitech/Tech_2/bomberman/src/API
**
** Made by raphael defreitas
** Login   <defrei_r@epitech.net>
**
** Started on  Tue Jun 03 11:52:41 2014 raphael defreitas
// Last update Sun Jun 15 21:38:12 2014 raphael defreitas
*/

#ifndef		API_ME_HH_
# define	API_ME_HH_

# include	<string>

# include	"object/IA.hh"
# include	"Lua/Script.hh"
# include	"Player.hh"

using namespace Lua;

namespace API
{
  class Me : public Player
  {
  public:
    Me(IA* ia);
    ~Me(void);

    void moveUp(void);
    void moveDown(void);
    void moveLeft(void);
    void moveRight(void);
    void putBomb(void);
    int getBombCapacity() const;
    int getBombRange() const;
    int getBombs() const;

    // Lua implementation
    static void registerScript(Script& script);
    static void registerMethods(Script& script);
    static int moveUp(lua_State* L);
    static int moveDown(lua_State* L);
    static int moveLeft(lua_State* L);
    static int moveRight(lua_State* L);
    static int putBomb(lua_State* L);
    static int getBombCapacity(lua_State* L);
    static int getBombRange(lua_State* L);
    static int getBombs(lua_State* L);


  protected:
    IA* _ia;
  };
}

#endif /* !API_ME_HH_*/
