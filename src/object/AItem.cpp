//
// AItem.cpp for Bomberman in /home/raphy/Epitech/Tech_2/bomberman/src/object
// 
// Made by raphael defreitas
// Login   <defrei_r@epitech.net>
// 
// Started on  Sat Jun 14 01:22:19 2014 raphael defreitas
// Last update Sat Jun 14 01:36:37 2014 raphael defreitas
//

#include "AItem.hh"
#include "ResourcesPath.hh"

std::string const AItem::Tag = "item";

AItem::AItem(const std::string& tag):
  ACube(tag)
{
}

AItem::~AItem()
{
}
