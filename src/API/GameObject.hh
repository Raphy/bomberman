/*
** GameObject.hh for Bomberman in /home/raphy/Epitech/Tech_2/bomberman/src/API
**
** Made by raphael defreitas
** Login   <defrei_r@epitech.net>
**
** Started on  Tue Jun 03 11:52:41 2014 raphael defreitas
// Last update Wed Jun 11 00:05:07 2014 raphael defreitas
*/

#ifndef		GAMEOBJECT_HH_
# define	GAMEOBJECT_HH_

# include	<lua.hpp>
# include	<string>

# include	"Lua/Script.hh"

using namespace Lua;

namespace API
{
  class GameObject
  {
  public:
    GameObject(float x, float y);
    ~GameObject(void);

    const std::string& getType(void) const;
    float getX(void) const;
    void setX(float value);
    float getY(void) const;
    void setY(float value);

    // Lua implementation
    static void registerScript(Script& script);
    static void registerMethods(Script& script);
    static int ctor(lua_State* L);
    static int dtor(lua_State* L);
    static int getType(lua_State* L);
    static int getX(lua_State* L);
    static int setX(lua_State* L);
    static int getY(lua_State* L);
    static int setY(lua_State* L);

  protected:
    std::string _type;
    float _x;
    float _y;
  };
}

#endif /* !GAMEOBJECT_HH_*/
