#ifndef  AGAMEOBJECT_HH_
# define AGAMEOBJECT_HH_

# include "AObject.hh"

class AGameObject: public AObject
{
public:
    
    struct State {
        glm::vec3 position;
        glm::vec3 rotation;
        glm::vec3 scale;
    };
    
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

    virtual bool instanciatedObjects() { return !this->_objects.empty(); }
    
    // Need to remove the objects from the vector
    virtual std::vector<AGameObject*> &getInstanciatedObjects() { return this->_objects; }
    
    std::tuple<double, double> getPosition() const {
        return std::make_tuple(_position.x, _position.z);
    }

    // Returns the objects and clean the list
    template<class OutputIterator>
    OutputIterator getObjectsAndReset(OutputIterator out_it) {
        auto in_it = _objects.begin();
        while (in_it != _objects.end()) {
            *(out_it++) = *(in_it++);
        }
        _objects.clear();
        return out_it;
    }
    
    virtual Rectangle getCollider() const;

protected:
    
    //Instantiated object list
    std::vector<AGameObject*> _objects;
    
    // A type (string) used to dinstinguish
    // differents AGameObject (in onCollision() for example)
    std::string const m_type;
    // Indicate if the object is already in the game.
    bool m_dead;
    
    State _state;

    // Constructor called by childrens. Take the type as parameter
    // to force child to set it.  
    AGameObject(std::string const& type) : AObject(), m_type(type), m_dead(false) {}

    virtual void restoreLastState(AGameObject const&);
    void saveCurrentState();

    void addObject(AGameObject *);

    // Used by children to set their m_dead attribute to true. 
    void die() { m_dead = true; }
};

#endif   /* AGAMEOBJECT_HH_*/
