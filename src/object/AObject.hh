
#ifndef AOBJECT_HH_
# define AOBJECT_HH_

# include <SdlContext.hh>
# include <glm/glm.hpp>
# include <glm/gtc/matrix_transform.hpp>
# include <iostream>
# include <OpenGL.hh>
# include <Game.hh>
# include <Clock.hh>
# include <Input.hh>
# include <SdlContext.hh>
# include <Geometry.hh>
# include <Texture.hh>
# include <BasicShader.hh>
# include <Model.hh>

# include <tuple>

# include "Rectangle.hh"

class AObject
{
public:
    
    AObject():
        _position(0, 0, 0),
        _rotation(0, 0, 0),
        _scale(1, 1, 1)
    {
    }

    virtual ~AObject() {}

    virtual bool instanciatedObjects() const { return false; }
    
    // Need to remove the objects from the vector
    virtual std::vector<AObject*> &getInstanciatedObjects() { return this->_objects; }
    
    virtual bool initialize() = 0;
    virtual void update(gdl::Clock const& clock, gdl::Input& input) = 0;
    virtual void draw(gdl::AShader & shader, gdl::Clock const& clock) = 0;
    
    Rectangle getCollider() const { return Rectangle(_position, _scale); }

    void setPosition(glm::vec3 position) { _position = position; }
    void setPosition(double x, double y) { _position = glm::vec3(x, y, 0); }
    void setSpeed(float speed) { this->_speed = speed; }
    
    std::tuple<double, double> getPosition() const {
        return std::make_tuple(_position.x, _position.y);
    }

protected:
    std::vector<AObject*> _objects;
    glm::vec3 _position;
    glm::vec3 _rotation;
    glm::vec3 _scale;
    float _speed;
    
    void lookNorth() { this -> lookAt(glm::vec3(0, 0, 0)); }
    void lookSouth() { this -> lookAt(glm::vec3(0, 180, 0)); }
    void lookWest() { this -> lookAt(glm::vec3(0, 90, 0)); }
    void lookEast() { this -> lookAt(glm::vec3(0, -90, 0));}
    void translate(glm::vec3 const &v) { _position += v; }
    void rotate(glm::vec3 const &axis, float angle) { _rotation += axis * angle; }
    void lookAt(glm::vec3 const &point) { _rotation = point; }
    void scale(glm::vec3 const &scale) { _scale *= scale; }

    glm::mat4 getTransformation();
};

#endif // !AOBJECT_HH_
