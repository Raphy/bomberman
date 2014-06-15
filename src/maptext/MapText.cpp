
#include "MapText.hh"

// This avoid a compiler bug with new c++ features.
const char MapText::VOID;// = '_';
const char MapText::PLAYER_1;// = '1';
const char MapText::PLAYER_2;// = '2';
const char MapText::ENEMY;// = 'e';
const char MapText::WALL;// = 'w';
const char MapText::BOMB;// = 'b';
const char MapText::FIRE;// = 'f';
const char MapText::BOX;// = 'f';

MapText::MapText() :
    m_width(0), m_height(0)
{
}