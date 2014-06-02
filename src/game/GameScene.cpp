#include	"GameScene.hh"

const std::string GameScene::Tag = "game";


GameScene::GameScene(SceneArguments const & args)
  : AScene(Tag), _static(), _movable(), _quad_tree(0)
{
}

GameScene::~GameScene(void) {  
    delete _quad_tree;
}

bool GameScene::initialize(void) {
    _quad_tree = new QuadTree(Rectangle(0, 0, 100, 100)); // replace 100, 100 by map size.
    return true;
}

bool GameScene::update(gdl::Clock const& clock, gdl::Input& input) {

    // If objects can access to the quad tree in their method 'update', 
    // we have to rebuild the quad tree here, and after update.

    // foreach object, update and insert in the clean quad tree.
    _quad_tree->clear();
    this->foreachObject([&](AGameObject& obj) {
        obj.update(clock, input);
        _quad_tree->insert(obj);
    });

    // foreach movable object, check collision with others
    // and call onCollision().
    this->foreachObject(_movable, [&](AGameObject& obj) {
        // skip if it is dead
        if (obj.isDead()) return;
        // fetch the list of near objects with the
        // quad tree's method "retrieve".
        std::list<AGameObject*> list;
        _quad_tree->retrieve(list, obj.getCollider());
        // foreach near object, call a closure.
        this->foreachObject(list, [&](AGameObject& near_obj) {
            // if the near object is dead, skip it.
            if (near_obj.isDead()) return ;
            // it there is a collision, call the "onCollision" obejct's handler.
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
