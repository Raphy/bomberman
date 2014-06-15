//
// Map.cpp for Bomberman in /home/raphy/Epitech/Tech_2/bomberman/src/API
// 
// Made by raphael defreitas
// Login   <defrei_r@epitech.net>
// 
// Started on  Tue Jun  3 12:12:44 2014 raphael defreitas
// Last update Sun Jun 15 21:32:45 2014 raphael defreitas
//

#include	<cstring>
#include	<iostream>
#include	<typeinfo>
#include	<list>
#include	<vector>

#include	"Bomb.hh"
#include	"BombCapacityBuff.hh"
#include	"BombRangeBuff.hh"
#include	"Box.hh"
#include	"Fire.hh"
#include	"game/Rectangle.hh"
#include	"game/GameAPI.hh"
#include	"GameObject.hh"
#include	"Map.hh"
#include	"Me.hh"
#include	"object/AGameObject.hh"
#include	"object/Bomb.hh"
#include	"object/Box.hh"
#include	"object/IA.hh"
#include	"object/Marvin.hh"
#include	"object/Wall.hh"
#include	"Player.hh"
#include	"SpeedBuff.hh"
#include	"Wall.hh"

using namespace API;

Map::Map(void)
{
}

Map::~Map(void)
{
}

std::vector<GameObject*> Map::get(int x, int y, int d, Me* me)
{
  std::vector<GameObject*> objects;
  std::list<AGameObject*> list_go;

  // Retrieveing the objects from the map
  Rectangle rect((double)x - (double)d, (double)y - (double)d, (double)d * 2, (double)d * 2);
  GameAPI::getInstance().getObjectsIn(rect, list_go);

  // Creating our own vector of API::GameObjects
  for (std::list<AGameObject*>::iterator it = list_go.begin(); it != list_go.end(); it++)
    {
      if ((*it)->getType() == "player1" || (*it)->getType() == "player2")
	objects.push_back(new Player((Marvin*)*it));
      else if ((*it)->getType() == "wall")
	objects.push_back(new API::Wall((::Wall*)*it));
      else if ((*it)->getType() == "ia" && *it == me->getAGameObject())
	objects.push_back(new Me((IA*)*it));
      else if ((*it)->getType() == "ia")
	objects.push_back(new Player((Marvin*)*it));
      else if ((*it)->getType() == "bomb")
	objects.push_back(new API::Bomb((::Bomb*)*it));
      else if ((*it)->getType() == "box")
	objects.push_back(new API::Box((::Box*)*it));
      else if ((*it)->getType() == "fire")
	objects.push_back(new API::Fire((::Fire*)*it));
      else if ((*it)->getType() == "speed_buff")
	{
	  objects.push_back(new API::SpeedBuff((::SpeedBuff*)*it));
	  objects.push_back(new Item((AGameObject*)*it));
	}
      else if ((*it)->getType() == "bomb_capacity_buff")
	{
	  objects.push_back(new API::BombCapacityBuff((::BombCapacityBuff*)*it));
	  objects.push_back(new Item((AGameObject*)*it));
	}
      else if ((*it)->getType() == "bomb_range_buff")
	{
	  objects.push_back(new API::BombRangeBuff((::BombRangeBuff*)*it));
	  objects.push_back(new Item((AGameObject*)*it));
	}
    }

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
      {"getSize", Map::getSize},
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
  Me* me = *(Me**)luaL_checkudata(L, 5, "luaL_Me");

  std::vector<GameObject*> vec = udata->get(x, y, distance, me);

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

int Map::getSize(lua_State* L)
{
  VirtualMachine vm(L);
  std::tuple<double, double> size = GameAPI::getInstance().getMapSize();
  lua_pushnumber(L, std::get<0>(size));
  lua_pushnumber(L, std::get<1>(size));
  return 2;
}

