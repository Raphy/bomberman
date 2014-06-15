
#ifndef	COND_VAR_HH_
# define	COND_VAR_HH_ 

# include	"ICondVar.hh"
# include	"IMutex.hh"

class CondVar : public ICondVar
{
public:
	CondVar();
	~CondVar();

	void wait(void);
	void signal(void);
	void broadcast(void);

private:
	pthread_cond_t	_cond;
	IMutex *			_mutex;
};

#endif