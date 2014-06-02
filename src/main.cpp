
#include <OpenGL.hh>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <cstdlib>
#include "Wall.hh"
#include "GameEngine.hpp"

int main()
{
    GameEngine engine;

    if (engine.initialize() == false) {
        return (EXIT_FAILURE);
    }

    while (engine.update() == true) {
        engine.draw();
    }

    return EXIT_SUCCESS;
}


//~ Formatted by Jindent --- http://www.jindent.com
