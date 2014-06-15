//
// Configuration.cpp for Bomberman in /home/raphy/Epitech/Tech_2/bomberman/src
// 
// Made by raphael defreitas
// Login   <defrei_r@epitech.net>
// 
// Started on  Sun Jun 15 02:19:52 2014 raphael defreitas
// Last update Sun Jun 15 06:06:15 2014 raphael defreitas
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
  std::ifstream ifs(config_file);
  if (ifs.good())
    {
      std::string line;
      while (std::getline(ifs, line))
	_parseConfigLine(line);
      ifs.close();
    }
}

void Configuration::save(void)
{
  std::string config_file = ResourcesPath::root("configuration.conf");
  std::ofstream ofs(config_file);
  if (ofs.good())
    {
      for (std::map<std::string, std::string>::iterator it = _variables.begin(); it != _variables.end(); it++)
	ofs << it->first << "=" << it->second << std::endl;
    }
  ofs.close();
}

Configuration::~Configuration(void)
{
}

void Configuration::_parseConfigLine(const std::string& line)
{
  size_t pos = line.find('=');
  if (pos == std::string::npos)
    return;
  std::string name = line.substr(0, pos);
  std::string value = line.substr(pos + 1);
  _setVariable(name, value);
}

void Configuration::_setVariable(const std::string& name, const std::string& value)
{
  _variables[name] = value;
}
