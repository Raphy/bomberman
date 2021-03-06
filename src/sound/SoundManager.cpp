#include <iostream>
#include <fstream>
#include <exception>
#include <sstream>
#include "SoundManager.hh"
#include "ResourcesPath.hh"
#include "Configuration.hh"
#include "Exception.hh"

std::string const SoundManager::CONF_FILE = "volume.conf";

SoundManager::SoundManager()
  : _volume(128), _volumeFx(128), _volumeMusic(128), _mute(false), _muteFx(false), _muteMusic(false)
{
}

SoundManager::~SoundManager()
{
  stop();
  while (deleteFx(_soundFx.begin()->first) == true);
  while (deleteMusic(_soundMusic.begin()->first) == true);
  Mix_CloseAudio();
}

SoundManager& SoundManager::getInstance()
{
  static SoundManager instance;
  return instance;
}

void SoundManager::load(void)
{
  // Setting the  default configuration variables
  Configuration::setDefault<int>("sound_volume_fx", 128);
  Configuration::setDefault<int>("sound_volume_music", 128);
  if (Mix_OpenAudio(44100, AUDIO_S16SYS, 2, 2048) == -1)
    throw Exception("Init Mix_OpenAudio fail");
  Mix_AllocateChannels(64);
  setVolumeFx(Configuration::get<int>("sound_volume_fx"));
  setVolumeMusic(Configuration::get<int>("sound_volume_music"));
}

bool    SoundManager::loadFx(const std::string& tag, const std::string& path)
{
  Mix_Chunk *tmp;

  tmp = Mix_LoadWAV(path.c_str());
  if (tmp != NULL)
    {
      if (_soundFx.size() != 0 && _soundFx.find(tag) != _soundFx.end())
    return false;
      _soundFx.insert(std::pair<std::string, Mix_Chunk*>(tag, tmp));
    }
  else
    return false;
  return true;
}

bool    SoundManager::loadMusic(const std::string& tag, const std::string& path)
{
  Mix_Music *tmp;

  tmp = Mix_LoadMUS(path.c_str());
  if (tmp != NULL)
    {
      if (_soundMusic.size() != 0 && _soundMusic.find(tag) != _soundMusic.end()) {
        return false;
      }
      _soundMusic.insert(std::pair<std::string, Mix_Music*>(tag, tmp));
    }
  else {
    std::cerr << "warning: unable to load music " << path
      << ": " << Mix_GetError() << std::endl;
    return false;
  }
  return true;
}

bool SoundManager::deleteFx(const std::string& tag)
{
  std::map<std::string, Mix_Chunk*>::iterator it;

  it = _soundFx.find(tag);
  if (it == _soundFx.end())
    return false;
  Mix_FreeChunk(it->second);
  _soundFx.erase(it);
  return true;
}

bool SoundManager::deleteMusic(const std::string& tag)
{
  std::map<std::string, Mix_Music*>::iterator it;

  it = _soundMusic.find(tag);
  if (it == _soundMusic.end())
    return false;
  Mix_FreeMusic(it->second);
  _soundMusic.erase(it);
  return true;
}

bool    SoundManager::playMusic(const std::string& music)
{
  std::map<std::string, Mix_Music*>::iterator it;

  it = _soundMusic.find(music);
  if (it == _soundMusic.end())
    return false;
  if (Mix_PlayMusic(it->second, 1) == -1) {
    std::cerr << "warning: unable to play music taged '" << music
      << "'" << std::endl;
    return false;
  }
  return true;
}

bool    SoundManager::playMusicFade(const std::string& music)
{
  std::map<std::string, Mix_Music*>::iterator it;

  it = _soundMusic.find(music);
  if (it == _soundMusic.end())
    return false;
  if (Mix_FadeInMusic(it->second, 1, 1000) == -1)
    return false;
  return true;
}

bool    SoundManager::playFx(const std::string& music)
{
  std::map<std::string, Mix_Chunk*>::iterator it;

  it = _soundFx.find(music);
  if (it == _soundFx.end())
    return false;
  if (Mix_PlayChannel(-1, it->second, 0) == -1)
    return false;
  return true;
}

void    SoundManager::stopMusic()
{
  Mix_HaltMusic();
}

void    SoundManager::stopFx()
{
  Mix_HaltChannel(-1);
}

void    SoundManager::stop()
{
  stopFx();
  stopMusic();
}

void SoundManager::pause()
{
  pauseMusic();
  pauseFx();
}

void SoundManager::pauseFx()
{
  Mix_Pause(-1);
}

void SoundManager::pauseMusic()
{
  Mix_PauseMusic();
}

void SoundManager::resume()
{
  resumeFx();
  resumeMusic();
}

void SoundManager::resumeFx()
{
  Mix_Resume(-1);
}

void SoundManager::resumeMusic()
{
  Mix_ResumeMusic();
}

void    SoundManager::setVolume(int v)
{
  if (v >= 0 || v <= 128)
    {
      _volume = v;
      setVolumeFx(_volume);
      setVolumeMusic(_volume);
    }
}

void    SoundManager::setVolumeFx(int v)
{
  if (v < 0)
    _volumeFx = 0;
  else if (v > 128)
    _volumeFx = 128;
  else
    _volumeFx = v;

  Mix_Volume(-1, _volumeFx);
  Configuration::set<int>("sound_volume_fx", _volumeFx);
}

void    SoundManager::setVolumeMusic(int v)
{
  if (v < 0)
    _volumeMusic = 0;
  else if (v > 128)
    _volumeMusic = 128;
  else
  _volumeMusic = v;

  Mix_VolumeMusic(_volumeMusic);
  Configuration::set<int>("sound_volume_music", _volumeMusic);
}


int SoundManager::getVolume()
{
  return _volume;
}

int SoundManager::getVolumeFx()
{
  return _volumeFx;
}

int SoundManager::getVolumeMusic()
{
  return _volumeMusic;
}

void SoundManager::mute()
{
  if (isMute() == false)
    {
      _mute = true;
      muteMusic();
      muteFx();
    }
  else
    {
      _mute = false;
      muteMusic();
      muteFx();
    }
}

void SoundManager::muteMusic()
{
  if (isMuteMusic() == false)
    {
      _muteMusic = true;
      Mix_VolumeMusic(0);
    }
  else
    {
      _muteMusic = false;
      Mix_VolumeMusic(_volumeMusic);
    }
}

void SoundManager::muteFx()
{
  if (isMuteFx() == false)
    {
      _muteFx = true;
      Mix_Volume(-1, 0);
    }
  else
    {
      _muteFx = false;
      Mix_Volume(-1, _volumeFx);
    }
}

bool SoundManager::isMute()
{
  return _mute;
}

bool SoundManager::isMuteFx()
{
  return _muteFx;
}

bool SoundManager::isMuteMusic()
{
  return _muteMusic;
}
