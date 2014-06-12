#include <OpenGL.hh>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <cstdlib>
#include <string>

#include <unistd.h>
#include <iostream>
#include <exception>

#include "GameEngine.hh"

int main(__attribute__((unused))int argc, char** argv)
{
  // Calculating the base_path
  std::string base_path("./");
  std::string arg0(argv[0]);
  size_t pos = std::string::npos;
  if ((pos = arg0.find_last_of("/")) != std::string::npos)
    base_path = arg0.substr(0, pos + 1);

  // à partir de là, base_path est valide
  try {
        GameEngine engine;

         if (engine.initialize() == false) {
            return (EXIT_FAILURE);
        }

        while (engine.update() == true) {
            engine.draw();
        }
    }
    catch(std::exception& ex) {
        std::cerr << "[EXCEPTION] " << ex.what() << std::endl;
    }

  return EXIT_SUCCESS;
}
