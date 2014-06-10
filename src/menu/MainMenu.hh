#ifndef MAINMENU_HH_
#define MAINMENU_HH_

# include "AMenuScene.hh"


class MainMenu : public AMenuScene
{
public:
  MainMenu(SceneArguments const&);
  ~MainMenu();

  virtual bool initialize();
  virtual bool update(gdl::Clock const& clock, gdl::Input& input);
  virtual bool draw(gdl::AShader & shader, gdl::Clock const &clock);

private:

};

#endif
