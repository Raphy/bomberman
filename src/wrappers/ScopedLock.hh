
#ifndef	SCOPED_LOCK_HPP
# define	SCOPED_LOCK_HPP

# include	"IMutex.hh"

class ScopedLock
{
public:
	ScopedLock(IMutex * const mutex);
	~ScopedLock();

private:
	IMutex *	_mutex;
};

#endif