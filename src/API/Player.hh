/*
** Player.hh for bomberman in /home/raphy/Epitech/Tech_2/bomberman/src/API
**
** Made by raphael defreitas
** Login   <defrei_r@epitech.net>
**
** Started on  Mon May 26 17:48:52 2014 raphael defreitas
// Last update Mon May 26 18:23:19 2014 raphael defreitas
*/

#ifndef		PLAYER_HH_
# define	PLAYER_HH_

# include	<string>

namespace API
{
  class Player
  {
  public:
    Player(void);
    ~Player(void);

    bool moveUp(void);
    bool moveDown(void);
    bool moveLeft(void);
    bool moveRight(void);
    bool putBomb(void);

    const std::string& getName(void) const;
    int getPositionX(void) const;
    int getPositionY(void) const;

  protected:
    std::string _name;
    int _position_x;
    int _position_y;
  };
}

#endif /* !PLAYER_HH_*/
