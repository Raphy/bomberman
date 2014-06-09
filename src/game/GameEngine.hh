
#ifndef GAME_ENGINE_HH_
# define GAME_ENGINE_HH_

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

# include "ScenesManager.hh"

# include "MenuScene.hh"
# include "GameScene.hh"

class GameEngine : public gdl::Game {

private:
    // Define the first scene to be loaded.
    typedef GameScene FirstScene;

    // GDL
    gdl::SdlContext        m_context;
    gdl::Clock             m_clock;
    gdl::Input             m_input;
    gdl::BasicShader       m_shader;

    // other
    ScenesManager m_scenes_manager;

public:
    GameEngine();
    ~GameEngine();
    bool initialize();
    bool update();
    void draw();
};

#endif // !GAME_ENGINE_HH_
