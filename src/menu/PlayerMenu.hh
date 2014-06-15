#ifndef PLAYERMENU_HH_
#define PLAYERMENU_HH_

# include "AMenuScene.hh"
# include "AWidget.hh"
# include "Cursor.hh"
# include "SoundManager.hh"

class PlayerMenu : public AMenuScene
{
public:
  PlayerMenu(SceneArguments const&);
  ~PlayerMenu();

  virtual bool initialize();
  virtual bool update(gdl::Clock const& clock, gdl::Input& input);
  virtual bool draw(gdl::AShader & shader, gdl::Clock const &clock);

  void backhandler(int);
  void nbiahandler(int);
  void nbplayerhandler(int);
  void continuehandler(int);

private:
  Cursor *_cursor;
  Cursor *_nb1;
  Cursor *_nb2;
  Cursor *_nb1s;
  Cursor *_nb2s;
  int _nbplayer = 1;

  bool _btnUp = false;
  bool _btnDown = false;
  bool _btnSpace = false;

  static SoundManager& _son;

};

#endif
