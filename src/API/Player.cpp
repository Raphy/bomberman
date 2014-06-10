//
// Player.cpp for Bomberman in /home/raphy/Epitech/Tech_2/bomberman/src/API
// 
// Made by raphael defreitas
// Login   <defrei_r@epitech.net>
// 
// Started on  Tue Jun  3 12:02:27 2014 raphael defreitas
// Last update Wed Jun 11 01:41:32 2014 raphael defreitas
//

#include	<lua.hpp>
#include	<string>

#include	"GameObject.hh"
#include	"Lua/Script.hh"
#include	"Player.hh"

using namespace API;
using namespace Lua;

Player::Player(const std::string& name, float x, float y) :
  GameObject::GameObject(x, y), _name(name)
{
  this->_type = "Player";
}

Player::~Player(void)
{
}

const std::string& Player::getName(void) const
{
  return this->_name;
}

void Player::registerScript(Script& script)
{
  luaL_newmetatable(script.getVirtualMachine().getState(), "luaL_Player");

    luaL_Reg meta[] =
      {
	{"new", Player::ctor},
	{"__gc", Player::dtor},
	{NULL, NULL}
      };
    luaL_setfuncs(script.getVirtualMachine().getState(), meta, 0);
    Player::registerMethods(script);

    lua_pushvalue(script.getVirtualMachine().getState(), -1);
    lua_setfield(script.getVirtualMachine().getState(), -1, "__index");
    lua_setglobal(script.getVirtualMachine().getState(), "Player");
}

void Player::registerMethods(Script& script)
{
  GameObject::registerMethods(script);
  luaL_Reg methods[] =
    {
      {"getName", Player::getName},
      {NULL, NULL}
    };
  luaL_setfuncs(script.getVirtualMachine().getState(), methods, 0);
}

int Player::ctor(lua_State* L)
{
  const char* name = luaL_checkstring(L, 2);
  float x = luaL_checknumber(L, 3);
  float y = luaL_checknumber(L, 4);
  Player** udata = (Player**)lua_newuserdata(L, sizeof(Player*));
  *udata = new Player(std::string(name), x, y);
  luaL_getmetatable(L, "luaL_Player");
  lua_setmetatable(L, -2);
  return 1;
}

int Player::dtor(lua_State* L)
{
  Player* udata = *(Player**)lua_touserdata(L, 1);
  delete udata;
  return 0;
}

int Player::getName(lua_State* L)
{
  Player* udata = *(Player**)lua_touserdata(L, 1);
  lua_pushstring(L, udata->getName().c_str());
  return 1;
}
