#include <cstdlib>

#include "SceneStatus.hh"

SceneStatus::SceneStatus()
    : m_type(None), m_rewind_id(), m_go_on_factory(NULL, NULL)
{
}

SceneStatus::~SceneStatus() {
    if (m_go_on_factory.second) {
        delete m_go_on_factory.second;
        m_go_on_factory.second = NULL;
    }
}

SceneStatus::Type SceneStatus::getType() const {
    return m_type;
}

SceneId const& SceneStatus::getRewindId() const {
    return m_rewind_id;
}

SceneStatus::PairFactory const& SceneStatus::getGoOnFactory() const {
    return m_go_on_factory;
}

void SceneStatus::setNone() {
    m_type = None;
}

void SceneStatus::setBack() {
    m_type = Back;
}

void SceneStatus::setRewind(SceneId const& scene_id) {
    m_type = Rewind;
    m_rewind_id = scene_id;
}

void SceneStatus::setGoOn(FunctSceneFactory factory, SceneArguments& args) {
    m_type = GoOn;
    if (m_go_on_factory.second) {
        delete m_go_on_factory.second;
        m_go_on_factory.second = NULL;
    }
    m_go_on_factory = PairFactory(factory, &args);
}
