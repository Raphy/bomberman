#ifndef MAPTEXTSAVER_HH_
# define MAPTEXTSAVER_HH_

# include <fstream>
# include <map>

# include "MapText.hh"
# include "AGameObject.hh"

class MapTextSaver : public MapText {

private:
    std::ofstream m_file;

    static std::map<std::string, char> s_letter_from_tag;

public:
    MapTextSaver(std::string const& pathname, size_t width, size_t height);

    void add(char type, size_t x, size_t y);
    void add(AGameObject const& obj); // do nothing when obj is marvin
    void addPlayer(int player_num, size_t x, size_t y);
    void save();
};


#endif // !MAPTEXTSAVER_HH_