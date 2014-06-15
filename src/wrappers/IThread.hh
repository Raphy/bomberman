
#ifndef	ITHREAD_HH_
# define	ITHREAD_HH_ 

class IThread
{
public:
	enum status { NOT_START, ALIVE, DEAD };

	virtual ~IThread() {}

	virtual status const &	getStatus() const = 0;
//	void	start(start_routine_t routine, void *arg);
//	void	join();

	virtual int start() = 0;
	virtual int join() = 0;
	virtual int detach() = 0;

	virtual void *	routine() = 0;
};

#endif