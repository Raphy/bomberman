#ifndef CURSOR_HH_
# define CURSOR_HH_

#include <string>
#include "AObject.hh"

class Cursor : public AObject
{
public:
  Cursor(const std::string& path, const glm::vec3& position, const glm::vec3& scale);
  virtual ~Cursor();

  virtual bool initialize();
  virtual void update(gdl::Clock const& clock, gdl::Input& input);
  virtual void draw(gdl::AShader& shader, gdl::Clock const& clock);

  void setPosY(const glm::vec3&);
  void setPosX(const glm::vec3&);

  glm::vec3 getPosition() const;
  glm::vec3 getScale() const;
  void setScale(const glm::vec3&);

protected:
  std::string _texturePath;
  glm::vec3 _position;
  glm::vec3 _scale;

  gdl::Texture _texture;
  gdl::Geometry _geometry;

};

#endif
