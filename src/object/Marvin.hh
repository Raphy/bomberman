#ifndef MARVIN_HH_
# define MARVIN_HH_

# include  <map>

# include  "APlayer.hh"
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


class Marvin: public APlayer
{
public:

    Marvin(int nbr = 1);
    virtual ~Marvin() {}
    
    virtual bool initAnim();
    virtual void update(gdl::Clock const& clock, gdl::Input& input);

    virtual void setBindKeys(inputBinding const& bind = {SDLK_UP, SDLK_DOWN, SDLK_LEFT, SDLK_RIGHT, SDLK_RCTRL});
    
private:
    State   _state;
    std::vector<inputStructure> _inputs;
    int totalPressed = 0;
    
    void run(gdl::Clock const&);
    void stop(gdl::Clock const&);

    virtual void run();
    virtual void stop();

    void none(gdl::Clock const &clock);
    void onBombPressed(gdl::Clock const& clock);
};

#endif // !MARVIN_HH_
