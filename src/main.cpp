//
// main.cpp for Bomberman in /home/raphy/Epitech/Tech_2/bomberman/src
// 
// Made by raphael defreitas
// Login   <defrei_r@epitech.net>
// 
// Started on  Wed May 28 17:17:07 2014 raphael defreitas
// Last update Wed May 28 18:02:17 2014 raphael defreitas
//

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
