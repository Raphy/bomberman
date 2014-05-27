/*
** VirtualMachine.hh for bomberman in /home/raphy/Epitech/Tech_2/bomberman/src/Lua
**
** Made by raphael defreitas
** Login   <defrei_r@epitech.net>
**
** Started on  Mon May 26 18:21:39 2014 raphael defreitas
// Last update Mon May 26 19:01:08 2014 raphael defreitas
*/

#ifndef		VIRTUALMACHINE_HH_
# define	VIRTUALMACHINE_HH_

# include	<lua.hpp>
# include	<string>

namespace Lua
{
  class VirtualMachine
  {
  public:
    VirtualMachine(void);
    VirtualMachine(lua_State* L);
    ~VirtualMachine(void);

    void loadLibraries(void);

    std::string getError(void);

    bool runFile(const std::string& filename);
    bool runString(const std::string& str);

  protected:
    lua_State* _L;
  };
}

#endif /* !VIRTUALMACHINE_HH_*/
