
#include "ExampleScene.hh"

const std::string ExampleScene::Tag = "example";

ExampleScene::ExampleScene(SceneArguments const& args) 
    : AScene(Tag)
{
}

ExampleScene::~ExampleScene() {

}

bool ExampleScene::initialize() {
    return true;
}

bool ExampleScene::update(gdl::Clock const& clock, gdl::Input& input) {
    return true;
}

bool ExampleScene::draw(gdl::AShader& shader, gdl::Clock const& clock) {
    return true;
}