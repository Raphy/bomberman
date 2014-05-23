#include	"GameScene.hh"

/* CONSTRUCTORS */

GameScene::GameScene(SceneArguments const & args)
  : AScene("GameScene"), _static(), _movable(), _quad_tree(0)
{
}

GameScene::~GameScene(void)
{  
    delete _quad_tree;
}

/* MEMBER FUNCTION */

bool    GameScene::initialize(void)
{
    _quad_tree = new QuadTree(Rectangle(0, 0, 100, 100)); // replace 100, 100 by map size.
    return true;
}

bool    GameScene::update(gdl::Clock const& clock, gdl::Input& input)
{
    // clear the quad tree.
    _quad_tree->clear();

    // foreach object, update and insert in the quad tree
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

bool    GameScene::draw(void)
{
    return true;
}