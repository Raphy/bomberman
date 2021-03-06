#ifndef MAINMENU_HH_
# define MAINMENU_HH_

# include "AMenuScene.hh"
# include "AWidget.hh"
# include "Cursor.hh"
# include "SoundManager.hh"
# include "PlaylistManager.hh"
# include "ScoreMenu.hh"

class MainMenu : public AMenuScene
{
public:
  MainMenu(SceneArguments const&);
  ~MainMenu();

  virtual bool initialize();
  virtual bool update(gdl::Clock const& clock, gdl::Input& input);
  virtual bool draw(gdl::AShader & shader, gdl::Clock const &clock);

  void playhandler(int);
  void optionhandler(int);
  void exithandler(int);
  void loadhandler(int);
  void scorehandler(int);
  void initPlaylist();

private:
  PlaylistManager _playlist;
  SceneArguments& _arg;
  Cursor *_cursor;

  bool _btnUp = false;
  bool _btnDown = false;
  bool _btnSpace = false;

  static SoundManager& _son;



};

#endif
