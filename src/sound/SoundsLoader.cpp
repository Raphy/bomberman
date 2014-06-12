#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <iterator>

#include "SoundsLoader.hh"
#include "SoundManager.hh"
#include "ResourcesPath.hh"

std::string const SoundsLoader::CONF_FILE = "sounds.conf";

SoundManager& SoundsLoader::s_sound_manager = SoundManager::getInstance();

void SoundsLoader::operator()() {

    std::string filename = ResourcesPath::sound(CONF_FILE);
    std::ifstream f(filename);

    if (f) {
        size_t line_no = 0;
        std::string line;
        while (getline(f, line)) {
            line_no++;
            std::istringstream line_stream(line);
            std::vector<std::string> words;
            copy(std::istream_iterator<std::string>(line_stream),
                std::istream_iterator<std::string>(),
                std::back_inserter(words));
            if (words.size() != 3) {
                std::cerr << "warning: " << filename << ":"
                    << line_no << ": invalid syntax" << std::endl;
            }
            else {
                std::string sound_type = words[0];
                std::string sound_tag = words[1];
                std::string sound_file = ResourcesPath::sound(words[2]);

                bool success = true;
                if (sound_type == "fx") {
                    success = s_sound_manager.loadFx(sound_tag, sound_file);
                }
                else if (sound_type == "music") {
                    success = s_sound_manager.loadMusic(sound_tag, sound_file);
                }
                else {
                    std::cerr << "warning: " << filename << ":"
                        << line_no << ": unknown type '"
                        << sound_type << "'" << std::endl;
                }
                if (success == false) {
                    std::cerr << "warning: " << filename << ":"
                        << line_no << ": could't load '"
                        << sound_file << "'" << std::endl;
                }
            }
        }
    }
}