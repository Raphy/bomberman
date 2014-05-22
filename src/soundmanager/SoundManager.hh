#include <SDL/SDL.h>
#include <SDL/SDL_mixer.h>
#include <map>
#include <string>

/*
** Gestion d'erreur ++
*/

class SoundManager
{
public:
  static SoundManager& getInstance();

  void playMusic(const std::string&);
  void playFx(const std::string&);

  /*
  **   check le doublon ? depend comment il sera utilise ? singleton ?
  */
  void loadFx(const std::string&, const std::string&);
  void loadMusic(const std::string&, const std::string&);

  /*
  ** Penser a STOPER AVANT D'effacer
  */
  void deleteFx(const std::string& tag);
  void deleteMusic(const std::string& tag);

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

  /*
  ** Map de son
  */
  std::map<std::string, Mix_Music *> _soundMusic;
  std::map<std::string, Mix_Chunk *> _soundFx;

  /*
  ** Volume 0 to 128
  */
  int _volume;
  int _volumeFx;
  int _volumeMusic;
  bool _mute;
  bool _muteFx;
  bool _muteMusic;
  const std::string path;
};
