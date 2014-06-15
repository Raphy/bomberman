/* 
 * File:   AIA.hh
 * Author: svirch_n
 *
 * Created on 12 June 2014, 14:37
 */

#ifndef IA_HH
#define	IA_HH

# include   "APlayer.hh"
# include   "Lua/Script.hh"
# include   "ResourcesPath.hh"

class IA: public APlayer {

public:

    enum Going {
        Up = 0,
        Left = 1,
        Down = 2,
        Right = 3,
        None = 4
    };
    
    IA();
    virtual ~IA();

    virtual bool initialize();
    
    virtual void update(const gdl::Clock& clock, gdl::Input& input);
    
    void goOneCaseDown();
    void goOneCaseUp();
    void goOneCaseLeft();
    void goOneCaseRight();


    virtual void onCollision(AGameObject&);

    virtual Rectangle getCollider() const;

    
private:
    
    glm::vec3   _from;
    int         _to;
    Going       _direction;
    
    // removable
    bool        pressed;
    Lua::Script* _script;
    
    void onUpPressed(gdl::Clock const &clock);
    void onDownPressed(gdl::Clock const &clock);
    void onLeftPressed(gdl::Clock const &clock);
    void onRightPressed(gdl::Clock const &clock);
};

#endif	/* IA_HH */

