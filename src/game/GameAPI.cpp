#include "GameAPI.hh"
#include "QuadTree.hh"

GameAPI& GameAPI::getInstance() {
    static GameAPI instance;
    return instance;
}

void GameAPI::save(std::string const& pathname) {
    if (isset()) {
        m_scene->save(pathname);
    }
}

int GameAPI::getMapWidth() const {
    return isset() ? m_scene->getMapWidth() : 0;
}

int GameAPI::getMapHeight() const {
    return isset() ? m_scene->getMapHeight() : 0;
}

std::tuple<int, int> GameAPI::getMapSize() const {
    return std::make_tuple(getMapWidth(), getMapWidth());
}

std::list<AGameObject*>& GameAPI::getObjectsIn(Rectangle const& area,
    std::list<AGameObject*>& list, std::string const& filter_tag) {

    if (isset()) {

        QuadTree& quad_tree = m_scene->getQuadTree();
        quad_tree.retrieve(list, area);
        list.remove_if([&] (AGameObject const* obj) -> bool {
            return obj->isDead() || !obj->getCollider().overlapping(area) ||
                (filter_tag.empty() == false && filter_tag == obj->getType());
        });
    }

    return list;
}
