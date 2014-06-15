/*
 * File:   MapGenerator.cpp
 * Author: parejo_p
 *
 * Created on 11 June 2014, 19:17
 */

#include <ctime>
#include <cstdlib>
#include <vector>
#include <string>
#include <cmath>
#include <complex>
#include <iostream>
#include <cassert>
#include "MapGenerator.hh"
#include "Wall.hh"
#include "Box.hh"
#include "Exception.hh"

static int const  BRANCHRATE      = -2;    // positive means more branches and negative longer branches
static char const WALL            = '#';
static char const PATH            = ' ';
static char const UNDEFINED       = '?';
static char const TOBEDEFINED     = '!';
static char const DESTRUCTIBLE    = '@';
static int const  DESTRUCTIBILITY = 50; // in percent

MapGenerator::MapGenerator():
    _field(nullptr)
{
    srand(time(NULL));
}

MapGenerator::~MapGenerator(){}

/* MEMBER FUNCTIONS */
std::pair<std::list<AGameObject*>, std::list<AGameObject*>> MapGenerator::Generate(int width, int height)
{
    std::cout << "Generating Map....." << std::endl;
    this -> _width  = width;
    this -> _height = height;
    this -> _field  = new std::vector<std::vector<char> >(this -> _height,
                                      std::vector<char>(this -> _width, UNDEFINED));

    // Start point
    MapGenerator::Dig(rand() % this -> _height, rand() % this -> _width);

    while (this -> _frontier.empty() == false)
    {
        double pos = static_cast<double>(rand()) / static_cast<double>(RAND_MAX);
        assert((pos >= 0) && (pos <= 1));
        pos = static_cast<int>(std::pow(pos, exp(-BRANCHRATE)) * this -> _frontier.size());
        assert((pos >= 0) && (pos < this -> _frontier.size()));

        std::pair<int, int> & choice = this -> _frontier[pos];
        if (MapGenerator::Check(choice.first, choice.second) == true) {
            MapGenerator::Dig(choice.first, choice.second);
        }
        else {
            MapGenerator::Harden(choice.first, choice.second);
        }
        this -> _frontier.erase(this -> _frontier.begin() + pos);
    }
    return MapGenerator::ToList();
}

void MapGenerator::Dig(int y, int x)
{
    (*this -> _field)[y][x] = PATH;
    setExtra(y, x - 1);
    setExtra(y, x + 1);
    setExtra(y - 1, x);
    setExtra(y + 1, x);

    while (this -> _extra.empty() == false)
    {
        int elem = rand() % this -> _extra.size();
        this -> _frontier.push_back(this -> _extra[elem]);
        this -> _extra.erase(this -> _extra.begin() + elem);
    }
}

bool MapGenerator::Check(int y, int x)
{
    std::vector<std::vector<char>> & field = (*this -> _field);

    
    if (((x > 0 && field[y][x - 1] == PATH)
            ^ (x < this -> _width - 1 && field[y][x + 1] == PATH)
            ^ (y > 0 && field[y - 1][x] == PATH)
            ^ (y < this -> _height - 1 && field[y + 1][x] == PATH)) == true) {
        return true;
    }
    return false;
}

void    MapGenerator::Harden(int y, int x)
{
    if (rand() % 100 <= DESTRUCTIBILITY) {
        (*this -> _field)[y][x] = DESTRUCTIBLE;
    }
    else {
        (*this -> _field)[y][x] = WALL;
    }
}

void MapGenerator::setExtra(int y, int x)
{
    std::vector<std::vector<char>> & field = (*this -> _field);
    
    if (y >= 0 && y < this -> _height && x >= 0 && x < this -> _width
            && field[y][x] == UNDEFINED) {
        field[y][x] = TOBEDEFINED;
        this -> _extra.push_back(std::pair<int, int>(y, x));
    }
}

std::pair<std::list<AGameObject*>, std::list<AGameObject*>> MapGenerator::ToList()
{
    for (int y = 0; y < this -> _height; y++) {
        for (int x = 0; x < this -> _width; x++) {
            if (x == 0 || y == 0 || x == this -> _width - 1 || y == this -> _height - 1) {
                (*this -> _field)[y][x] = WALL;
                this -> _objects.first.push_back(new Wall());
                this -> _objects.first.back()->setPosition(static_cast<double>(x), static_cast<double>(y));
            } else {
                if ((*this -> _field)[y][x] == UNDEFINED) {
                    MapGenerator::Harden(y, x);
                }
                switch ((*this -> _field)[y][x])
                {
                    case WALL:
                        this -> _objects.first.push_back(new Wall());
                        this -> _objects.first.back()->setPosition(static_cast<double>(x), static_cast<double>(y));
                        break;
                    case DESTRUCTIBLE:
                        this -> _objects.second.push_back(new Box());
                        this -> _objects.second.back()->setPosition(static_cast<double>(x), static_cast<double>(y));
                        break;
                    default:
                        break;
                }
            }
        }
    }
    MapGenerator::printMap();
    std::cout << "Completed!" << std::endl;
    return this -> _objects;
}

std::pair<int, int> MapGenerator::seekSpot(int y, int x) 
{    
    for (int j = y; j < this -> _height; j++) {
        for (int i = (j == x) ? (x) : (0); i < this -> _width; i++) {
            if ((*this -> _field)[j][i] == PATH) {
                std::cout << (*this -> _field)[j][i] << std::endl;
                return std::pair<int, int>(y, x);
            }
        }
    }
    
    for (int j = y; j > 0; j--) {
        for (int i = (j == x) ? (x) : (this -> _width - 1); i > 0; i--) {
            if ((*this -> _field)[j][i] == PATH) {
                std::cout << (*this -> _field)[j][i] << std::endl;
                return std::pair<int, int>(y, x);
            }
        }
    }
    return std::pair<int, int>(-1, -1);
}

std::list<std::pair<int, int> > MapGenerator::setHumans(int players, int ai)
{
    std::list<std::pair<int, int> >   playersList;
    
    assert(players <= 3 && "4 players max");
    assert(this -> _field != nullptr && "You should call MapGenerator::Generate() before MapGenerator::setHumans()");
        
    int                 tab[4 * 2] = {1, 1, this -> _width - 1, 1, this -> _width - 1, this -> _height - 1, 1, this -> _height - 1};
    std::pair<int, int> coord;

    std::cout << "Spawning players" << std::endl;
    MapGenerator::printMap();
    for (int i = 0; i < players * 2; i += 2) {
        coord = MapGenerator::seekSpot(tab[i + 1], tab[i]);
        if (coord.first == -1)
            throw Exception("Could not find available spot for player to spawn.");
        std::cout << "player " << (i + 1) / 2 << " [" << coord.first <<  ","  << coord.second << "]" << std::endl;
        playersList.push_back(coord);
    }
    std::cout << "END" << std::endl;
    return playersList;
}

void MapGenerator::printMap() const {
    for (int j = 0; j < this -> _height; j++) {
        for (int i = 0; i < this -> _width; i++) {
            std::cout << (*this -> _field)[j][i];
        }
        std::cout << std::endl;
    }
}



//~ Formatted by Jindent --- http://www.jindent.com
