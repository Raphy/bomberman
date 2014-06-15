#ifndef AMENUSCENE_HH_
# define AMENUSCENE_HH_

# include <string>
# include <map>

# include "AScene.hh"
# include "SceneArguments.hh"
# include "AWidget.hh"
# include "Camera.hh"
# include "ResourcesPath.hh"

class AMenuScene : public AScene
{
protected:
  float _windowX;
  float _windowY;

  gdl::Texture _texture;
  gdl::Geometry _geometry;

  Camera *_camera;

  glm::mat4 _projection;

  std::string _pathTexture;

  typedef void (AMenuScene::*ButtonHandler)(int);
  std::map<AWidget*, ButtonHandler> _mapButton;

  int _cursorPos;

public:
  AMenuScene(const std::string& tag);
  virtual ~AMenuScene();

  virtual bool initialize();
  virtual bool update(gdl::Clock const& clock, gdl::Input& input);
  virtual bool draw(gdl::AShader& shader, gdl::Clock const &clock);

  void setTexture(const std::string& path);

  void addButton(const std::string& path,  const glm::vec3& pos, const glm::vec3& scale, const ButtonHandler& fct, int c);

  float getWindowX() const;
  float getWindowY() const;

  float getXPercent(float) const;
  float getYPercent(float) const;

};

#endif
