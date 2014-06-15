/*
** Map.hh for Bomberman in /home/raphy/Epitech/Tech_2/bomberman/src/API
**
** Made by raphael defreitas
** Login   <defrei_r@epitech.net>
**
** Started on  Tue Jun 03 11:52:41 2014 raphael defreitas
// Last update Sun Jun 15 01:58:48 2014 raphael defreitas
*/

#ifndef		API_MAP_HH_
# define	API_MAP_HH_

# include	<vector>

# include	"GameObject.hh"
# include	"Me.hh"

namespace API
{
  class Map
  {
  public:
    Map(void);
    ~Map(void);

    std::vector<GameObject*> get(int x, int y, int d, Me* me);

    // Lua implementation
    static void registerScript(Script& script);
    static void registerMethods(Script& script);
    static int get(lua_State* L);
    static int free(lua_State* L);
  };
}

#endif /* !API_MAP_HH_*/
