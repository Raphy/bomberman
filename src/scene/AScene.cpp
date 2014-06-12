#include <map>

#include "AScene.hh"
#include "Camera.hh"
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

Camera* AScene::getCamera(const std::string& label) {
   auto it = m_cameras.find(label);
   
   if (it == m_cameras.end())
       return nullptr;
   return it->second;
}

void AScene::removeCamera(std::string label) {
   m_cameras.erase(m_cameras.find(label)); 
}


bool AScene::metaDraw(gdl::AShader& shader, const gdl::Clock& clock) {

    assert(m_cameras.empty() == false);
    
    int offset = 800 / m_cameras.size();
    int i = 0;
    
    for (auto const& pair : m_cameras) {
        glViewport(i * offset, 0, offset, 600);
        pair.second->forceUpdate(shader, m_cameras.size());
        draw(shader, clock);
        i++;
    }
    
    
    return true;
}
