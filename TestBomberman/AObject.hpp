#include <SdlContext.hh>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include <OpenGL.hh>
#include <Game.hh>
#include <Clock.hh>
#include <Input.hh>
#include <SdlContext.hh>
#include <Geometry.hh>
#include <Texture.hh>
#include <BasicShader.hh>
#include <Model.hh>

class AObject
{
public:
  AObject():
    _position(0,0,0),
    _rotation(0,0,0),
    _scale(1,1,1)
  {
  }

  virtual ~AObject()
  {}

  virtual bool initialize()
  {
    return (true);
  }

  virtual void update(gdl::Clock const&clock,gdl::Input&input)
  {
    (void) clock;
    (void) input;
  }

  virtual void
  draw
  (gdl::AShader &shader,gdl::Clock const&clock) = 0;

  void translate(glm::vec3 const&v)
  {
    _position+=v;
  }

  void rotate(glm::vec3 const&axis, float angle)
  {
    _rotation += axis * angle;
  }

  void lookAt(glm::vec3 const& point) {

    _rotation = point;

  }

  void scale(glm::vec3 const&scale)
  {
    _scale *= scale;
  }

  glm::mat4 getTransformation()
  {
    glm::mat4 transform(1);

    transform = glm::translate(transform,_position);


    transform = glm::rotate(transform, _rotation.x, glm::vec3(1,0,0));
    transform = glm::rotate(transform, _rotation.y, glm::vec3(0,1,0));
    transform = glm::rotate(transform, _rotation.z, glm::vec3(0,0,1));


    
    transform = glm::scale(transform,_scale);
    return(transform);
  }

protected:
  glm::vec3 _position;
  glm::vec3 _rotation;
  glm::vec3 _scale;
};
