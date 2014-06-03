#include "GameEngine.hh"

#include "GameScene.hh"

GameEngine::GameEngine() : m_scenes_manager() {
}

GameEngine::~GameEngine() {
}

bool GameEngine::initialize() {
    if (!m_context.start(800, 600, "My bomberman!")) {
        return false;
    }

    glEnable(GL_DEPTH_TEST);

    if (!m_shader.load("./build/shaders/basic.fp", GL_FRAGMENT_SHADER) ||
        !m_shader.load("./build/shaders/basic.vp", GL_VERTEX_SHADER) ||
        !m_shader.build()) {
        return false;
    }

    m_shader.bind();
    m_shader.setUniform("view", glm::lookAt(
        glm::vec3(0, 0, -10),
        glm::vec3(0, 0, 0),
        glm::vec3(0, 1, 0)
    ));
    m_shader.setUniform("projection", glm::perspective(
        60.0f, 
        800.0f / 600.0f, 
        0.1f,
        100.0f
    ));

    //SceneArguments scene_args;
    //scene_args.set("toto", "titi");
    //m_scenes_manager.start<GameScene>(scene_args);

    return true;
}

bool GameEngine::update() {

    if (m_input.getInput(SDL_QUIT)) {
        return false;
    }

    m_context.updateClock(m_clock);
    m_context.updateInputs(m_input);

    /*
    try {
        IScene& scene = m_scenes_manager.getCurrentScene();
        scene.update(m_clock, m_input);
        if (!m_scenes_manager.applyChanges()) {
            // throw an exception
            return false;
        }

    }
    catch (std::string& err) {
        return false;
    }
    */
    return true;
}

void GameEngine::draw() {

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    m_shader.bind();

    m_context.flush();
}
