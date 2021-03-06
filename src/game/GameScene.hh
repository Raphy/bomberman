#ifndef GAMESCENE_HH_
# define GAMESCENE_HH_

# include <list>
# include <cassert>

# include "AScene.hh"
# include "AGameObject.hh"
# include "SceneArguments.hh"
# include "QuadTree.hh"
# include "Marvin.hh"
# include "PlaylistManager.hh"
# include "SkyBox.hh"

/*
** Should need these arguments:
** Player= 1 | 2
*/

// The most interesting scene.
class GameScene : public AScene
{
public:
    static const std::string Tag;
    static const int SKYBOX_OFFSET;

public:
    GameScene(SceneArguments const& args);
    virtual ~GameScene();

    void save(std::string const& filename) const;
 
    int getMapWidth() const { return m_map_width; }
    int getMapHeight() const { return m_map_height; }

    QuadTree& getQuadTree()
    { assert(m_quad_tree); return *m_quad_tree; }
    QuadTree const& getQuadTreeConst() const
    { assert(m_quad_tree); return *m_quad_tree; }


    virtual bool initialize();
    virtual bool update(gdl::Clock const& clock, gdl::Input& input);
    bool resume();
    
protected:        
    virtual bool draw(gdl::AShader& shader, gdl::Clock const& clock);
    
private:
    int m_map_width;
    int m_map_height;
    int m_view_size;
    
    Marvin* m_players[2];
    std::list<AGameObject*> m_objects;
    std::list<AGameObject*> m_walls;
    std::list<AGameObject*> m_loadObj;
    std::list<std::pair<AGameObject*, int>> m_garbageCollector;
    // The magic data structure !
    QuadTree* m_quad_tree;
    SkyBox* m_skybox;
    PlaylistManager m_playlist;
    

private:
    static size_t playerIdx(int num) {
        assert(num == 1 || num == 2);
        return num - 1;
    }

    void fitCamera();

    unsigned int nPlayersRemaing() const;

    template<typename T>
    void instantiateObject(int x, int y, std::list<AGameObject*> & list, bool isStatic = false) {
        list.push_back(new T());
        list.back()->setPosition(
            static_cast<double>(x), static_cast<double>(y));
        list.back()->isStatic(isStatic);
    }

    void loadMap(std::string const& filename);
    void genMap(int width, int height, int players, int ai);
    void initPlayer(int num, int x, int y);

    SkyBox * createSkybox() const;
    
    void initPlaylist();

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
        foreachObject(m_objects, closure);
        foreachObject(m_walls, closure);
    }
    template<typename Funct>
    void foreachObject(Funct closure) const {
        foreachObject(m_objects, closure);
        foreachObject(m_walls, closure);
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
        removeObjectsIf(m_objects, closure);
        removeObjectsIf(m_walls, closure);
    }

    // Clear then build the quad tree with new objects positions.
    void rebuildQuadTree();
    void zoomCamera(int key);
    bool isGameOver() const;    
    void createFloor();
    bool isPlayer(AGameObject const& obj) const;
    bool isWithinPlayers(AGameObject const & obj) const;
};

#endif