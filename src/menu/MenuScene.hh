#ifndef MENUSCENE_HH_
# define MENUSCENE_HH_

# include "AScene.hh"
# include "SceneArguments.hh"
# include "AWidget.hh"

#include <vector>

class MenuScene : public AScene
{
public:
  static const std::string Tag;

  MenuScene(SceneArguments const& args);
  virtual ~MenuScene();

  virtual bool initialize();
  virtual bool update(gdl::Clock const& clock, gdl::Input& input);
  virtual bool draw(gdl::AShader & shader, gdl::Clock const &clock);

private:
  gdl::Texture _texture;
  gdl::Geometry _geometry;

  /* for the camera */
  glm::mat4 _projection;
  glm::mat4 _transformation;

  std::vector<AWidget*> _listButton;

};

#endif
