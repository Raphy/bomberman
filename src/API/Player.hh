/*
** Player.hh for Bomberman in /home/raphy/Epitech/Tech_2/bomberman/src/API
**
** Made by raphael defreitas
** Login   <defrei_r@epitech.net>
**
** Started on  Tue Jun 03 11:52:41 2014 raphael defreitas
// Last update Tue Jun  3 12:19:05 2014 raphael defreitas
*/

#ifndef		PLAYER_HH_
# define	PLAYER_HH_

# include	<string>

# include	"GameObject.hh"

namespace API
{
  class Player : public GameObject
  {
  public:
    Player(const std::string& name, float x = 0, float y = 0);
    ~Player(void);

    const std::string& getName(void) const;

  protected:
    std::string _name;
  };
}

#endif /* !PLAYER_HH_*/
