#include <OpenGL.hh>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <cstdlib>
#include <string>
#include <ctime>

#include <unistd.h>
#include <iostream>
#include <exception>

#include "GameEngine.hh"
#include "ResourcesPath.hh"
#include "Configuration.hh"
#include "SoundManager.hh"
#include "Scoring.hh"

int main()
{
  ResourcesPath::setRootDir("./build");

  // Initialization of the random system
  srand(time(NULL));

  try {
    GameEngine engine;

    // Loading statics and singletons classes
    Configuration::load();
    SoundManager::getInstance().load();
    Scoring::getInstance().load();

    if (engine.initialize() == false) {
      return (EXIT_FAILURE);
    }

    while (engine.update() == true)
      engine.draw();

    // Saving statics and singletons classes
    Configuration::save();
    Scoring::getInstance().save();
  }
  catch(std::exception& ex) {
    std::cerr << "[EXCEPTION] " << ex.what() << std::endl;
  }



  return EXIT_SUCCESS;
}
