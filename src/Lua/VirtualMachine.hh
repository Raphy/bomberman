/*
** VirtualMachine.hh for Bomberman in /home/raphy/Epitech/Tech_2/bomberman/src/Lua
**
** Made by raphael defreitas
** Login   <defrei_r@epitech.net>
**
** Started on  Tue Jun 03 11:42:59 2014 raphael defreitas
// Last update Wed Jun 11 12:30:15 2014 raphael defreitas
*/

#ifndef		VIRTUALMACHINE_HH_
# define	VIRTUALMACHINE_HH_

# include	<string>
# include	<stdexcept>
# include	<vector>

# include	"lua.hpp"

namespace Lua
{
  class VirtualMachine
  {
  public:
    VirtualMachine(void);
    ~VirtualMachine(void);

    void clean(void);

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
	  this->clean();
	  return result;
	}
      throw new std::runtime_error("LuaVariableNotExistsException: " + name); // Exception: LuaVariableNotExistsException
    }

    template<typename T>
    void set(const std::string& name, T value)
    {
      // See specializations
      throw new std::runtime_error("LuaTypeNotImplementedException"); // Type not implemented
    }

    template<class T>
    T* getClass(const std::string& name)
    {
      T* result;
      if(this->_variableExists(name))
	{
	  result = *(T**)lua_touserdata(this->_state, 1);
	  this->clean();
	  return result;
	}
      throw new std::runtime_error("LuaVariableNotExistsException: " + name); // Exception: LuaVariableNotExistsException
    }

    template<class T>
    void setClass(const std::string& tname, const std::string& name, T* data)
    {
      T** udata = this->_newClass<T>();
      *udata = data;
      luaL_setmetatable(this->_state, tname.c_str());
      lua_setglobal(this->_state, name.c_str());
    }

  protected:
    lua_State* _state;

    bool _variableExists(const std::string& name);

    template<typename T>
    T _get()
    {
      // See specializations
      throw new std::runtime_error("LuaTypeNotImplementedException"); // Type not implemented
    }

    template<class T>
    T** _newClass()
    {
      T** result = (T**)lua_newuserdata(this->_state, sizeof(T*));
      return result;
    }
  };

  /*
  ** VirtualMachine::_get specializations
  */
  template<>
  inline bool VirtualMachine::_get<bool>()
  {
    if(!lua_isboolean(this->_state, -1))
      throw new std::runtime_error("LuaVariableIsNotBooleanException"); // Exception: LuaVariableIsNotBooleanException
    return (bool)lua_toboolean(this->_state, -1);
  }

  template <>
  inline float VirtualMachine::_get<float>()
  {
    if(!lua_isnumber(this->_state, -1))
      throw new std::runtime_error("LuaVariableIsNotFloatException"); // Exception: LuaVariableIsNotFloatException
    return (float)lua_tonumber(this->_state, -1);
  }

  template <>
  inline int VirtualMachine::_get<int>()
  {
    if(!lua_isnumber(this->_state, -1))
      throw new std::runtime_error("LuaVariableIsNotIntException"); // Exception: LuaVariableIsNotIntException
    return (int)lua_tonumber(this->_state, -1);
  }

  template <>
  inline std::string VirtualMachine::_get<std::string>()
  {
    if(!lua_isstring(this->_state, -1))
      throw new std::runtime_error("LuaVariableIsNotStringException"); // Exception: LuaVariableIsNotStringException
    return std::string(lua_tostring(this->_state, -1));
  }

  /*
  ** VirtualMachine::set specializations
  */
  template<>
  inline void VirtualMachine::set<bool>(const std::string& name, bool value)
  {
    lua_pushboolean(this->_state, value ? 1 : 0);
    lua_setglobal(this->_state, name.c_str());
  }

  template <>
  inline void VirtualMachine::set<float>(const std::string& name, float value)
  {
    lua_pushnumber(this->_state, value);
    lua_setglobal(this->_state, name.c_str());
  }

  template <>
  inline void VirtualMachine::set<int>(const std::string& name, int value)
  {
    lua_pushinteger(this->_state, value);
    lua_setglobal(this->_state, name.c_str());
  }

  template <>
  inline void VirtualMachine::set<std::string>(const std::string& name, std::string value)
  {
    lua_pushstring(this->_state, value.c_str());
    lua_setglobal(this->_state, name.c_str());
  }
}

#endif /* !VIRTUALMACHINE_HH_*/
