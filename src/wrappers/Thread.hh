
#ifndef	THREAD_HH_
# define	THREAD_HH_ 

# include	<pthread.h>
# include	"IThread.hh"
# include	"ICondVar.hh"
# include	"IMutex.hh"

class Thread : public IThread
{
public:
	Thread();
	~Thread();

	IThread::status const &	getStatus() const;
//	void	start(start_routine_t routine, void *arg);
//	void	join();

	int start();
	int join();
	int detach();

//	virtual void *	run() = 0;

protected:
	pthread_t			_thread;
	IThread::status	_status;
	ICondVar				*_cv;
	IMutex				*_mutex;
};

#endif
