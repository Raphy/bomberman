#ifndef GAME_API_HH_
# define GAME_API_HH_

# include <string>
# include <tuple>
# include <iterator>

# include "GameScene.hh"

class GameAPI {

// Pattern singleton
private:
    GameAPI() : m_scene(nullptr) {}
    GameAPI(GameAPI const&);
    void operator=(GameAPI const&);

public:
    static GameAPI& getInstance();

// Attributes
private:
    GameScene* m_scene;

// Interface
public:
    // A game scene is it running ?
    bool isset() const { return m_scene != nullptr; }

    // Save the current game in a file.
    void save(std::string const& pathname);

    // Get the map size.
    int getMapWidth() const;
    int getMapHeight() const;
    std::tuple<int, int> getMapSize() const;

    // Get objects in an area. 
    std::list<AGameObject*>& getObjectsIn(Rectangle const& area,
        std::list<AGameObject*>& list,
        std::string const& filter_tag="");

// Internal but public because of "no friend"
public:
    void set(GameScene& scene) { m_scene = &scene; }
    void unset() { m_scene = nullptr; }

};

#endif // !GAME_API_HH_