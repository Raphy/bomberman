#ifndef GAMESCENE_HH_
# define GAMESCENE_HH_

# include <list>

# include "AScene.hh"
# include "AGameObject.hh"
# include "SceneArguments.hh"
# include "QuadTree.hh"
# include "Marvin.hh"

/*
** Should need these arguments:
** Player= 1 | 2
*/

// The most interesting scene.
class GameScene : public AScene
{
public:
    static const std::string Tag;

public:
    GameScene(SceneArguments const& args);
    virtual ~GameScene();

    virtual bool initialize();
    virtual bool update(gdl::Clock const& clock, gdl::Input& input);
    
protected:        
    virtual bool draw(gdl::AShader& shader, gdl::Clock const& clock);
    
private:
    int m_map_width;
    int m_map_height;

    Marvin* m_players[2];
    // List of static object (wall, ...)
    std::list<AGameObject*> m_static;
    // List of movable object (player, ia, bomb, ...)
    std::list<AGameObject*> m_movable;
    // The magic data structure !
    QuadTree* m_quad_tree;

private:
    static size_t playerIdx(int num) {
        assert(num == 1 || num == 2);
        return num - 1;
    }

    void loadMap(std::string const& filename);
    void genMap(int width, int height);
    void initPlayer(int num, int x, int y);
    void save(std::string const& filename) const;

    // Call a closure/functor for each object in the list.
    // (the closure must take an AGameObject&)
    template<typename Funct>
    void foreachObject(std::list<AGameObject*>& objects, Funct closure) {
        for (auto obj : objects) {
            closure(*obj);
        }
    }
    template<typename Funct>
    void foreachObject(std::list<AGameObject*> const& objects, Funct closure) const {
        for (auto obj : objects) {
            closure(*obj);
        }
    }

    // Call a closure/functor for each static and movable object.
    template<typename Funct>
    void foreachObject(Funct closure) {
        foreachObject(m_movable, closure);
        foreachObject(m_static, closure);
    }
    template<typename Funct>
    void foreachObject(Funct closure) const {
        foreachObject(m_movable, closure);
        foreachObject(m_static, closure);   
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
        removeObjectsIf(m_static, closure);
        removeObjectsIf(m_movable, closure);
    }

    // Clear then build the quad tree with new objects positions.
    void rebuildQuadTree();
};

#endif