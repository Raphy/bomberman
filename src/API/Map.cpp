//
// Map.cpp for Bomberman in /home/raphy/Epitech/Tech_2/bomberman/src/API
// 
// Made by raphael defreitas
// Login   <defrei_r@epitech.net>
// 
// Started on  Tue Jun  3 12:12:44 2014 raphael defreitas
// Last update Wed Jun 11 18:33:20 2014 raphael defreitas
//

#include	"Map.hh"

using namespace API;

Map::Map(void)
{
}

Map::~Map(void)
{
}

std::vector<GameObject*> Map::get(int x, int y, int distance)
{
  std::vector<GameObject*> objects;
  // ToDo : Fill the vector with the corrects GameObjects ;)
  return objects;
}

void Map::registerScript(Script& script)
{
  luaL_newmetatable(script.getVirtualMachine().getState(), "luaL_Map");

  /*luaL_Reg meta[] =
      {
	{"new", Map::ctor},
	{"__gc", Map::dtor},
	{NULL, NULL}
      };
      luaL_setfuncs(script.getVirtualMachine().getState(), meta, 0);*/
    Map::registerMethods(script);

    lua_pushvalue(script.getVirtualMachine().getState(), -1);
    lua_setfield(script.getVirtualMachine().getState(), -1, "__index");
    lua_setglobal(script.getVirtualMachine().getState(), "Map");
}

void Map::registerMethods(Script& script)
{
  luaL_Reg methods[] =
    {
      {"get", Map::get},
      {NULL, NULL}
    };
  luaL_setfuncs(script.getVirtualMachine().getState(), methods, 0);
}

int Map::ctor(lua_State* L)
{
  Map** udata = (Map**)lua_newuserdata(L, sizeof(Map*));
  *udata = new Map();
  luaL_getmetatable(L, "luaL_Map");
  lua_setmetatable(L, -2);
  return 1;
}

int Map::dtor(lua_State* L)
{
  Map* udata = *(Map**)lua_touserdata(L, 1);
  delete udata;
  return 0;
}

int Map::get(lua_State* L)
{
  Map* udata = *(Map**)lua_touserdata(L, 1);
  // ToDo: setVector<GameObject> ...
  return 1;
}

