
#ifndef	MUTEX_HH_
# define	MUTEX_HH_ 

# include	<pthread.h>
# include	"IMutex.hh"

class Mutex : public IMutex
{
public:
	Mutex();
	~Mutex(void);

	void lock(void);
	void unlock(void);
	bool trylock(void);

	pthread_mutex_t &	getNativeMutex() { return _mutex; }

private:
	pthread_mutex_t	_mutex;
};

#endif