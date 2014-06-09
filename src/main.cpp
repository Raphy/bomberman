#include	<cstdlib>
#include	<iostream>

#include "GameEngine.hh"

int main(int ac, char **av) {

    GameEngine engine;

    if (!engine.initialize()) {
      std::cerr << "error: fail to initialize game engine" << std::endl;
      return EXIT_FAILURE;
    }

    while (engine.update()) {
      engine.draw();
    }

    return EXIT_SUCCESS;
}

/*
#include "API/Manager.hh"
#include "Lua/Script.hh"
int main(int argc, char** argv)
{
  if (argc == 1)
    {
      std::cerr << "Usage: " << argv[0] << " <script lua>" << std::endl;
      return (EXIT_FAILURE);
    }

  Lua::Script ia(argv[1]);
  API::Manager& api_manager = API::Manager::getInstance();

  api_manager.registerScript(ia);

  try
    {

      if (!ia.execute())
	std::cerr << "[LUA ERROR Exec] " << ia.getVirtualMachine().getError() << std::endl;
      if (!ia.initialization())
	std::cerr << "[LUA ERROR] " << ia.getVirtualMachine().getError() << std::endl;
      if (!ia.play())
	std::cerr << "[LUA ERROR] " << ia.getVirtualMachine().getError() << std::endl;

      int x = ia.getVirtualMachine().get<int>("x");

      std::cout << "x=" << x << std::endl;
    }
  catch (std::exception* ex)
    {
      std::cerr << "[EXCEPTION] " << ex->what() << std::endl;
      return (EXIT_FAILURE);
    }

  return EXIT_SUCCESS;
}
*/


/*
//* Graph main
#include <OpenGL.hh>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <cstdlib>

#include "GameEngine.hh"
#include "Wall.hh"

#include <unistd.h>

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
*/

//*

/* LUA main
#include	<cstdlib>
#include	<exception>
#include	<iostream>

#include	"API/Me.hh"
#include	"Lua/Script.hh"

int main(int argc, char** argv)
{
  if (argc == 1)
    {
      std::cerr << "Usage: " << argv[0] << " <script lua>" << std::endl;
      return (EXIT_FAILURE);
    }

  try
    {
      // Creating the script object from the specified script file
      Lua::Script script(argv[1]);

      // Registering the API
      API::Me::luaRegister(script);
      API::Me **me = static_cast<API::Me **>(lua_newuserdata(script.getState(), sizeof(API::Me *)) );
      (*me) = new API::Me("Raphy", 42.1, 21.0);

      luaL_setmetatable(script.getState(), "Me");
      lua_setglobal(script.getState(), "me");

      // Running the script
      if (!script.run())
	{
	  std::cerr << "[LUA ERROR] " << script.getError() << std::endl;
	  return (EXIT_FAILURE);
	}
    }
    catch (std::exception& ex)
    {
      std::cerr << "[EXCEPTION] " << ex.what() << std::endl;
      return (EXIT_FAILURE);
    }

  return (EXIT_SUCCESS);
}
//*/
