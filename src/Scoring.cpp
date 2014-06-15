//
// Scoring.cpp for Bomberman in /home/raphy/Epitech/Tech_2/bomberman/src
// 
// Made by raphael defreitas
// Login   <defrei_r@epitech.net>
// 
// Started on  Sun Jun 15 11:50:38 2014 raphael defreitas
// Last update Sun Jun 15 13:06:17 2014 raphael defreitas
//

#include	<iostream>
#include	<fstream>
#include	<list>
#include	<sstream>
#include	<string>

#include	"ResourcesPath.hh"
#include	"Scoring.hh"

Scoring Scoring::_instance = Scoring();

Scoring::Scoring(void) :
  _score_p1(0), _score_p2(0)
{
}

Scoring::~Scoring(void)
{
}

Scoring& Scoring::getInstance(void)
{
  return _instance;
}

void Scoring::load(void)
{
  this->_loadFileToList("scores_player_1.conf", this->_scores_p1);
  this->_loadFileToList("scores_player_2.conf", this->_scores_p2);
}

void Scoring::save(void)
{
  this->_saveListToFile(this->_scores_p1, "scores_player_1.conf");
  this->_saveListToFile(this->_scores_p2, "scores_player_2.conf");
}

void Scoring::incrP1(unsigned int value)
{
  this->_score_p1 += value;
}

void Scoring::incrP2(unsigned int value)
{
  this->_score_p2 += value;
}

void Scoring::flush(void)
{
  this->addScoreP1(this->_score_p1);
  this->addScoreP2(this->_score_p2);
  this->_score_p1 = 0;
  this->_score_p2 = 0;
}

void Scoring::addScoreP1(unsigned int score)
{
  this->_addScore(this->_scores_p1, score);
}

void Scoring::addScoreP2(unsigned int score)
{
  this->_addScore(this->_scores_p1, score);
}

const std::list<unsigned int>& Scoring::getScoresP1(void) const
{
  return this->_scores_p1;
}

const std::list<unsigned int>& Scoring::getScoresP2(void) const
{
  return this->_scores_p2;
}

void Scoring::_addScore(std::list<unsigned int>& scores, unsigned int score)
{
  if (score == 0)
    return;
  scores.push_back(score);
  scores.unique();
  scores.sort();
  if (scores.size() > 5)
    scores.pop_back();
  std::cout << std::endl;
}

void Scoring::_loadFileToList(const std::string& file, std::list<unsigned int>& scores)
{
  std::string scores_file = ResourcesPath::root(file);
  std::ifstream ifs(scores_file);
  if (ifs.good())
    {
      std::string line;
      while (std::getline(ifs, line))
	{
	  unsigned int score;
	  std::stringstream ss(line);
	  ss >> score;
	  this->_addScore(scores, score);
	}
    }
  ifs.close();
  scores.sort();
}

void Scoring::_saveListToFile(std::list<unsigned int>& scores, const std::string& file)
{
  std::string scores_file = ResourcesPath::root(file);
  std::ofstream ofs(scores_file);
  if (ofs.good())
    for(std::list<unsigned int>::iterator it = scores.begin(); it != scores.end(); it++)
      ofs << *it << std::endl;
  ofs.close();
}
