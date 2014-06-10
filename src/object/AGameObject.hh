#ifndef  AGAMEOBJECT_HH_
# define AGAMEOBJECT_HH_

# include "AObject.hh"

class AGameObject: public AObject
{
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
    // Get the type of the object.
    std::string const& getType() const { return m_type; }

    std::tuple<double, double> getPosition() const {
        return std::make_tuple(_position.x, _position.z);
    }


protected:
    // A type (string) used to dinstinguish
    // differents AGameObject (in onCollision() for example)
    std::string const m_type;
    // Indicate if the object is already in the game.
    bool m_dead;

    // Constructor called by childrens. Take the type as parameter
    // to force child to set it.  
    AGameObject(std::string const& type) : AObject(), m_type(type), m_dead(false) {}

    // Used by children to set their m_dead attribute to true. 
    void die() { m_dead = true; }
};

#endif   /* AGAMEOBJECT_HH_*/
