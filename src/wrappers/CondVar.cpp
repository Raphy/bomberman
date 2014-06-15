
#include <stdexcept>
#include "CondVar.hh"
#include "ScopedLock.hh"
#include "Mutex.hh"

/*int pthread_cond_destroy(pthread_cond_t *cond);
int pthread_cond_init(pthread_cond_t *restrict cond,
	const pthread_condattr_t *restrict attr);
pthread_cond_t cond = PTHREAD_COND_INITIALIZER; 
*/

/*
int pthread_cond_timedwait(pthread_cond_t *restrict cond,
	pthread_mutex_t *restrict mutex,
	const struct timespec *restrict abstime);

int pthread_cond_wait(pthread_cond_t *restrict cond,
	pthread_mutex_t *restrict mutex); 
int pthread_cond_broadcast(pthread_cond_t *cond);
int pthread_cond_signal(pthread_cond_t *cond); 
*/

CondVar::CondVar()
{
	_mutex = new Mutex();
	if (pthread_cond_init(&_cond, NULL) != 0)
		throw std::runtime_error("Can't init condition variable");
}
CondVar::~CondVar()
{
	delete _mutex;
	if (pthread_cond_destroy(&_cond) != 0)
		throw std::runtime_error("Can't destroy condition variable");
}

void CondVar::wait(void)
{
	ScopedLock lock(_mutex);
	if (pthread_cond_wait(&_cond, &(_mutex->getNativeMutex())) != 0)
		throw std::runtime_error("Can't wait condition variable");
}
void CondVar::signal(void)
{
	if (pthread_cond_signal(&_cond) != 0)
		throw std::runtime_error("Can't signal condition variable");
}
void CondVar::broadcast(void)
{
	if (pthread_cond_broadcast(&_cond) != 0)
		throw std::runtime_error("Can't broadcast condition variable");
}
