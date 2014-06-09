#include <algorithm>
#include <cassert>
#include <cerrno>
#include <cstring>
#include <iterator>

#include "MapTextLoader.hh"
#include "Exception.hh"

MapTextLoader::MapTextLoader(std::string const& pathname) :
    MapText(), m_file(pathname)
{
    if (!m_file) {
        throw Exception(pathname + ": " + std::string(strerror(errno)));
    }

    assert(m_width == 0 && m_height == 0);
    std::string line;
    while (readLine(line)) {
        m_map.push_back(StrVector());
        split(line, m_map.back());
        if (m_map.back().empty()) {
            m_map.pop_back();
        } else {
            m_width = std::max(m_width, (size_t)m_map.back().size());
            m_height++;
        }
    }       
}

void MapTextLoader::split(std::string const& line, StrVector& vector) const {
    std::istringstream iss(line);
    std::copy(
        std::istream_iterator<std::string>(iss),
        std::istream_iterator<std::string>(),
        std::back_inserter(vector)
    );
}

bool MapTextLoader::readLine(std::string& line_buf) {
    return std::getline(m_file, line_buf);
}