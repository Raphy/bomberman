#include "AScene.hh"


AScene::AScene(std::string const& id_tag)
    : m_status(), m_id(id_tag)
{
}

void AScene::setStatusNone() {
    m_status.setNone();
}

void AScene::setStatusBack() {
    m_status.setBack();
}

void AScene::setStatusRewind(std::string const& id_tag) {
    m_status.setRewind(SceneId(id_tag));
}

SceneStatus const& AScene::getStatus() const {
    return m_status;
}

SceneId const& AScene::getId() const {
    return m_id;
}