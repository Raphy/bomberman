/*
** Script.hh for Bomberbam in /home/raphy/Epitech/Tech_2/bomberman/src/Lua
**
** Made by raphael defreitas
** Login   <defrei_r@epitech.net>
**
** Started on  Tue May 27 17:57:46 2014 raphael defreitas
// Last update Wed May 28 15:44:58 2014 raphael defreitas
*/

#ifndef		SCRIPT_HH_
# define	SCRIPT_HH_

# include	<iostream>
# include	<lua.hpp>
# include	<string>
# include	<vector>

# include	"lua.hpp"

namespace Lua
{
  class Script
  {
  public:
    Script(const std::string& filename);
    Script(lua_State* state);
    ~Script(void);

    lua_State* getState();
    const std::string& getFilename(void) const;

    void setError(const std::string& msg);
    std::string getError(void);

    bool run(void);

    template <typename T>
    T get(const std::string& name)
    {
      T result;
      if(this->_variableExists(name))
	{
	  result =  this->_get<T>();
	  this->_clean();
	  return (result);
	}
      throw new std::exception(); // variable not exists
    }

    template<class T>
    T* getClass(const std::string& name)
    {
      T** obj = static_cast<T **>(luaL_checkudata(this->_state, 1, name.c_str()));
      return (*obj);
    }

    template<typename T>
    std::vector<T> getVector(const std::string& name)
    {
      std::vector<T> result;
      if(this->_variableExists(name))
        {
	  lua_pushnil(this->_state);
	  while (lua_next(this->_state, -2))
	    {
	      result.push_back(this->_get<T>());
	      lua_pop(this->_state, 1);
	    }
          this->_clean();
          return (result);
        }
      throw new std::exception(); // variable not exists
    }

  protected:
    lua_State* _state;
    std::string _filename;
    bool _close;

    bool _variableExists(const std::string& name);
    void _clean();

    template <typename T>
    T _get()
    {
      throw new std::exception(); // type not implemented
    }

  };

  /*
  ** Script::_get<T>() specializations
  **/
  template <>
  inline bool Script::_get<bool>()
  {
    if(!lua_isboolean(this->_state, -1))
      throw new std::exception(); // the variable is not bool
    return (bool)lua_toboolean(this->_state, -1);
  }

  template <>
  inline float Script::_get<float>()
  {
    if(!lua_isnumber(this->_state, -1))
      throw new std::exception(); // the variable is not float
    return (float)lua_tonumber(this->_state, -1);
  }

  template <>
  inline int Script::_get<int>()
  {
    if(!lua_isnumber(this->_state, -1))
      throw new std::exception(); // the variable is not int
    return (int)lua_tonumber(this->_state, -1);
  }

  template <>
  inline std::string Script::_get<std::string>()
  {
    if(!lua_isstring(this->_state, -1))
      throw new std::exception(); // the variable is not string
    return (std::string(lua_tostring(this->_state, -1)));
  }
}

#endif /* !SCRIPT_HH_*/
