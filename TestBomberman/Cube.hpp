

class Cube : public AObject
{
private:
  gdl::Texture _texture;
  gdl::Geometry _geometry;
  float _speed;

public:
  Cube() {}
  virtual ~Cube() {}
  virtual bool initialize()
  {
    _speed = 10.0f;
    if (_texture.load("./LibBomberman_linux_x64/assets/textures/blank.tga")==false)
      {
	       std::cerr << "Cannot load the cube texture" << std::endl;
	       return (false);
      }

    _geometry.setColor(glm::vec4(1, 0, 0, 1));

    _geometry.pushVertex(glm::vec3(0.5, -0.5, 0.5));
    _geometry.pushVertex(glm::vec3(0.5, 0.5, 0.5));
    _geometry.pushVertex(glm::vec3(-0.5, 0.5, 0.5));
    _geometry.pushVertex(glm::vec3(-0.5, -0.5, 0.5));

    _geometry.pushUv(glm::vec2(0.0f, 0.0f));
    _geometry.pushUv(glm::vec2(1.0f, 0.0f));
    _geometry.pushUv(glm::vec2(1.0f, 1.0f));
    _geometry.pushUv(glm::vec2(0.0f, 1.0f));

    _geometry.setColor(glm::vec4(1, 1, 1, 1));
    _geometry.pushVertex(glm::vec3(0.5, -0.5, -0.5));
    _geometry.pushVertex(glm::vec3(0.5, 0.5, -0.5));
    _geometry.pushVertex(glm::vec3(-0.5, 0.5, -0.5));
    _geometry.pushVertex(glm::vec3(-0.5, -0.5, -0.5));
    _geometry.pushUv(glm::vec2(0.0f, 0.0f));
    _geometry.pushUv(glm::vec2(1.0f, 0.0f));
    _geometry.pushUv(glm::vec2(1.0f, 1.0f));
    _geometry.pushUv(glm::vec2(0.0f, 1.0f));
    _geometry.setColor(glm::vec4(0, 1, 1, 1));
    _geometry.pushVertex(glm::vec3(0.5, -0.5, -0.5));
    _geometry.pushVertex(glm::vec3(0.5, 0.5, -0.5));
    _geometry.pushVertex(glm::vec3(0.5, 0.5, 0.5));
    _geometry.pushVertex(glm::vec3(0.5, -0.5, 0.5));
    _geometry.pushUv(glm::vec2(0.0f, 0.0f));
    _geometry.pushUv(glm::vec2(1.0f, 0.0f));
    _geometry.pushUv(glm::vec2(1.0f, 1.0f));
    _geometry.pushUv(glm::vec2(0.0f, 1.0f));
    _geometry.setColor(glm::vec4(1, 0, 1, 1));
    _geometry.pushVertex(glm::vec3(-0.5, -0.5, 0.5));
    _geometry.pushVertex(glm::vec3(-0.5, 0.5, 0.5));
    _geometry.pushVertex(glm::vec3(-0.5, 0.5, -0.5));
    _geometry.pushVertex(glm::vec3(-0.5, -0.5, -0.5));
    _geometry.pushUv(glm::vec2(0.0f, 0.0f));
    _geometry.pushUv(glm::vec2(1.0f, 0.0f));
    _geometry.pushUv(glm::vec2(1.0f, 1.0f));
    _geometry.pushUv(glm::vec2(0.0f, 1.0f));
    _geometry.setColor(glm::vec4(0, 1, 0, 1));
    _geometry.pushVertex(glm::vec3(0.5, 0.5, 0.5));
    _geometry.pushVertex(glm::vec3(0.5, 0.5, -0.5));
    _geometry.pushVertex(glm::vec3(-0.5, 0.5, -0.5));
    _geometry.pushVertex(glm::vec3(-0.5, 0.5, 0.5));
    _geometry.pushUv(glm::vec2(0.0f, 0.0f));
    _geometry.pushUv(glm::vec2(1.0f, 0.0f));
    _geometry.pushUv(glm::vec2(1.0f, 1.0f));
    _geometry.pushUv(glm::vec2(0.0f, 1.0f));
    _geometry.setColor(glm::vec4(0, 0, 1, 1));
    _geometry.pushVertex(glm::vec3(0.5, -0.5, -0.5));
    _geometry.pushVertex(glm::vec3(0.5, -0.5, 0.5));
    _geometry.pushVertex(glm::vec3(-0.5, -0.5, 0.5));
    _geometry.pushVertex(glm::vec3(-0.5, -0.5, -0.5));
    _geometry.pushUv(glm::vec2(0.0f, 0.0f));
    _geometry.pushUv(glm::vec2(1.0f, 0.0f));
    _geometry.pushUv(glm::vec2(1.0f, 1.0f));
    _geometry.pushUv(glm::vec2(0.0f, 1.0f));

    _geometry.build();
    return (true);
  }


  virtual void update(gdl::Clock const &clock, gdl::Input &input)
  {
    if (input.getKey(SDLK_UP))
      translate(glm::vec3(0, 0, 1) * static_cast<float>(clock.getElapsed()) * _speed);
    if (input.getKey(SDLK_DOWN))
      translate(glm::vec3(0, 0, -1) * static_cast<float>(clock.getElapsed()) * _speed);
    if (input.getKey(SDLK_LEFT))
      translate(glm::vec3(-1, 0, 0) * static_cast<float>(clock.getElapsed()) * _speed);
    if (input.getKey(SDLK_RIGHT))
      translate(glm::vec3(1, 0, 0) * static_cast<float>(clock.getElapsed()) * _speed);
  }

  virtual void draw(gdl::AShader &shader, gdl::Clock const &clock)
  {
    (void)clock;
    _texture.bind();
    _geometry.draw(shader, getTransformation(), GL_QUADS);
  }
};
