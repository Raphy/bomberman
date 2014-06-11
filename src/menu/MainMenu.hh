#ifndef MAINMENU_HH_
#define MAINMENU_HH_

# include "AMenuScene.hh"
# include "AWidget.hh"
# include "Cursor.hh"

class MainMenu : public AMenuScene
{
public:
  MainMenu(SceneArguments const&);
  ~MainMenu();

  virtual bool initialize();
  virtual bool update(gdl::Clock const& clock, gdl::Input& input);
  virtual bool draw(gdl::AShader & shader, gdl::Clock const &clock);

  /* definir le handler de chaque boutton*/
  void playhandler();
  void optionhandler();
  void exithandler();
  void loadhandler();

private:
  Cursor *_cursor;

  bool _btnUp = false;
  bool _btnDown = false;
  bool _btnSpace = false;

};

#endif
