/*
** Me.hh for Bomberman in /home/raphy/Epitech/Tech_2/bomberman/src/API
**
** Made by raphael defreitas
** Login   <defrei_r@epitech.net>
**
** Started on  Tue Jun 03 11:52:41 2014 raphael defreitas
// Last update Tue Jun  3 12:20:54 2014 raphael defreitas
*/

#ifndef		ME_HH_
# define	ME_HH_

# include	<string>

# include	"Player.hh"

namespace API
{
  class Me : public Player
  {
  public:
    Me(const std::string& name, float x, float y);
    ~Me(void);

    bool moveUp(void);
    bool moveDown(void);
    bool moveLeft(void);
    bool moveRight(void);
    bool putBomb(void);
  };
}

#endif /* !ME_HH_*/
