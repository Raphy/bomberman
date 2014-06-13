#ifndef OPTIONMENU_HH_
#define OPTIONMENU_HH_

#include "AMenuScene.hh"
#include "Cursor.hh"
#include "SoundManager.hh"

class OptionMenu : public AMenuScene
{
public:
  OptionMenu(SceneArguments const&);
  ~OptionMenu();

  virtual bool initialize();
  virtual bool update(gdl::Clock const& clock, gdl::Input& input);
  virtual bool draw(gdl::AShader & shader, gdl::Clock const &clock);

  void soundfxhandler(int);
  void soundmusichandler(int);
  void backhandler(int);

private:
  Cursor *_cursor;
  Cursor *_cursorbsonfx;
  Cursor *_cursorbsonmusic;

  Cursor *_cursorFx;
  Cursor *_cursorMusic;

  bool _btnUp = false;
  bool _btnDown = false;
  bool _btnSpace = false;

  static SoundManager& _son;

};

#endif
