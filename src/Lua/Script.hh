/*
** Script.hh for Bomberman in /home/raphy/Epitech/Tech_2/bomberman/src/Lua
**
** Made by raphael defreitas
** Login   <defrei_r@epitech.net>
**
** Started on  Tue Jun 03 12:35:28 2014 raphael defreitas
// Last update Thu Jun  5 13:59:19 2014 raphael defreitas
*/

#ifndef		SCRIPT_HH_
# define	SCRIPT_HH_

# include	<lua.hpp>

# include	"VirtualMachine.hh"

namespace Lua
{
  class Script
  {
  public:
    Script(const std::string& filename);
    ~Script(void);

    VirtualMachine& getVirtualMachine(void);

    bool execute(void);
    bool initialization(void);
    bool play(void);

  protected:
    VirtualMachine _vm;
  };
}

#endif /* !SCRIPT_HH_*/
