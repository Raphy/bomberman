#ifndef WINMENU_HH_
# define WINMENU_HH_

# include "AMenuScene.hh"

class WinMenu : public AMenuScene
{
public:
  WinMenu(SceneArguments const&);
  ~WinMenu();

  virtual bool initialize();
  virtual bool update(gdl::Clock const& clock, gdl::Input& input);
  virtual bool draw(gdl::AShader & shader, gdl::Clock const &clock);

private:
  double _time;
  SceneArguments& _arg;

};

#endif
