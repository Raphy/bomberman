#ifndef AMENUSCENE_HH_
# define AMENUSCENE_HH_

# include "AScene.hh"
# include "SceneArguments.hh"
# include "AWidget.hh"
# include "Button.hh"

#include <vector>
#include <string>

class AMenuScene : public AScene
{
public:
  AMenuScene(const std::string& tag);
  virtual ~AMenuScene();

  virtual bool initialize();
  virtual bool update(gdl::Clock const& clock, gdl::Input& input);
  virtual bool draw(gdl::AShader & shader, gdl::Clock const &clock);

  void setTexture(const std::string& path);

protected:
  gdl::Texture _texture;
  gdl::Geometry _geometry;

  /* for the camera */
  glm::mat4 _projection;
  glm::mat4 _transformation;
  std::string _pathTexture;

  /*
    typedef void (MenuScene::*ButtonHandler)();
    std::map<AWidget*, ButtonHandler> _mapButton;
  */
};

#endif
