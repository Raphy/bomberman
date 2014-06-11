#ifndef MAPMENU_HH_
#define MAPMENU_HH_

# include "AMenuScene.hh"
# include "AWidget.hh"
# include "Cursor.hh"


class MapMenu : public AMenuScene
{
public:
  MapMenu(SceneArguments const&);
  ~MapMenu();

  virtual bool initialize();
  virtual bool update(gdl::Clock const& clock, gdl::Input& input);
  virtual bool draw(gdl::AShader & shader, gdl::Clock const &clock);

  /* definir le handler de chaque boutton*/
  void map1handler();
  void map2handler();
  void maprandomhandler();
  void backhandler();

private:
  Cursor *_cursor;

  bool _btnUp = false;
  bool _btnDown = false;
  bool _btnSpace = false;

};

#endif
