#ifndef SCOREMENU_HH_
# define SCOREMENU_HH_

# include "AMenuScene.hh"

class ScoreMenu : public AMenuScene
{
public:
  ScoreMenu(SceneArguments const&);
  ~ScoreMenu();

  virtual bool initialize();
  virtual bool update(gdl::Clock const& clock, gdl::Input& input);
  virtual bool draw(gdl::AShader & shader, gdl::Clock const &clock);

private:
  SceneArguments& _args;

};

#endif
