
#ifndef	IMUTEX_HH_
# define	IMUTEX_HH_ 

# include	<pthread.h>

class IMutex
{
public:
	virtual ~IMutex(void) {}

	virtual void lock(void) = 0;
	virtual void unlock(void) = 0;
	virtual bool trylock(void) = 0;

	virtual pthread_mutex_t &	getNativeMutex() /*const*/ = 0;
};

#endif