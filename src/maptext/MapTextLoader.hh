#ifndef MAPTEXTLOADER_HH_
# define MAPTEXTLOADER_HH_

# include <fstream>

# include "MapText.hh"

class MapTextLoader : public MapText {

private:
    std::ifstream m_file;

public:
    MapTextLoader(std::string const& pathname);

private:
    void split(std::string const& line, StrVector& vector) const;
    bool readLine(std::string& line_buf);
};

#endif // !MAPTEXTLOADER_HH_