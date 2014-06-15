//
// Configuration.cpp for Bomberman in /home/raphy/Epitech/Tech_2/bomberman/src
// 
// Made by raphael defreitas
// Login   <defrei_r@epitech.net>
// 
// Started on  Sun Jun 15 02:19:52 2014 raphael defreitas
// Last update Sun Jun 15 05:02:44 2014 raphael defreitas
//

#include	<iostream>
#include	<fstream>
#include	<string>

#include	"Configuration.hh"
#include	"ResourcesPath.hh"

std::map<std::string, std::string> Configuration::_variables = std::map<std::string, std::string> ();

void Configuration::load(void)
{
  std::string config_file = ResourcesPath::root("configuration.conf");
  std::cout << "Reading " << config_file << std::endl;
  std::ifstream ifs(config_file);
  if (ifs.good())
    {
      std::cout << "File OK" << std::endl;
      std::string line;
      while (std::getline(ifs, line))
	_parseConfigLine(line);
      ifs.close();
    }
  std::cout << "End load" << std::endl;
}

void Configuration::save(void)
{
  std::cout << "Save" << std::endl;
  for (std::map<std::string, std::string>::iterator it = _variables.begin(); it != _variables.end(); it++)
    std::cout << it->first << " <=> " << it->second << std::endl;
}

Configuration::~Configuration(void)
{
}

void Configuration::_parseConfigLine(const std::string& line)
{
  std::cout << "Line: " << line << std::endl;
  size_t pos = line.find('=');
  if (pos == std::string::npos)
    return;
  std::string name = line.substr(0, pos);
  std::string value = line.substr(pos + 1);
  _setVariable(name, value);
}

void Configuration::_setVariable(const std::string& name, const std::string& value)
{
  std::cout << name << " = " << value << std::endl;
  _variables[name] = value;
}
