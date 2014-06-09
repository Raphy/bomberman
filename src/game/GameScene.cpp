#include <cstdlib>
#include "GameScene.hh"

const std::string GameScene::Tag = "game";

GameScene::GameScene(SceneArguments const & args)
    : AScene(Tag), _map_width(100), _map_height(100),
     _static(), _movable(), _quad_tree(0)
{

    std::string const& str_width = args.get("width");
    std::string const& str_height = args.get("height");

    if (str_width.empty() == false) {
        _map_width = atoi(str_width.c_str());
    }

    if (str_height.empty() == false) {
        _map_height = atoi(str_height.c_str());
    }
}

GameScene::~GameScene(void) {  
    delete _quad_tree; 
}

bool GameScene::initialize(void) {
    _quad_tree = new QuadTree(Rectangle(0, 0, _map_width, _map_height));
    return true;
}

bool GameScene::update(gdl::Clock const& clock, gdl::Input& input) {

    // Foreach object, update and insert in the new quad tree.
    this->foreachObject([&](AGameObject& obj) {
        obj.update(clock, input);
    });

    this->rebuildQuadTree();

    // Foreach movable object, check collision with others
    // and call onCollision().
    this->foreachObject(_movable, [&](AGameObject& obj) {

        if (obj.isDead()) return;

        std::list<AGameObject*> list;
        _quad_tree->retrieve(list, obj.getCollider());
        this->foreachObject(list, [&](AGameObject& near_obj) {

            if (near_obj.isDead()) return ;

            if (obj.getCollider().overlapping(near_obj.getCollider())) {
                obj.onCollision(near_obj);
            }
        });
    });

    // then, remove all dead objects.
    this->removeObjectsIf([&](AGameObject& obj) -> bool {
        return obj.isDead();
    });

    return true;
}

bool GameScene::draw(gdl::AShader& shader, gdl::Clock const& clock) {
    return true;
}

void GameScene::rebuildQuadTree() {
    _quad_tree->clear();

    this->foreachObject([&](AGameObject& obj) {
        _quad_tree->insert(obj);
    });
}
