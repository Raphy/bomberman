#ifndef SOUNDS_LOADER_HH_
# define SOUNDS_LOADER_HH_

# include <string>

# include "SoundManager.hh"

class SoundsLoader {
private:
    static SoundManager& s_sound_manager;

public:
    void operator()();
};

#endif // !SOUNDS_LOADER_HH_
