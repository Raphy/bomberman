#ifndef PAUSEMENU_HH_
# define PAUSEMENU_HH_

# include "AMenuScene.hh"
# include "AWidget.hh"
# include "Cursor.hh"
# include "SoundManager.hh"
# include "PlaylistManager.hh"
# include "GameAPI.hh"

class PauseMenu : public AMenuScene
{
public:
  PauseMenu(SceneArguments const&);
  ~PauseMenu();

  virtual bool initialize();
  virtual bool update(gdl::Clock const& clock, gdl::Input& input);
  virtual bool draw(gdl::AShader & shader, gdl::Clock const &clock);


  void resumehandler(int);
  void savehandler(int);
  void optionhandler(int);
  void exitmenuhandler(int);

private:
  SceneArguments& _arg;
  Cursor *_cursor;
  Cursor *_save;

  bool _isSave = false;
  bool _btnUp = false;
  bool _btnDown = false;
  bool _btnSpace = false;

  static SoundManager& _son;


};

#endif
