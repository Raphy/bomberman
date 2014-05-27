#include "PlaylistManager.hh"

PlaylistManager::PlaylistManager()
  :_son(SoundManager::getInstance()), _n(0)
{
}

PlaylistManager::~PlaylistManager()
{
  deletePlaylist();
}

void PlaylistManager::addPlaylist(const std::string& tag)
{
  _playlist.push_back(tag);
}

void PlaylistManager::deletePlaylist()
{
  while (!_playlist.empty())
    _playlist.pop_back();
}

void PlaylistManager::playPlaylist()
{
  _son.playMusicFade(_playlist[_n]);
}

bool PlaylistManager::update()
{
  if (Mix_PlayingMusic() == 0)
      return false;
  next();
  return true;
}

void PlaylistManager::next()
{
  _n++;
  if (_n == _playlist.size())
    _n = 0;
  _son.playMusicFade(_playlist[_n]);
}
