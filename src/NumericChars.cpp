//
// NumericChars.cpp for Bomberman in /home/raphy/Epitech/Tech_2/bomberman/src
// 
// Made by raphael defreitas
// Login   <defrei_r@epitech.net>
// 
// Started on  Sun Jun 15 19:51:05 2014 raphael defreitas
// Last update Sun Jun 15 20:13:47 2014 raphael defreitas
//

#include	"NumericChars.hh"
#include	"ResourcesPath.hh"

NumericChars NumericChars::_instance = NumericChars();

NumericChars::NumericChars()
{
}

NumericChars::~NumericChars()
{
}

void NumericChars::load(void)
{
  this->_textures[0] = ResourcesPath::asset("img/alpha/0.tga");
  this->_textures[1] = ResourcesPath::asset("img/alpha/1.tga");
  this->_textures[2] = ResourcesPath::asset("img/alpha/2.tga");
  this->_textures[3] = ResourcesPath::asset("img/alpha/3.tga");
  this->_textures[4] = ResourcesPath::asset("img/alpha/4.tga");
  this->_textures[5] = ResourcesPath::asset("img/alpha/5.tga");
  this->_textures[6] = ResourcesPath::asset("img/alpha/6.tga");
  this->_textures[7] = ResourcesPath::asset("img/alpha/7.tga");
  this->_textures[8] = ResourcesPath::asset("img/alpha/8.tga");
  this->_textures[9] = ResourcesPath::asset("img/alpha/9.tga");
}

NumericChars& NumericChars::getInstance()
{
  return _instance;
}

std::stack<std::string> NumericChars::getTextures(unsigned int number)
{
  std::stack<std::string> textures;

  if (number == 0)
    textures.push(this->_textures[0]);
  else
    {
      while (number > 0)
	{
	  unsigned int num = number % 10;
	  textures.push(this->_textures[num]);
	  number /= 10;
	}
    }

  return textures;
}
