// This is the minimal code for a scene

#include "AScene.hh"
#include "SceneArguments.hh"

class ExampleScene : public AScene {

private:
    // Like you want ...
public:
    // A tag which is used to identify the scene. (not necessary but better) 
    static const std::string Tag; 

    // SceneArguments is an hash map key => value (see SceneArguments.hh)
    ExampleScene(SceneArguments const& args);
    virtual ~ExampleScene();

    virtual bool initialize();
    virtual bool update(gdl::Clock const& clock, gdl::Input& input);
    virtual bool draw(gdl::AShader & shader, gdl::Clock const &clock);
};