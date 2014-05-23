#ifndef AGAME_OBJECT_HH
# define AGAME_OBJECT_HH

#include <string>

#include "AObject.hh"

// An object specialized for game.
class AGameObject : public AObject {

protected:
    // A type (string) used to dinstinguish
    // differents AGameObject (in onCollision() for example)
    std::string const m_type;
    // Indicate if the object is already in the game.
    bool m_dead;

    // Constructor called by childrens. Take the type as parameter
    // to force child to set it.  
    AGameObject(std::string const& type) : AObject(), m_type(type), m_dead(false) {}

    // Get the type of the object.
    std::string const& getType() const { return m_type; }
    // Used by children to set their m_dead attribute to true. 
    void die() { m_dead = true; }

public:
    // Is it dead ?
    bool isDead() const { return m_dead; }

    virtual ~AGameObject() {}
    // Called when collision occured with the other object as parameter.
    virtual void onCollision(AGameObject&) {}
    // A generic iteraction between objects (useful for IA)
    virtual void onMessage(std::string const&, AGameObject&) {}
    // Inflige damages to the game Object (prototype must be discuted).
    virtual void takeDamages() {}
};

#endif // !AGAME_OBJECT_HH