#ifndef LOADINGMENU_HH_
# define LOADINGMENU_HH_

# include "AMenuScene.hh"

class LoadingMenu : public AMenuScene
{
public:
  LoadingMenu(SceneArguments const&);
  ~LoadingMenu();

  virtual bool initialize();
  virtual bool update(gdl::Clock const& clock, gdl::Input& input);
  virtual bool draw(gdl::AShader & shader, gdl::Clock const &clock);
private:
  SceneArguments& _args;

};

#endif
