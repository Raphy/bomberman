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
	
	AObject(): _position(0,0,0), _rotation(0,0,0), _scale(1,1,1) {}
	virtual ~AObject() {}

	virtual bool initialize();
	virtual void update(gdl::Clock const& clock, gdl::Input& input);
	virtual void draw(gdl::AShader & shader, gdl::Clock const& clock);

protected:

	glm::vec3 _position;
	glm::vec3 _rotation;
	glm::vec3 _scale;

	void translate(glm::vec3 const& v) { _position += v; }
	void rotate(glm::vec3 const& axis, float angle) { _rotation += axis * angle; }
	void lookAt(glm::vec3 const& point) { _rotation = point; }
	void scale(glm::vec3 const& scale) { _scale *= scale; }
	glm::mat4 getTransformation();

};