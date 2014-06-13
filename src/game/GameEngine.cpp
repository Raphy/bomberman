#include <iostream>

#include "GameEngine.hh"
#include "GameScene.hh"
#include "Exception.hh"
#include "MainMenu.hh"
#include "SoundsLoader.hh"
#include "ResourcesPath.hh"

GameEngine::GameEngine():
    m_scenes_manager()
{
}

GameEngine::~GameEngine()
{
}

bool GameEngine::initialize() {

    if (!m_context.start(800, 600, "My bomberman!")) {
        throw Exception("fail to start gdl context");
    }

    glEnable(GL_DEPTH_TEST);

    if (!m_shader.load(ResourcesPath::shader("basic.fp"), GL_FRAGMENT_SHADER)) {
        throw Exception("fail to load '" + ResourcesPath::shader("basic.fp") + "'");
    }
    if (!m_shader.load(ResourcesPath::shader("basic.vp"), GL_VERTEX_SHADER)) {
        throw Exception("fail to load '" + ResourcesPath::shader("basic.vp") + "'");
    }
    if (!m_shader.build()) {
        throw Exception("fail to build shader");
    }

    SoundsLoader()();

    SceneArguments scene_args;
    m_scenes_manager.start<FirstScene>(scene_args);

    return true;
}

bool GameEngine::update() {

    m_context.updateClock(m_clock);
    m_context.updateInputs(m_input);

    if (m_input.getInput(SDL_QUIT)) {
        return false;
    }

    if (m_scenes_manager.empty()) {
        return false;
    }

    if (m_scenes_manager.applyChanges() == false) {
        throw Exception("critical error");
    }

    if (m_scenes_manager.empty()) {
        return false;
    }

    IScene& scene = m_scenes_manager.getCurrentScene();
    if (scene.update(m_clock, m_input) == false) {
        throw Exception("fail to update scene '" + scene.getId().unwrap() + "'");
    }


    return true;
}

void GameEngine::draw() {

    if (m_scenes_manager.empty())
        return ;
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    m_shader.bind();
    IScene& scene = m_scenes_manager.getCurrentScene();
    scene.metaDraw(m_shader, m_clock);
    m_context.flush();
}
