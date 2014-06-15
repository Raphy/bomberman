/*
** Configuration.hh for Bomberman in /home/raphy/Epitech/Tech_2/bomberman/src
**
** Made by raphael defreitas
** Login   <defrei_r@epitech.net>
**
** Started on  Sun Jun 15 02:19:46 2014 raphael defreitas
// Last update Sun Jun 15 05:17:01 2014 raphael defreitas
*/

#ifndef		CONFIGURATION_HH_
# define	CONFIGURATION_HH_

# include	<iostream>
# include	<map>
# include	<sstream>
# include	<stdexcept>
# include	<string>

# include	"Exception.hh"

class Configuration
{
public:
  static void load(void);
  static void save(void);

  template<typename T>
  static void set(const std::string& name, T value)
  {
    std::stringstream ss;
    ss << value;
    _setVariable(name, ss.str());
  }

  template<typename T>
  static T get(const std::string& name)
  {
    if (_variables.find(name) == _variables.end())
      throw Exception("Variable " + name + " not exists (maybe not default value set ?)");
    std::stringstream ss(_variables[name]);
    T value;
    ss >> value;
    return value;
  }

private:
  Configuration(void);
  ~Configuration(void);

  static std::map<std::string, std::string> _variables;

  static void _parseConfigLine(const std::string& line);
  static void _setVariable(const std::string& name, const std::string& value);
};

#endif /* !CONFIGURATION_HH_*/
