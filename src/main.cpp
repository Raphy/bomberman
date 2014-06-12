#include <OpenGL.hh>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <cstdlib>
#include <string>

#include <unistd.h>
#include <iostream>
#include <exception>

#include "GameEngine.hh"
#include "ResourcesPath.hh"

int main()
{
    ResourcesPath::setRootDir("./build");
    
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
