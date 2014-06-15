#include <cstdlib>
#include <cassert>
#include <iterator>

#include "API/Manager.hh"
#include "GameScene.hh"
#include "Exception.hh"
#include "MapTextLoader.hh"
#include "MapTextSaver.hh"
#include "GameAPI.hh"

#include "Wall.hh"
#include "Box.hh"
#include "IA.hh"
#include "MapGenerator.hh"
#include "Bomb.hh"
#include "Fire.hh"
#include "SkyBox.hh"
#include "Floor.hh"

#include "OptionMenu.hh"
#include "PauseMenu.hh"
#include "LoseMenu.hh"

const int GameScene::SKYBOX_OFFSET = 50;
const std::string GameScene::Tag = "game";
static int const GARBAGE_FRAME_COUNTER = 10;
static int const DEFAULT_VIEW_SIZE = 10;

GameScene::GameScene(SceneArguments const & args)
    : AScene(Tag), m_map_width(0), m_map_height(0), m_view_size(DEFAULT_VIEW_SIZE),
    m_players(),
    m_objects(), m_walls(), m_quad_tree(0),
    m_playlist()
{
    m_players[0] = nullptr;
    m_players[1] = nullptr;

    // load a file or gen a map
    std::string const& str_file = args.get("file");
    if (str_file.empty() == false) {
        loadMap(str_file);
    }
    else {
        std::string const& str_width = args.get("width");
        std::string const& str_height = args.get("height");
        std::string const& str_players = args.get("players");
        std::string const& str_ai = args.get("ai");
        
        if (str_width.empty() || str_height.empty()) {
            throw Exception("fail to construct the game scene: "
                "missing arguments 'file', 'width' or 'height'");
        }
        genMap(atoi(str_width.c_str()), atoi(str_height.c_str()), atoi(str_players.c_str()), atoi(str_ai.c_str()));
    }
    this -> m_skybox = createSkybox();
    this -> createFloor();
    // api registration
    GameAPI::getInstance().set(*this);
}

GameScene::~GameScene() {
    // api unregistration
    GameAPI::getInstance().unset();

    // free memory$
    delete m_quad_tree;
    delete m_skybox;
    foreachObject([] (AGameObject& obj) {
        delete &obj;
    });
    foreachObject(m_loadObj, [] (AGameObject& obj) {
        delete &obj;
    });
    for (auto it = this -> m_garbageCollector.begin(); it != this -> m_garbageCollector.end(); ++it) {
        delete (*it).first;
    }
}

void GameScene::initPlayer(int num, int x, int y) {
    size_t idx = playerIdx(num);

    if (m_players[idx]) {
        Exception err;
        err.getStream() << "invalid duplicated object 'player" << num << "'";
        throw err;
    }

    Marvin* player = new Marvin(num);
    player->setPosition(static_cast<double>(x), static_cast<double>(y));

    if (num == 2) {
        player->setBindKeys();
    }
    else {
        player->setBindKeys({SDLK_z, SDLK_s, SDLK_q, SDLK_d, SDLK_LCTRL});
    }
    m_players[idx] = player;
    m_objects.push_back(player);
}

void GameScene::loadMap(std::string const& filename) {
    try {
        MapTextLoader loader(filename);
        std::tie (m_map_width, m_map_height) = loader.getDim();
        if (m_map_width < 10 || m_map_height < 10) {
            throw Exception("the map '" + filename + "' is too small");
        }
        loader.foreachObject([&](char type, int x, int y) {
            switch (type) {
                case MapText::PLAYER_1: initPlayer(1, x, y); break;
                case MapText::PLAYER_2: initPlayer(2, x, y); break;
                case MapText::ENEMY:    instantiateObject<IA>(x, y, m_objects); break;
                case MapText::BOX:      instantiateObject<Box>(x, y, m_objects); break;
                case MapText::WALL:     instantiateObject<Wall>(x, y, m_walls); break;
                case MapText::BOMB:     instantiateObject<Bomb>(x, y, m_objects); break;
                case MapText::FIRE:     instantiateObject<Fire>(x, y, m_objects); break;
                default: break;
            }
        });
        if (!m_players[0] && !m_players[1]) {
            throw Exception("the map '" + filename + "' doesn't contain any player");
        }
    } catch (Exception err) {
        // todo: graphical error
        throw err;
    }
}

void GameScene::createFloor() {
    for (int i = 0; i < getMapHeight(); i++) {
        for (int j = 0; j < getMapWidth(); j++) {
            instantiateObject<Floor>(j, i, m_walls);
        }
    }
}

SkyBox* GameScene::createSkybox() const {
    SkyBox * result = new SkyBox();
    result->setScale(glm::vec3(getMapWidth() + SKYBOX_OFFSET, SKYBOX_OFFSET * 1, getMapHeight() + SKYBOX_OFFSET));
    result->setPosition(glm::vec3(getMapWidth() / 2, -(SKYBOX_OFFSET * 0.5), getMapHeight() / 2));
    return result;
}

void GameScene::genMap(int width, int height, int players, int ai) {
    m_map_width = width;
    m_map_height = height;
    MapGenerator    map;

    std::pair<std::list<AGameObject*>, std::list<AGameObject*>> tmp = map.Generate(width, height);
    this -> m_walls.merge(tmp.first);
    this -> m_objects.merge(tmp.second);
    
    std::list<std::pair<int, int> > playersList = map.setHumans(players, ai);

    for (int i = 0; i < players; i++) {
        initPlayer(i + 1, playersList.front().second, playersList.front().first);
        playersList.erase(playersList.begin());
    }
    for (auto it = playersList.begin(); it != playersList.end();) {
        instantiateObject<IA>((*it).second, (*it).first, m_objects);
        playersList.erase(it++);
    }
    this -> createFloor();
}

void GameScene::save(std::string const& filename) const {
    MapTextSaver saver(filename, m_map_width, m_map_height);

    for (int player_num = 1; player_num <= 2; player_num++) {
        AGameObject const* player = m_players[playerIdx(player_num)];
        if (player) {
            double x, y;
            std::tie (x, y) = player->getPosition();
            saver.addPlayer(player_num,
                static_cast<size_t>(x), static_cast<size_t>(y));
        }
    }

    this->foreachObject([&](AGameObject const& obj) {
        saver.add(obj);
    });

    saver.save();
}

void GameScene::initPlaylist() {
    m_playlist.deletePlaylist();
    m_playlist.addPlaylist("maintheme");
    m_playlist.playPlaylist();
}

bool GameScene::isGameOver() const {
    for (auto player : m_players) {
        if (player && player->isDead() == false) {
            return false;
        }
    }
    return true;
}

bool GameScene::initialize() {

    bool init_success = true;

    m_quad_tree = new QuadTree(Rectangle(0, 0, m_map_width, m_map_height));
    m_skybox->initialize();
    
    foreachObject([&] (AGameObject& obj) {
        if (obj.initialize() == false) {
            init_success = false;
        }
    });

    if (init_success == false) {
        return false;
    }

    for (int player_num = 1; player_num <= 2; player_num++) {
        size_t idx = playerIdx(player_num);
        if (m_players[idx] != nullptr) {
            Camera* camera = new Camera(m_players[idx]);
            camera->setOffset(glm::vec3(0, 4, -4));
            camera->initialize();
            addCamera("p" + std::to_string(player_num), camera);
        }
    }

    initPlaylist();

    rebuildQuadTree();

    // pre-loading those objects so to have their .fbx already in memory
    this -> m_loadObj.push_back(new Bomb());
    this -> m_loadObj.push_back(new Fire());
    this -> m_loadObj.push_back(new IA());

    return true;
}

void GameScene::zoomCamera(int key) {
    for (int player_num = 1; player_num <= 2; player_num++) {
        if (m_players[playerIdx(player_num)]) {
            Camera *cam = getCamera("p" + std::to_string(player_num));
            if (cam) {
                if (key == SDLK_KP_PLUS) {
                    cam->zoomPlus();
                }
                else {
                    cam->zoomMinus();
                }
            }
        }
    }
}

bool GameScene::isPlayer(AGameObject const& obj) const {
    for (auto player : m_players) {
        if (player && player == &obj) {
            return true;
        }
    }
    return false;
}

bool GameScene::update(gdl::Clock const& clock, gdl::Input& input) {

    m_playlist.update();

    if (input.getKey(SDLK_ESCAPE)) {
      setStatusGoOn<PauseMenu>(*new SceneArguments());
        return true;
    }
    else if (input.getKey(SDLK_KP_PLUS)) {
        zoomCamera(SDLK_KP_PLUS);
    }
    else if (input.getKey(SDLK_KP_MINUS)) {
        zoomCamera(SDLK_KP_MINUS);
    }

    if (isGameOver()) {
        std::cout<< "game over" << std::endl;
        setStatusGoOn<LoseMenu>(*new SceneArguments());
    }

    std::list<AGameObject*> new_objects;

    // Foreach object, update and insert in the new quad tree.
    for (auto obj : m_objects) {
        if (obj->isDead() == false) {
            obj->update(clock, input);
            if (obj->instanciatedObjects()) {
                obj->getObjectsAndReset(std::back_inserter(new_objects));
            }
        }
    }

    if (new_objects.empty() == false) {
        for (auto obj : new_objects) {
            if (obj->initialize() == false) {
                return false;
            }
            m_objects.push_back(obj);
        }
    }

    rebuildQuadTree();

    // Foreach movable object, check collision with others
    // and call onCollision().
    for (auto obj : m_objects) {
        if (obj->isDead()) continue;
        std::list<AGameObject*> near_list;
        m_quad_tree->retrieve(near_list, obj->getCollider());
        for (auto near_obj : near_list) {
            if (near_obj->isDead()) continue;
            if (obj != near_obj && obj->getCollider().overlapping(near_obj->getCollider())) {
                obj->onCollision(*near_obj);
            }
        }
    }

    // then, sets cooldown to item for garbage collector.
    bool no_more_ai = true;
    for (auto it = m_objects.begin(); it != m_objects.end();) {
        if (isPlayer(**it) == false && (*it)->isDead()) {
            this -> m_garbageCollector.push_back(std::pair<AGameObject*, int>(*it, GARBAGE_FRAME_COUNTER));
            m_objects.erase(it++);
        }
        else {
            if (no_more_ai && (*it)->getType() == IA::Tag) {
                no_more_ai = false;
            }
            it++;
        }
    }

    // Free object after cooldown.
    for (auto it = this -> m_garbageCollector.begin(); it != this -> m_garbageCollector.end();) {
        (*it).second--;
        if ((*it).second == 0) {
            delete (*it).first;
            this -> m_garbageCollector.erase(it++);
        }
        else {
            ++it;
        }
    }

    if (no_more_ai && nAiRemaing() == 1) {
        std::cout << "You win !" << std::endl;
        setStatusGoOn<LoseMenu>(*new SceneArguments());
    }

    return true;
}

bool GameScene::draw(gdl::AShader& shader, gdl::Clock const& clock) {

    this -> m_skybox->draw(shader, clock);
    foreachObject([&] (AGameObject& obj) {
        if (obj.isDead() == false && GameScene::isWithinPlayers(obj) == true) {
                obj.draw(shader, clock);
        }
    });
    return true;
}

unsigned int GameScene::nAiRemaing() const {
    unsigned int n = 0;
    for (auto player : m_players) {
        if (player != nullptr && player->isDead() == false) {
            n++;
        }
    }
    return n;
}

bool GameScene::resume() {
    m_playlist.playPlaylist();
    return true;
}

void GameScene::rebuildQuadTree() {
    m_quad_tree->clear();

    foreachObject([&](AGameObject& obj) {
        m_quad_tree->insert(obj);
    });
}

bool GameScene::isWithinPlayers(const AGameObject& obj) const {

    std::tuple<double, double> posSelf;
    std::tuple<double, double> posObj = obj.getPosition();
    double xSelf = 0;
    double ySelf = 0;
    double xObj = std::get<0>(posObj);
    double yObj = std::get<1>(posObj);
    
    for (auto player : this -> m_players) {
        if (player == nullptr) {
            continue;
        }
        posSelf = player->getPosition();
        xSelf = std::get<0>(posSelf);
        ySelf = std::get<1>(posSelf);
        
        if (xSelf + this -> m_view_size / 2 >= xObj && ySelf + this -> m_view_size / 2 >= yObj
                && xSelf - this -> m_view_size / 2 <= xObj && ySelf - this -> m_view_size / 2 <= yObj) {
            return true;
        }
    }
    return false;
}

/*
 *       -------    ^
 *       |     |    |
 *       |  *  |    |
 *       |     |    |
 *       -------    |
 *  <----------------  X
 *
 *                  Z
 */
