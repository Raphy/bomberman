# include "Cursor.hh"

Cursor::Cursor(const std::string& path, const glm::vec3& position, const glm::vec3& scale)
{
  _texturePath = path;
  _position = position;
  _position.x += -30;
  _scale = scale;
}

Cursor::~Cursor()
{

}

bool Cursor::initialize()
{
  if (_texture.load(_texturePath) == false)
    {
      std::cerr << "Cannot load the widget texture" << std::endl;
      return false;
    }

  _geometry.setColor(glm::vec4(1, 1, 1, 1));

  _geometry.pushVertex(glm::vec3(0, 0, 0));
  _geometry.pushVertex(glm::vec3(1, 0, 0));
  _geometry.pushVertex(glm::vec3(1, 1, 0));
  _geometry.pushVertex(glm::vec3(0, 1, 0));

  _geometry.pushUv(glm::vec2(0.0f, 1.0f));
  _geometry.pushUv(glm::vec2(1.0f, 1.0f));
  _geometry.pushUv(glm::vec2(1.0f, 0.0f));
  _geometry.pushUv(glm::vec2(0.0f, 0.0f));

  _geometry.build();

  return true;
}

void Cursor::update(gdl::Clock const& clock, gdl::Input& input)
{

}

void Cursor::draw(gdl::AShader & shader, gdl::Clock const& clock)
{
  (void)clock;

  glm::mat4 transform(1);

  transform = glm::translate(transform, _position);
  transform = glm::scale(transform, _scale);

  _texture.bind();

  _geometry.draw(shader, transform, GL_QUADS);
}

void Cursor::setPosY(const glm::vec3& position)
{
  _position.y = position.y;
}

void Cursor::setPosX(const glm::vec3& position)
{
  _position.x = position.x;
}

glm::vec3 Cursor::getPosition() const
{
  return _position;
}
