#ifndef MAPTEXT_HH_
# define MAPTEXT_HH_

# include <vector>
# include <string>
# include <tuple>
# include <fstream>

class MapText {

protected:
    size_t m_width, m_height;
    typedef std::vector<std::string> StrVector;
    typedef std::vector<StrVector> StrMatrix;
    StrMatrix m_map;

public:

    static const char DELIM = ' ';

    static const char VOID = '_';
    static const char PLAYER_1 = '1';
    static const char PLAYER_2 = '2';
    static const char ENEMY = 'e';
    static const char WALL = 'w';
    static const char BOMB = 'b';
    static const char FIRE = 'f';

public:
    MapText();

    // tuple for fun :)
    std::tuple<int,int> getDim() const
    { return std::make_tuple((int)m_width, (int)m_height); }

    template <typename F> // f(char c, size_t x, size_t y)
    void foreachObject(F closure) {
        size_t y = m_map.size();
        for (auto& str_vec : m_map) {
            y--;
            size_t x = str_vec.size();
            for (auto& str : str_vec) {
                x--;
                for (auto c : str) {
                    closure(c, x, y);
                }
            }
        }
    }

    template <typename F> // f(size_t x, size_t y)
    void foreachObject(char type, F closure) {
        this->foreachObject([&](char c, size_t x, size_t y) {
            if (c == type) {
                closure(x, y);
            }
        });
    }
};

#endif // !MAPTEXT_HH_