/*
** Map.hh for Bomberman in /home/raphy/Epitech/Tech_2/bomberman/src/API
**
** Made by raphael defreitas
** Login   <defrei_r@epitech.net>
**
** Started on  Tue Jun 03 11:52:41 2014 raphael defreitas
// Last update Tue Jun  3 12:16:30 2014 raphael defreitas
*/

#ifndef		MAP_HH_
# define	MAP_HH_

# include	<vector>

# include	"GameObject.hh"

namespace API
{
  class Map
  {
  public:
    Map(void);
    ~Map(void);

    std::vector<GameObject*> get(int x, int y);
  };
}

#endif /* !MAP_HH_*/