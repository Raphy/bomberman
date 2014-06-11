#include <cstdlib>
#include <cassert>

#include "GameScene.hh"
#include "Exception.hh"
#include "MapTextLoader.hh"
#include "MapTextSaver.hh"

#include "Wall.hh"

const std::string GameScene::Tag = "game";

GameScene::GameScene(SceneArguments const & args)
    : AScene(Tag), m_map_width(0), m_map_height(0),
    m_players(),
    m_static(), m_movable(), m_quad_tree(0)
{
    m_players[0] = nullptr;
    m_players[1] = nullptr;

    std::string const& str_file = args.get("file");
    if (str_file.empty() == false) {
        loadMap(str_file);
    }
    else {
        std::string const& str_width = args.get("width");
        std::string const& str_height = args.get("height");

        if (str_width.empty() || str_height.empty()) {
            throw Exception("fail to construct the game scene: "
                "missing arguments 'file', 'width' or 'height'");
        }
        genMap(atoi(str_width.c_str()), atoi(str_height.c_str()));
    }
}

GameScene::~GameScene() {  
    delete m_quad_tree; 
}

void GameScene::initPlayer(int num, int x, int y) {
    size_t idx = playerIdx(num);

    if (m_players[idx]) {
        Exception err;
        err.getStream() << "invalid duplicated object 'player" << num << "'";
        throw err;
    }

    Marvin* player = new Marvin();
    player->setPosition(static_cast<double>(x), static_cast<double>(y));
    if (num == 1) player->setBindKeys();
    else player->setBindKeys({SDLK_z, SDLK_s, SDLK_q, SDLK_d});
    m_players[idx] = player;
    m_movable.push_back(player);
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
                case MapText::ENEMY:
                    //m_movable.push_back(new ?)
                    //m_movable.back()->setPosition(
                    //  static_cast<double>(x), static_cast<double>(y));
                    break;
                case MapText::WALL:
                    m_static.push_back(new Wall());
                    m_static.back()->setPosition(
                        static_cast<double>(x), static_cast<double>(y));
                    break;
                // case MapText::BOMB: break;
                // case MapText::FIRE: break;
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

void GameScene::genMap(int width, int height) {
    m_map_width = width;
    m_map_height = height;
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

bool GameScene::initialize() {

    bool init_success = true;

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
            camera->setOffset(glm::vec3(0, 10, -10));
            camera->initialize();
            addCamera("p" + std::to_string(player_num), camera);
        }
    }

    m_quad_tree = new QuadTree(Rectangle(0, 0, m_map_width, m_map_height));
    rebuildQuadTree();
    return true;
}

bool GameScene::update(gdl::Clock const& clock, gdl::Input& input) {

    // Foreach object, update and insert in the new quad tree.
    foreachObject([&](AGameObject& obj) {

        obj.update(clock, input);
    });

    rebuildQuadTree();

    // Foreach movable object, check collision with others
    // and call onCollision().
    foreachObject(m_movable, [&](AGameObject& obj) {

        if (obj.isDead()) return;

        std::list<AGameObject*> list;
        m_quad_tree->retrieve(list, obj.getCollider());
        foreachObject(list, [&](AGameObject& near_obj) {

            if (near_obj.isDead()) return ;

            if (obj.getCollider().overlapping(near_obj.getCollider()) && &obj != &near_obj) {
                obj.onCollision(near_obj);
            }
        });
    });

    // then, remove all dead objects.
    removeObjectsIf([&](AGameObject& obj) -> bool {
        return obj.isDead();
    });

    return true;
}

bool GameScene::draw(gdl::AShader& shader, gdl::Clock const& clock) {

    foreachObject([&] (AGameObject& obj) {
        if (obj.isDead() == false) {
            obj.draw(shader, clock);
        }
    });
    return true;
}

void GameScene::rebuildQuadTree() {
    m_quad_tree->clear();

    foreachObject([&](AGameObject& obj) {
        m_quad_tree->insert(obj);
    });
}
