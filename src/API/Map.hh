/*
** Map.hh for Bomberman in /home/raphy/Epitech/Tech_2/bomberman/src/API
**
** Made by raphael defreitas
** Login   <defrei_r@epitech.net>
**
** Started on  Tue Jun 03 11:52:41 2014 raphael defreitas
// Last update Fri Jun 13 22:25:07 2014 raphael defreitas
*/

#ifndef		MAP_HH_
# define	MAP_HH_

# include	<vector>

# include	"game/GameScene.hh"
# include	"GameObject.hh"
# include	"Me.hh"

namespace API
{
  class Map
  {
  public:
    Map(GameScene* gs);
    ~Map(void);

    std::vector<GameObject*> get(int x, int y, int d, Me* me);

    // Lua implementation
    static void registerScript(Script& script);
    static void registerMethods(Script& script);
    static int get(lua_State* L);
    static int free(lua_State* L);

  protected:
    GameScene* _gs;

  };
}

#endif /* !MAP_HH_*/
