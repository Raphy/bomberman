#ifndef MARVIN_HH_
# define MARVIN_HH_

# include  <map>

# include  "AModel.hh"
# include  "ResourcesPath.hh"

class Marvin;
typedef void (Marvin::*inputFunction)(gdl::Clock const&);

struct inputStructure {
    int value;
    bool isPressed;
    inputFunction function;
    inputFunction functionPressed;
    inputFunction functionReleased;
};

struct inputBinding {
    int up;
    int down;
    int left;
    int right;
    int bomb;
};


class Marvin: public AModel
{
public:

    Marvin() : AModel(ResourcesPath::asset("minion/minion.obj"), "marvin"), totalPressed(0) {}
    virtual ~Marvin() {}
    
    virtual bool initialize();
    virtual void update(gdl::Clock const& clock, gdl::Input& input);

    virtual void onCollision(AGameObject&);
    virtual Rectangle getCollider() const;
    virtual void setBindKeys(inputBinding const& bind = {SDLK_UP, SDLK_DOWN, SDLK_LEFT, SDLK_RIGHT, SDLK_RCTRL});
    
    static std::string const Tag;
    
private:
    State   _state;
    std::vector<inputStructure> _inputs;
    int totalPressed = 0;
    
    void run(gdl::Clock const&);
    void stop(gdl::Clock const&);
    void none(gdl::Clock const &clock);
    void onUpPressed(gdl::Clock const& clock);
    void onDownPressed(gdl::Clock const& clock);
    void onLeftPressed(gdl::Clock const& clock);
    void onRightPressed(gdl::Clock const& clock);
    void onBombPressed(gdl::Clock const& clock);
};

#endif // !MARVIN_HH_
