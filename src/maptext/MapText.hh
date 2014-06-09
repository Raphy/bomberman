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
    static const char HERO = 'h';
    static const char ENEMY = 'e';
    static const char WALL = 'w';

public:
    MapText();

    // tuple for fun :)
    std::tuple<size_t,size_t> getDim() const
    { return std::make_tuple(m_width, m_height); }

    template <typename F> // f(char c, size_t x, size_t y)
    void foreachObject(F closure) {
        size_t y = 0;
        for (auto str_vec : m_map) {
            size_t x = 0;
            for (auto str : str_vec) {
                for (auto c : str) {
                    closure(c, x, y);
                }
                x++;
            }
            y++;
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