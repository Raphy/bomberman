
#include <stdexcept>
#include "Thread.hh"
#include "CondVar.hh"
#include "Mutex.hh"

static void *	runThread(void * arg)
{
	return (static_cast<Thread *>(arg))->run();
}


Thread::Thread()
	: _status(NOT_START), _cv(new CondVar()), _mutex(new Mutex())
{}
Thread::~Thread()
{
	if (_status == ALIVE)
		throw std::runtime_error("Destruction of alive thread");
	delete _cv;
	delete _mutex;
}

IThread::status const &	Thread::getStatus() const
{
	return _status;
}
/*void			Thread::start(start_routine_t routine, void *child)
{
	if (_status == ALIVE)
		throw std::runtime_error("Creation of alive thread");
	_status = ALIVE;
	pthread_create(&this->_thread, NULL, routine, child);
}
void			Thread::join()
{
	if (_status != ALIVE)
		throw std::runtime_error("Try to join a non-started or dead thread");
	_status = DEAD;
	pthread_join(this->_thread, NULL);
}
*/
int	Thread::start()
{
	if (_status == ALIVE)
		throw std::runtime_error("Creation of alive thread");
	_status = ALIVE;
	return pthread_create(&this->_thread, NULL, runThread, this);	
}
int	Thread::join()
{
	if (_status != ALIVE)
		throw std::runtime_error("Try to join a non-started or dead thread");
	_status = DEAD;
	return pthread_join(this->_thread, NULL);
}
int	Thread::detach()
{
	return -1;
}
