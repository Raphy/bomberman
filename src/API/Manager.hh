/*
** Manager.hh for Bomberman in /home/raphy/Epitech/Tech_2/bomberman/src/API
**
** Made by raphael defreitas
** Login   <defrei_r@epitech.net>
**
** Started on  Thu Jun 05 10:38:15 2014 raphael defreitas
// Last update Sun Jun 15 01:58:36 2014 raphael defreitas
*/

#ifndef		API_MANAGER_HH_
# define	API_MANAGER_HH_

# include	"game/GameScene.hh"
# include	"Lua/Script.hh"
# include	"object/IA.hh"

using namespace Lua;

namespace API
{
  class Manager
  {
  public:
    static Manager& getInstance(void);

    void registerScript(Script& script);
    void registerMe(Script& script, IA* ia);
    void registerMap(GameScene* gs);

  private:
    Manager(void);
    ~Manager(void);

    static Manager _instance;
    GameScene* _gs;
  };
}

#endif /* !API_MANAGER_HH_*/
