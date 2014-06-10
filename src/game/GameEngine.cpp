
#include "GameEngine.hh"
#include "GameScene.hh"
#include    "Basic.hh"

GameEngine::GameEngine():
    m_scenes_manager()
{
}

GameEngine::~GameEngine()
{
}

bool GameEngine::initialize()
{
    if (!m_context.start(800, 600, "My bomberman!")) {
        return false;
    }

    glEnable(GL_DEPTH_TEST);

    if (!m_shader.load("./build/shaders/basic.fp", GL_FRAGMENT_SHADER) ||!m_shader.load("./build/shaders/basic.vp", GL_VERTEX_SHADER) ||!m_shader.build()) {
        return false;
    }

    
    this->_position = glm::vec3(0, 15, -20);
    this->_lookAtPosition = glm::vec3(0, 0, 0);
    
//    m_shader.bind();
//    m_shader.setUniform("view", glm::lookAt(this->_position, this->_lookAtPosition, glm::vec3(0, 1, 0)));
//    m_shader.setUniform("projection", glm::perspective(60.0f, 800.0f / 600.0f, 0.1f, 10000.0f));

    /*
     * SceneArguments scene_args;
     * m_scenes_manager.start<MenuScene>(scene_args);
     */
    _scene = new Basic();

    _scene -> initialize();

    return true;
}

bool GameEngine::update()
{
    if (m_input.getInput(SDL_QUIT)) {
        return false;
    }

    m_context.updateClock(m_clock);
    m_context.updateInputs(m_input);
    _scene -> update(m_clock, m_input);

    /*
     * try {
     *   IScene& scene = m_scenes_manager.getCurrentScene();
     *   scene.update(m_clock, m_input);
     *   if (!m_scenes_manager.applyChanges()) {
     *       // throw an exception
     *       return false;
     *   }
     *
     * }
     * catch (std::string& err) {
     *   return false;
     * }
     */
    return true;
}

void GameEngine::draw()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    m_shader.bind();
    _scene -> metaDraw(m_shader, m_clock);
    m_context.flush();
}


//~ Formatted by Jindent --- http://www.jindent.com
