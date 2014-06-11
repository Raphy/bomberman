#ifndef AWIDGET_HH_
# define AWIDGET_HH_

#include <string>
#include "AObject.hh"

class AWidget : public AObject
{
public:
  AWidget(const std::string& path, const glm::vec3& position, const glm::vec3& scale, int c);
  virtual ~AWidget();

  virtual bool initialize();
  virtual void update(gdl::Clock const& clock, gdl::Input& input);
  virtual void draw(gdl::AShader & shader, gdl::Clock const& clock);

  int getCur() const;
  glm::vec3 getPos() const;

protected:
  gdl::Texture _texture;
  gdl::Geometry _geometry;

  std::string _texturePath;
  glm::vec3 _scale;
  glm::vec3 _position;

  int _cur;

};

#endif
