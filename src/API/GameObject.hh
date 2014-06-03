/*
** GameObject.hh for Bomberman in /home/raphy/Epitech/Tech_2/bomberman/src/API
**
** Made by raphael defreitas
** Login   <defrei_r@epitech.net>
**
** Started on  Tue Jun 03 11:52:41 2014 raphael defreitas
// Last update Tue Jun  3 12:07:25 2014 raphael defreitas
*/

#ifndef		GAMEOBJECT_HH_
# define	GAMEOBJECT_HH_

# include	<string>

namespace API
{
  class GameObject
  {
  public:
    GameObject(const std::string& type = "GameObject", float x = 0, float y = 0);
    ~GameObject(void);

    const std::string& getType(void) const;
    float getX(void) const;
    void setX(float value);
    float getY(void) const;
    void setY(float value);

  protected:
    std::string _type;
    float _x;
    float _y;
  };
}

#endif /* !GAMEOBJECT_HH_*/
