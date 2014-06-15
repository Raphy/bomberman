#ifndef SCOREMENU_HH_
# define SCOREMENU_HH_

# include "AMenuScene.hh"
# include "Scoring.hh"
# include "NumericChars.hh"
# include "Cursor.hh"

class ScoreMenu : public AMenuScene
{
public:
  ScoreMenu(SceneArguments const&);
  ~ScoreMenu();

  virtual bool initialize();
  virtual bool update(gdl::Clock const& clock, gdl::Input& input);
  virtual bool draw(gdl::AShader & shader, gdl::Clock const &clock);


private:
  SceneArguments& _args;
  static Scoring& _scoring;
  static NumericChars& _num;
  Cursor *p1;
  Cursor *p2;

  std::list<unsigned int> _scorp1;
  std::list<unsigned int> _scorp2;

  std::list<Cursor*> _sc1;
  std::list<Cursor*> _sc2;

};

#endif
