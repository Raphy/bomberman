#ifndef LOSEMENU_HH_
# define LOSEMENU_HH_

# include "AMenuScene.hh"

class LoseMenu : public AMenuScene
{
public:
  LoseMenu(SceneArguments const&);
  ~LoseMenu();

  virtual bool initialize();
  virtual bool update(gdl::Clock const& clock, gdl::Input& input);
  virtual bool draw(gdl::AShader & shader, gdl::Clock const &clock);

private:
  double _time;

};

#endif
