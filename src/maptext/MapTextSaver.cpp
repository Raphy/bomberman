#include <cassert>
#include <tuple>
#include "MapText.hh"

#include "MapTextSaver.hh"
#include "Wall.hh"

std::map<std::string, char> MapTextSaver::s_letter_from_tag = {
    { Wall::Tag, MapText::WALL },
    //{ Bomb::Tag, MapText::BOMB },
    //{ Enemy::Tag, MapText::ENEMY },
    //{ Fire::Tag, MapText:FIRE },
};

MapTextSaver::MapTextSaver(std::string const& pathname, size_t width, size_t height)
    : MapText(), m_file(pathname)
{
    assert(width > 0 && height > 0);
    m_width = width; m_height = height; 
    m_map.resize(m_height);
    for (auto& str_vec : m_map) {
        str_vec.resize(m_width);
    }
}

void MapTextSaver::add(char type, size_t x, size_t y) {
    if (x < m_width && y < m_height) {
        m_map[y][x] += type;
    }
}

void MapTextSaver::add(AGameObject const& obj) {
    auto it = s_letter_from_tag.find(obj.getType());
    if (it != s_letter_from_tag.end()) {
        double x, y;
        std::tie (x, y) = obj.getPosition();
        add(it->second, static_cast<size_t>(x), static_cast<size_t>(y));
    }
}

void MapTextSaver::addPlayer(int player_num, size_t x, size_t y) {
    assert(player_num == 1 || player_num == 2);
    add('0' + player_num, x, y);
}

void MapTextSaver::save() {
    for (auto const& str_vec : m_map) {
        for (auto const& str : str_vec) {
            m_file << (str.empty() ? "_" : str) << " ";
        }
        m_file << std::endl;
    }
}
