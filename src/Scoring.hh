/*
** Scoring.hh for Bomberman in /home/raphy/Epitech/Tech_2/bomberman/src
**
** Made by raphael defreitas
** Login   <defrei_r@epitech.net>
**
** Started on  Sun Jun 15 11:49:50 2014 raphael defreitas
// Last update Sun Jun 15 13:25:38 2014 raphael defreitas
*/

#ifndef		SCORING_HH_
# define	SCORING_HH_

# include	<list>
# include	<string>

class Scoring
{
public:
  static Scoring& getInstance(void);

  void load(void);
  void save(void);

  void incrP1(unsigned int value = 1);
  void incrP2(unsigned int value = 1);
  unsigned int getScoreP1(void) const;
  unsigned int getScoreP2(void) const;
  void flush(void);
  void addScoreP1(unsigned int score);
  void addScoreP2(unsigned int score);
  const std::list<unsigned int>& getScoresP1(void) const;
  const std::list<unsigned int>& getScoresP2(void) const;

private:
  Scoring(void);
  ~Scoring(void);

  static Scoring _instance;

  unsigned int _score_p1;
  unsigned int _score_p2;
  std::list<unsigned int> _scores_p1;
  std::list<unsigned int> _scores_p2;

  void _addScore(std::list<unsigned int>& scores, unsigned int score);
  void _loadFileToList(const std::string& file, std::list<unsigned int>& scores);
  void _saveListToFile(std::list<unsigned int>& scores, const std::string& file);
};

#endif /* !SCORE_HH_*/
