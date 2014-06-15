#ifndef MAPMENU_HH_
#define MAPMENU_HH_

# include "AMenuScene.hh"
# include "AWidget.hh"
# include "Cursor.hh"
# include "SoundManager.hh"

class MapMenu : public AMenuScene
{
public:
  MapMenu(SceneArguments const&);
  ~MapMenu();

  virtual bool initialize();
  virtual bool update(gdl::Clock const& clock, gdl::Input& input);
  virtual bool draw(gdl::AShader & shader, gdl::Clock const &clock);

  void map1handler(int);
  void map2handler(int);
  void maprandomhandler(int);
  void backhandler(int);

private:
  SceneArguments& _arg;
  Cursor *_cursor;

  bool _btnUp = false;
  bool _btnDown = false;
  bool _btnSpace = true;

  static SoundManager& _son;

};

#endif
