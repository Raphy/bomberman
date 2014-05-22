#ifndef     GAMESCENE_HH_
# define    GAMESCENE_HH_

# include   "AScene.hh"
# include   "AGameObject.hh"
# include   "SceneArgument.hh"
# include   <list>

/*
** Should need these arguments:
** Player= 1 | 2
*/

class       GameScene : public AScene
{
public:
  GameScene(SceneArgument const & args);
  virtual ~GameScene(void);

private:
  std::list<AGameObject*>   _static;
  std::list<AGameObject*>   _movable;

  virtual bool              initialize(void);
  virtual bool              update(void);
  virtual bool              draw(void);

};

#endif