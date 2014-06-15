
#ifndef	ICOND_VAR_HH_
# define	ICOND_VAR_HH_ 

# include	"ScopedLock.hh"

class ICondVar
{
public:
	virtual ~ICondVar() {}
	virtual void wait(void) = 0;
	virtual void signal(void) = 0;
	virtual void broadcast(void) = 0;
};

#endif