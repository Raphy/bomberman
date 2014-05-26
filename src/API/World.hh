/*
** World.hh for bomberman in /home/raphy/Epitech/Tech_2/bomberman/src/api
**
** Made by raphael defreitas
** Login   <defrei_r@epitech.net>
**
** Started on  Mon May 26 17:46:57 2014 raphael defreitas
// Last update Mon May 26 17:59:07 2014 raphael defreitas
*/

#ifndef		WORLD_HH_
# define	WORLD_HH_

# include	<list>

# include	"Player.hh"

namespace API
{
  class World
  {
  public:
    World();
    ~World();

    std::list<Player>& getPlayers(void);

  protected:
    std::list<Player> _players;
  };
}

#endif /* !WORLD_HH_*/
