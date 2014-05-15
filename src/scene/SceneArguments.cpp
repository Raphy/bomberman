#include "SceneArguments.hh"

 std::string const SceneArguments::static_empty_str = "";


void SceneArguments::set(std::string const& key, std::string const& value) {
    m_map[key] = value;
}

std::string const& SceneArguments::get(std::string const& key) const {
    auto it = m_map.find(key);
    return it == m_map.end() ? static_empty_str : it->second;
}