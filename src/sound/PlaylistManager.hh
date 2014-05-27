#ifndef		_PLAYLIST_MANAGER_HH_
# define	_PLAYLIST_MANAGER_HH_

# include <vector>
# include "SoundManager.hh"

class		PlaylistManager
{
public:
  PlaylistManager();
  ~PlaylistManager();

  void addPlaylist(const std::string&);
  void deletePlaylist();
  void playPlaylist();
  bool update();
  void next();

private:
  std::vector<std::string> _playlist;
  SoundManager& _son;
  unsigned int _n;
};

#endif
