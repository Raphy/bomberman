#include <iostream>
#include <fstream>
#include "SoundManager.hh"

SoundManager::SoundManager()
  : _volume(128), _volumeFx(128), _volumeMusic(128), _mute(false), _muteFx(false), _muteMusic(false)
{
  /*
  ** Init de SDL_Mix ? si singleton Mix_audio ! else allocate channel
  */
  Mix_OpenAudio(44100, AUDIO_S16SYS, 2, 2048); // #### RETOUR
  Mix_AllocateChannels(64); // nb channels for Fx

  /* Set du volume au max au debut*/
  setVolume(_volume);

  // path = ""; Tu ne peux pas modifier un membre si il est constant. (tu dois le faire dans la liste d'initialisation)
  /*
    loadFx("goats", path + "goats.wav");
    loadMusic("pokemon", path + "pokemon.mp3");
  */
}

SoundManager::~SoundManager()
{
  // Free tout les musics ? ou chacun les Free

  Mix_CloseAudio();
}

SoundManager& SoundManager::getInstance()
{
  static SoundManager instance;
  return instance;
}

void	SoundManager::loadFx(const std::string& tag, const std::string& path)
{
  Mix_Chunk *tmp;

  tmp = Mix_LoadWAV(path.c_str());
  if (tmp != NULL)
    _soundFx.insert(std::pair<std::string, Mix_Chunk*>(tag, tmp));
  else
    std::cout << "Music not create" << std::endl;
}

void	SoundManager::loadMusic(const std::string& tag, const std::string& path)
{
  Mix_Music *tmp;

  tmp = Mix_LoadMUS(path.c_str());
  if (tmp != NULL)
    _soundMusic.insert(std::pair<std::string, Mix_Music*>(tag, tmp));
  else
    std::cout << "Music not create" << std::endl;
}

void SoundManager::deleteFx(const std::string& tag)
{
  std::map<std::string, Mix_Chunk*>::iterator it;

  it = _soundFx.find(tag);
  if (it == _soundFx.end())
    std::cout << "Music :" << tag << "not found" << std::endl;
  else
    {
      Mix_FreeChunk(it->second);
      _soundFx.erase(it);
    }
}

void SoundManager::deleteMusic(const std::string& tag)
{
  std::map<std::string, Mix_Music*>::iterator it;

  it = _soundMusic.find(tag);
  if (it == _soundMusic.end())
    std::cout << "Music :" << tag << "not found" << std::endl;
  else
    {
      Mix_FreeMusic(it->second);
      _soundMusic.erase(it);
    }
}

void	SoundManager::playMusic(const std::string& music)
{
  std::map<std::string, Mix_Music*>::iterator it;

  it = _soundMusic.find(music);
  if (it == _soundMusic.end())
    std::cout << "Music :" << music << "not play" << std::endl;
  else
    Mix_PlayMusic(it->second, 1);
}

void	SoundManager::playFx(const std::string& music)
{
  std::map<std::string, Mix_Chunk*>::iterator it;

  it = _soundFx.find(music);
  if (it == _soundFx.end())
    std::cout << "Music :" << music << "not play" << std::endl;
  else
    Mix_PlayChannel(-1, it->second, 0);
}

void	SoundManager::stopMusic()
{
  Mix_HaltMusic();
}

void	SoundManager::stopFx()
{
  Mix_HaltChannel(-1);
}

void	SoundManager::stop()
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

void	SoundManager::setVolume(int v)
{
  if (v >= 0 || v <= 128)
    {
      _volume = v;
      setVolumeFx(_volume);
      setVolumeMusic(_volume);
    }
}

void	SoundManager::setVolumeFx(int v)
{
  if (v >= 0 || v <= 128)
    {
      Mix_Volume(-1, v);
      _volumeFx = v;
    }
}

void	SoundManager::setVolumeMusic(int v)
{
  if (v >= 0 || v <= 128)
    {
      Mix_VolumeMusic(v);
      _volumeMusic = v;
    }
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

void SoundManager::Mute()
{
  if (isMute() == false)
    {
      _mute = true;
      _muteFx = true;
      _muteMusic = true;
      MuteMusic();
      MuteFx();
    }
  else
    {
      _mute = false;
      _muteFx = false;
      _muteMusic = false;
      MuteMusic();
      MuteFx();
    }
}

void SoundManager::MuteMusic()
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

void SoundManager::MuteFx()
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
