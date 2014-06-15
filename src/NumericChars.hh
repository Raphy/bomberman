/*
** NumericChars.hh for Bomberman in /home/raphy/Epitech/Tech_2/bomberman/src
**
** Made by raphael defreitas
** Login   <defrei_r@epitech.net>
**
** Started on  Sun Jun 15 19:50:55 2014 raphael defreitas
// Last update Sun Jun 15 20:07:46 2014 raphael defreitas
*/

#ifndef		NUMERICCHARS_HH_
# define	NUMERICCHARS_HH_

# include	<list>
# include	<string>
# include	<stack>

class NumericChars
{
public:
  static NumericChars& getInstance();

  std::stack<std::string> getTextures(unsigned int number);

private:
  NumericChars();
  ~NumericChars();

  static NumericChars _instance;

  std::string _textures[10];
};

#endif /* !NUMERICCHARS_HH_*/
