/*
** VirtualMachine.hh for Bomberman in /home/raphy/Epitech/Tech_2/bomberman/src/Lua
**
** Made by raphael defreitas
** Login   <defrei_r@epitech.net>
**
** Started on  Tue Jun 03 11:42:59 2014 raphael defreitas
// Last update Thu Jun  5 14:03:22 2014 raphael defreitas
*/

#ifndef		VIRTUALMACHINE_HH_
# define	VIRTUALMACHINE_HH_

# include	<exception>
# include	<string>
# include	<vector>

# include	"lua.hpp"

namespace Lua
{
  class VirtualMachine
  {
  public:
    VirtualMachine(void);
    ~VirtualMachine(void);

    lua_State* getState(void);
    std::string getError(void);
    void setError(const std::string& error);

    bool loadFile(const std::string& filename);
    bool execute(void);
    bool call(const std::string& name);

    template<typename T>
    T get(const std::string& name)
    {
      T result;
      if(this->_variableExists(name))
	{
	  result =  this->_get<T>();
	  lua_pop(this->_state, lua_gettop(this->_state)); // Clean the Lua stack
	  return (result);
	}
      throw new std::exception(); // Exception: LuaVariableNotExistsException
    }

    template<class T>
    T getClass(const std::string& name)
    {
      throw new std::exception(); // ToDo: implement the method
    }

    template<class T>
    std::vector<T> getVector(const std::string& name)
    {
      throw new std::exception(); // ToDo: implement the method
    }

    template<typename T>
    void set(const std::string& name, T value)
    {
      throw new std::exception(); // Type not implemented
    }

    template<class T>
    void setClass(const std::string& name, T& value)
    {
      throw new std::exception(); // ToDo: implement the method
    }

    template<class T>
    void setVector(const std::string& name, std::vector<T>& value)
    {
      throw new std::exception(); // ToDo: implement the method
    }

  protected:
    lua_State* _state;

    bool _variableExists(const std::string& name);

    template<typename T>
    T _get()
    {
      throw new std::exception(); // Type not implemented
    }
  };

  /*
  ** VirtualMachine::_get specializations
  */
  template<>
  inline bool VirtualMachine::_get<bool>()
  {
    if(!lua_isboolean(this->_state, -1))
      throw new std::exception(); // Exception: LuaVariableIsNotBooleanException
    return (bool)lua_toboolean(this->_state, -1);
  }

  template <>
  inline float VirtualMachine::_get<float>()
  {
    if(!lua_isnumber(this->_state, -1))
      throw new std::exception(); // Exception: LuaVariableIsNotFloatException
    return (float)lua_tonumber(this->_state, -1);
  }

  template <>
  inline int VirtualMachine::_get<int>()
  {
    if(!lua_isnumber(this->_state, -1))
      throw new std::exception(); // Exception: LuaVariableIsNotIntException
    return (int)lua_tonumber(this->_state, -1);
  }

  template <>
  inline std::string VirtualMachine::_get<std::string>()
  {
    if(!lua_isstring(this->_state, -1))
      throw new std::exception(); // Exception: LuaVariableIsNotStringException
    return (std::string(lua_tostring(this->_state, -1)));
  }

  /*
  ** VirtualMachine::_set specializations
  */
}

#endif /* !VIRTUALMACHINE_HH_*/
