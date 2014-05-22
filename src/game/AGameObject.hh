

#ifndef AGAME_OBJECT_HH
# define AGAME_OBJECT_HH

#include <string>

#include "AObject.hh"

class AGameObject : public AObject {

protected:
    std::string const m_type;

    AGameObject(std::string const& type) : AObject(), m_type(type) {}
    std::string const& getType() const { return m_type; }

public:
    virtual ~AGameObject() {}
    virtual void onCollision(AGameObject&) {}
    virtual void onMessage(std::string const&, AGameObject&) {}
    virtual void takeDamages() {}
};

#endif // !AGAME_OBJECT_HH