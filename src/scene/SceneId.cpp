#include "SceneId.hh"

SceneId::SceneId(std::string const& tag)
    : m_tag(tag)
{
}

SceneId::SceneId(SceneId const& other)
    : m_tag(other.m_tag)
{
}

void SceneId::operator=(SceneId const& other) {
    m_tag = other.m_tag;
}

void SceneId::operator=(std::string const& tag) {
    m_tag = tag;
}

bool SceneId::operator==(SceneId const& other) const {
    return m_tag == other.m_tag;
}

bool SceneId::operator!=(SceneId const& other) const {
    return !operator==(other);
}