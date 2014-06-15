
#include "ScopedLock.hh"

ScopedLock::ScopedLock(IMutex * const mutex)
	: _mutex(mutex)
{
	_mutex->lock();
}
ScopedLock::~ScopedLock()
{
	_mutex->unlock();	
}
