/*
** APlayer.hh for Bomberman in /home/raphy/Epitech/Tech_2/bomberman/src/object
**
** Made by raphael defreitas
** Login   <defrei_r@epitech.net>
**
** Started on  Sun Jun 15 00:35:59 2014 raphael defreitas
// Last update Sun Jun 15 01:37:25 2014 raphael defreitas
*/

#ifndef		APLAYER_HH_
# define	APLAYER_HH_

# include	<string>

# include	"AModel.hh"

class APlayer : public AModel
{
public:
  virtual ~APlayer() {};

  int getBombRange() const { return this->_bomb_range; }
  void setBombRange(int value) { this->_bomb_range = value; }

  int getBombCapacity() const { return this->_bomb_capacity; }
  void setBombCapacity(int value) { this->_bomb_capacity = value; }
  
  virtual bool initAnim() = 0;
  virtual bool initialize();

  void putBomb();
  
  virtual Rectangle getCollider() const;

protected:
    APlayer(std::string const& modelPath, std::string const& id) :
    AModel(modelPath, id), _bomb_range(2), _bomb_capacity(1) {};
    
    virtual void onUpPressed(gdl::Clock const& clock);
    virtual void onDownPressed(gdl::Clock const& clock);
    virtual void onLeftPressed(gdl::Clock const& clock);
    virtual void onRightPressed(gdl::Clock const& clock);
    
    virtual void run();
    virtual void stop();

    int _bomb_range;
    int _bomb_capacity;
};

#endif /* !APLAYER_HH_*/
