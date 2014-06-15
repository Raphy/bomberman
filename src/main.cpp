#include <OpenGL.hh>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <cstdlib>
#include <string>
#include <ctime>

#include <unistd.h>
#include <iostream>
#include <sstream>
#include <exception>

#include "GameEngine.hh"
#include "ResourcesPath.hh"
#include "Configuration.hh"
#include "SoundManager.hh"
#include "Scoring.hh"

SceneArguments& getArgs(int argc, char** argv)
{
  SceneArguments args;

  /*if (argc == 4)
    {
      args.set("width", std::string(argv[1]));
      args.set("height", std::string(argv[2]));
      args.set("ia", std::string(argv[3]));
    }
  else if (argc > 1)
    {
      std::cerr << "Random map generation: " << argv[0] << " <width> <height> <ia>" << std::endl;
      }*/
  return args;
}

int main(int argc, char** argv)
{
  ResourcesPath::setRootDir("./build");

  // Initialization of the random system
  srand(time(NULL));

  // Random generation arguments
  SceneArguments args;
  if (argc == 4)
    {
      args.set("width", std::string(argv[1]));
      args.set("height", std::string(argv[2]));
      args.set("ia", std::string(argv[3]));
    }
  else if (argc > 1)
    {
      std::cerr << "Random map generation: " << argv[0] << " <width> <height> <ia>" << std::endl;
    }
  else
    {
      // Setting the default arguments for random generation
      std::stringstream ss;

      int width = 20 + rand() % 31; // Between 20-50
      ss << width;
      args.set("width", ss.str());
      ss.str("");
      ss.clear();

      int height = 20 + rand() % 31; // Between 20-50
      ss << height;
      args.set("height", ss.str());
      ss.str("");
      ss.clear();

      int ia = 1 + rand() % 3; // Between 1-3
      ss << ia;
      args.set("ia", ss.str());
      ss.str("");
      ss.clear();
    }

  try {
    GameEngine engine;

    // Loading statics and singletons classes
    Configuration::load();
    SoundManager::getInstance().load();
    Scoring::getInstance().load();

    engine.setArgs(args);
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
