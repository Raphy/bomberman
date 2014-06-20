/* 
 * File:   Demo.cpp
 * Author: svirch_n
 * 
 * Created on 15 June 2014, 21:25
 */

#include "Demo.hh"
#include "Marvin.hh"
#include "MainMenu.hh"

Demo::Demo(const SceneArguments& arg) : AScene("demo"), _arg(*new SceneArguments()) {
  _arg.set("width",arg.get("width"));
  _arg.set("file",arg.get("file"));
  _arg.set("players",arg.get("players"));
  _arg.set("height",arg.get("height"));
  _arg.set("ai",arg.get("ai"));
}


bool Demo::initialize() {
    
    Marvin * player = new Marvin();
    player->setPosition(glm::vec3(0, 0, 0));
    if (player->initialize() == false)
        return false;
    _objects.push_back(player);
    
    Camera * camera = new Camera(player);
    camera->setOffset(glm::vec3(0, 20, 20));
    
    addCamera("primary", camera);
    
    return true;
}

bool Demo::update(const gdl::Clock& clock, gdl::Input& input) {
    
    Camera *cam = getCamera("primary");
    
    glm::vec3 offset = cam->getOffset();
    
    if (offset.y <= 3)
        setStatusGoOn<MainMenu>(_arg);
    
    cam->setOffset(glm::vec3(offset.x, offset.y - 0.1, offset.z - 0.1));
    
    return true;
}

bool Demo::draw(gdl::AShader& shader, const gdl::Clock& clock) {
    
    
    for (auto object : this -> _objects) {
        
        object->draw(shader, clock);
        
    }
    return true;
}
