
#include <stdexcept>
#include <pthread.h>
#include "Mutex.hh"

/*int pthread_mutex_destroy(pthread_mutex_t *mutex);
int pthread_mutex_init(pthread_mutex_t *restrict mutex,
const pthread_mutexattr_t *restrict attr);
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER; 

int pthread_mutex_lock(pthread_mutex_t *mutex);
int pthread_mutex_trylock(pthread_mutex_t *mutex);
int pthread_mutex_unlock(pthread_mutex_t *mutex); 
*/
Mutex::Mutex()
{
	if (pthread_mutex_init(&_mutex, NULL) != 0)
		throw std::runtime_error("Can't init mutex");
}
Mutex::~Mutex()
{
	if (pthread_mutex_destroy(&_mutex) != 0)
		throw std::runtime_error("Can't destroy mutex");
}

void Mutex::lock(void)
{
	if (pthread_mutex_lock(&_mutex) != 0)
		throw std::runtime_error("Can't lock mutex");
}
void Mutex::unlock(void)
{
	if (pthread_mutex_unlock(&_mutex) != 0)
		throw std::runtime_error("Can't unlock mutex");
}
bool Mutex::trylock(void)
{
	return ((pthread_mutex_trylock(&_mutex) == 0) ? (true) : (false));
}
