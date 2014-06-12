#ifndef OPTIONMENU_HH_
#define OPTIONMENU_HH_

#include "AMenuScene.hh"
#include "Cursor.hh"

class OptionMenu : public AMenuScene
{
public:
  OptionMenu(SceneArguments const&);
  ~OptionMenu();

  virtual bool initialize();
  virtual bool update(gdl::Clock const& clock, gdl::Input& input);
  virtual bool draw(gdl::AShader & shader, gdl::Clock const &clock);

  /* definir le handler de chaque boutton*/
  void soundfxhandler(int);
  void soundmusichandler(int);
  void backhandler(int);

private:
  Cursor *_cursor;

  Cursor *_cursorFx;
  Cursor *_cursorMusic;

  bool _btnUp = false;
  bool _btnDown = false;
  bool _btnSpace = false;

};

#endif
