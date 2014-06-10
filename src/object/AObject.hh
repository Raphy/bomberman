
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

# include "Rectangle.hh"

class AObject
{
public:
    
    AObject():
        _position(0, 0, 0),
        _rotation(0, 0, 0),
        _scale(1, 1, 1),
        _static(false)
    {}

    virtual ~AObject() {}

    virtual bool instanciatedObjects() const { return false; }
    
    // Need to remove the objects from the vector
    virtual std::vector<AObject*> &getInstanciatedObjects() { return this->_objects; }
    
    virtual bool initialize() = 0;
    virtual void update(gdl::Clock const& clock, gdl::Input& input) = 0;
    virtual void draw(gdl::AShader & shader, gdl::Clock const& clock) = 0;
    
    Rectangle getCollider() const { return Rectangle(_position, _scale); }

    void setPosition(glm::vec3 position);
    glm::vec3 const& getPosition() const { return this->_position; }
    
    void setSpeed(float speed) { this->_speed = speed; }
    
    // Optimisation if the object doesn't move
    // Performance loss if used on movement object
    void isStatic(bool value = true) { this->_static = value; }
    
protected:
    
    //Instantiated object list
    std::vector<AObject*> _objects;
    
    glm::vec3 _position;
    glm::vec3 _rotation;
    glm::vec3 _scale;
    glm::mat4 _transformation;
    float _speed;

    bool _static;
    
    // object modifications
    void lookNorth();
    void lookSouth();
    void lookWest();
    void lookEast();
    void translate(glm::vec3 const &v);
    void rotate(glm::vec3 const &axis, float angle);
    void lookAt(glm::vec3 const &point);
    void scale(glm::vec3 const &scale);

    void checkStaticObject();
    glm::mat4 getTransformation();
    glm::mat4 getForceTransformation();
};

#endif // !AOBJECT_HH_
