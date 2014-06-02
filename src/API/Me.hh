/*
** Me.hh for bomberman in /home/raphy/Epitech/Tech_2/bomberman/src/API
**
** Made by raphael defreitas
** Login   <defrei_r@epitech.net>
**
** Started on  Mon May 26 17:48:52 2014 raphael defreitas
// Last update Wed May 28 18:00:27 2014 raphael defreitas
*/

#ifndef		ME_HH_
# define	ME_HH_

# include	<string>

# include	"Lua/Script.hh"

namespace API
{
  class Me
  {
  public:
    Me(const std::string& name, float x, float y);
    ~Me(void);

    const std::string& getName(void) const;
    int getPositionX(void) const;
    int getPositionY(void) const;

    bool moveUp(void);
    bool moveDown(void);
    bool moveLeft(void);
    bool moveRight(void);
    bool putBomb(void);

    /*
    ** Lua implementation
    */
    static void luaRegister(Lua::Script& script);

    static int getName(lua_State* L);
    static int getPositionX(lua_State* L);
    static int getPositionY(lua_State* L);

    static int moveUp(lua_State* L);
    static int moveDown(lua_State* L);
    static int moveLeft(lua_State* L);
    static int moveRight(lua_State* L);
    static int putBomb(lua_State* L);

  protected:
    std::string _name;
    float _position_x;
    float _position_y;
  };
}

#endif /* !ME_HH_*/
