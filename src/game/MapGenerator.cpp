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


static int const  BRANCHRATE      = -2;    // positive means more branches and negative longer branches
static char const WALL            = '#';
static char const PATH            = '.';
static char const UNDEFINED       = '?';
static char const TOBEDEFINED     = ',';
static char const DESTRUCTIBLE    = '@';
static int const  DESTRUCTIBILITY = 70; // in percent

MapGenerator::MapGenerator():
    _field(nullptr)
{
    srand(time(NULL));
}

MapGenerator::~MapGenerator(){}

/* MEMBER FUNCTIONS */
std::pair<std::list<AGameObject*>, std::list<AGameObject*>> MapGenerator::Generate(int width, int height)
{
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
    std::vector<std::pair<int, int>> extra;
    std::vector<std::vector<char>> & field = (*this -> _field);

    field[y][x] = PATH;
    if (x > 0 && field[y][x - 1] == UNDEFINED) {
        field[y][x - 1] = TOBEDEFINED;
        extra.push_back(std::pair<int, int>(y, x - 1));
    }
    if (x < this -> _width - 1 && field[y][x + 1] == UNDEFINED) {
        field[y][x + 1] = TOBEDEFINED;
        extra.push_back(std::pair<int, int>(y, x + 1));
    }
    if (y > 0 && field[y - 1][x] == UNDEFINED) {
        field[y - 1][x] = TOBEDEFINED;
        extra.push_back(std::pair<int, int>(y - 1, x));
    }
    if (y < this -> _height - 1 && field[y + 1][x] == UNDEFINED) {
        field[y + 1][x] = TOBEDEFINED;
        extra.push_back(std::pair<int, int>(y + 1, x));
    }

    while (extra.empty() == false)
    {
        int elem = rand() % extra.size();
        this -> _frontier.push_back(extra[elem]);
        extra.erase(extra.begin() + elem);
    }
}

bool MapGenerator::Check(int y, int x)
{
    int edgeState = 0;
    std::vector<std::vector<char>> & field = (*this -> _field);

    if (x > 0 && field[y][x - 1] == PATH) {
        edgeState += 1;
    }
    if (x < this -> _width - 1 && field[y][x + 1] == PATH) {
        edgeState += 2;
    }
    if (y > 0 && field[y - 1][x] == PATH) {
        edgeState += 4;
    }
    if (y < this -> _height - 1 && field[y + 1][x] == PATH) {
        edgeState += 8;
    }
    
    if (edgeState == 1 || edgeState == 2 || edgeState == 4 || edgeState == 8) {
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

std::pair<std::list<AGameObject*>, std::list<AGameObject*>> MapGenerator::ToList()
{
    for (int y = 0; y < this -> _height; y++) {
        for (int x = 0; x < this -> _width; x++) {
            if (x == 0 || y == 0 || x == this -> _width - 1 || y == this -> _height - 1) {
                this -> _objects.first.push_back(new Wall());
                this -> _objects.first.back()->setPosition(static_cast<double>(x), static_cast<double>(y));
            } else {
                if ((*this -> _field)[y][x] == UNDEFINED) {
                    MapGenerator::Harden(x, y);
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
    return this -> _objects;
}


//~ Formatted by Jindent --- http://www.jindent.com
