/*
** Manager.hh for Bomberman in /home/raphy/Epitech/Tech_2/bomberman/src/API
**
** Made by raphael defreitas
** Login   <defrei_r@epitech.net>
**
** Started on  Thu Jun 05 10:38:15 2014 raphael defreitas
// Last update Thu Jun  5 12:40:52 2014 raphael defreitas
*/

#ifndef		MANAGER_HH_
# define	MANAGER_HH_

# include	"Lua/Script.hh"

using namespace Lua;

namespace API
{
  class Manager
  {
  public:
    static Manager& getInstance(void);

    bool registerScript(Script& script);

  private:
    Manager(void);
    ~Manager(void);

    static Manager _instance;
  };
}

#endif /* !MANAGER_HH_*/
