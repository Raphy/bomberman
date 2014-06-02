#ifndef  AGAMEOBJECT_HH_
# define AGAMEOBJECT_HH_

# include "AObject.hh"

class AGameObject: public AObject
{
public:
 
 AGameObject(): _speed(10) {}
 virtual ~AGameObject() {}

 virtual void takeDamages() {}
 virtual void onCollision(AGameObject & obj) { (void) obj; }
 virtual void onMessage(AGameObject & obj, std::string const& message) { (void) obj; (void) message; }

protected:
 float _speed;
 
};

#endif   /* AGAMEOBJECT_HH_*/