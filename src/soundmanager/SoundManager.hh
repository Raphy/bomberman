#ifndef		_SOUND_MANAGER_HH_
# define	_SOUND_MANAGER_HH_

# include <SDL/SDL.h>
# include <SDL/SDL_mixer.h>
# include <map>
# include <string>

class SoundManager
{
public:
  static SoundManager& getInstance();

  bool playMusic(const std::string&);
  bool playMusicFade(const std::string&);
  bool playFx(const std::string&);

  bool loadFx(const std::string&, const std::string&);
  bool loadMusic(const std::string&, const std::string&);

  bool deleteFx(const std::string& tag);
  bool deleteMusic(const std::string& tag);

  void stopMusic();
  void stopFx();
  void stop();

  void pause();
  void pauseFx();
  void pauseMusic();

  void resume();
  void resumeFx();
  void resumeMusic();

  void setVolume(int v);
  void setVolumeFx(int v);
  void setVolumeMusic(int v);

  int getVolume();
  int getVolumeFx();
  int getVolumeMusic();

  void Mute();
  void MuteMusic();
  void MuteFx();
  bool isMute();
  bool isMuteMusic();
  bool isMuteFx();

private:
  SoundManager();
  ~SoundManager();
  SoundManager(SoundManager const&);
  void operator=(SoundManager const&);

  std::map<std::string, Mix_Music *> _soundMusic;
  std::map<std::string, Mix_Chunk *> _soundFx;

  int _volume;
  int _volumeFx;
  int _volumeMusic;
  bool _mute;
  bool _muteFx;
  bool _muteMusic;
};

#endif /* !_SOUND_MANAGER_HH_ */