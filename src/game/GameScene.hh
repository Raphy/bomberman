#ifndef     GAMESCENE_HH_
# define    GAMESCENE_HH_

# include   <list>

# include   "AScene.hh"
# include   "AGameObject.hh"
# include   "SceneArguments.hh"
# include   "QuadTree.hh"

/*
** Should need these arguments:
** Player= 1 | 2
*/

// The most interesting scene.
class       GameScene : public AScene
{
public:
    GameScene(SceneArguments const& args);
    virtual ~GameScene(void);

    virtual bool              initialize(void);
    virtual bool              update(gdl::Clock const& clock, gdl::Input& input);
    virtual bool              draw(void);

private:
    // List of static object (wall, ...)
    std::list<AGameObject*>   _static;
    // List of movable object (player, ia, bomb, ...)
    std::list<AGameObject*>   _movable;
    // The magic data structure !
    QuadTree*                 _quad_tree;

    // Call a closure/functor for each object in the list.
    // (the closure must take an AGameObject&)
    template<typename Funct>
    void foreachObject(std::list<AGameObject*>& objects, Funct closure) {
        for (auto obj : objects) {
            closure(*obj);
        }
    }

    // Call a closure/functor for each static and movable object.
    template<typename Funct>
    void foreachObject(Funct closure) {
        foreachObject(_static, closure);
        foreachObject(_movable, closure);
    }

    // Foreach object of the list, remove it if closure return true.
    template<typename Funct>
    void removeObjectsIf(std::list<AGameObject*>& objects, Funct closure) {
        auto it = objects.begin();
        while (it != objects.end()) {
            if (closure(**it)) {
                objects.erase(it++);
            }
            else {
                it++;
            }
        }
    }

    // Foreach static and movable object, remove it if the closure return true.
    template<typename Funct>
    void removeObjectsIf(Funct closure) {
        removeObjectsIf(_static, closure);
        removeObjectsIf(_movable, closure);
    }
};

#endif