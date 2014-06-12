//
// Map.cpp for Bomberman in /home/raphy/Epitech/Tech_2/bomberman/src/API
// 
// Made by raphael defreitas
// Login   <defrei_r@epitech.net>
// 
// Started on  Tue Jun  3 12:12:44 2014 raphael defreitas
// Last update Thu Jun 12 20:26:35 2014 raphael defreitas
//

#include	<cstring>
#include	<iostream>
#include	<typeinfo>

#include	"GameObject.hh"
#include	"Map.hh"
#include	"Player.hh"

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
  /*objects.push_back(new GameObject(1.1, 2.2));
  objects.push_back(new Player("Player1", 3.3, 4.4));
  objects.push_back(new Player("Player2", 5.5, 6.6));*/
  return objects;
}

void Map::registerScript(Script& script)
{
  luaL_newmetatable(script.getVirtualMachine().getState(), "luaL_Map");
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
      {"free", Map::free},
      {NULL, NULL}
    };
  luaL_setfuncs(script.getVirtualMachine().getState(), methods, 0);
}

int Map::get(lua_State* L)
{
  VirtualMachine vm(L);
  Map* udata = vm.toClass<Map>();
  int x = luaL_checkinteger(L, 2);
  int y = luaL_checkinteger(L, 3);
  int distance = luaL_checkinteger(L, 4);

  std::vector<GameObject*> vec = udata->get(x, y, distance);

  lua_newtable(vm.getState());
  int i = 0;
  for(std::vector<GameObject*>::iterator it = vec.begin(); it != vec.end(); it++, i++)
    {
      std::string tname("luaL_" + (*it)->getType());
      GameObject** udata = (GameObject**)lua_newuserdata(L, sizeof(GameObject*));
      *udata = *it;
      luaL_getmetatable(L, tname.c_str());
      lua_setmetatable(L, -2);
      lua_rawseti(vm.getState(), -2, i + 1);
    }
  return 1;
}

int Map::free(lua_State* L)
{
  VirtualMachine vm(L);
  luaL_checktype (vm.getState(), 2, LUA_TTABLE);

  int size = luaL_len(L, 2);

  for (int i = 0; i < size; i++)
    {
      lua_rawgeti(L, 2, i + 1);
      int top = lua_gettop(L);
      GameObject* udata = *(GameObject**)lua_touserdata(L, top);
      delete udata;
      lua_pop(L, 1);
    }

  return 0;
}
