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
#include "Configuration.hh"


SoundManager& SoundsLoader::s_sound_manager = SoundManager::getInstance();

void SoundsLoader::operator()() {

  ResourcesPath::root("./build");

  Configuration::setDefault<std::string>("maintheme", ResourcesPath::sound("goto80.wav"));
  Configuration::setDefault<std::string>("button", ResourcesPath::sound("button.wav"));
  Configuration::setDefault<std::string>("menu", ResourcesPath::sound("menu.wav"));
  bool success = true;

  success = s_sound_manager.loadMusic("maintheme", ResourcesPath::sound(Configuration::get<std::string>("maintheme")));
  success = s_sound_manager.loadMusic("menu", ResourcesPath::sound(Configuration::get<std::string>("menu")));
  success = s_sound_manager.loadFx("button", ResourcesPath::sound(Configuration::get<std::string>("button")));

  if (success == false)
    std::cerr << "some sounds are not loaded" << std::endl;
}
